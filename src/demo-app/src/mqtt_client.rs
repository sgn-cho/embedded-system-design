use std::net::SocketAddr;

use mqtt::AsyncClient;
use paho_mqtt::{self as mqtt, MQTT_VERSION_5};
use axum::{extract::{
    ws::{WebSocket, Message},
    WebSocketUpgrade,
    ConnectInfo,
    TypedHeader},
    response::IntoResponse
};
use tokio_stream::StreamExt;
use log::{info, warn};
use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize)]
struct SensorSocketMessage {
    sensor_type: String,
    sensor_value: f64
}

pub async fn ws_handler(
    ws: WebSocketUpgrade,
    _: Option<TypedHeader<axum::headers::UserAgent>>,
    ConnectInfo(addr): ConnectInfo<SocketAddr>
) -> impl IntoResponse
{
    ws.on_upgrade(move |socket| handle_websocket(socket, addr))
}

async fn handle_websocket(mut socket: WebSocket, addr: SocketAddr) {
    let mut client = connect_mqtt().await;
    let mut stream = client.get_stream(10);

    info!("mqtt connection established with {addr}");
    while let Some(message_opt) = stream.next().await {
        if let Some(message) = message_opt {
            let test = message.payload();
            let mut buffer = [0u8; 8];

            for idx in 0..8 {
                buffer[idx] = test[7 - idx];
            }

            let send_data = SensorSocketMessage {
                sensor_type: message.topic().to_string(),
                sensor_value: f64::from_be_bytes(buffer)
            };
            
            if socket
                .send(Message::Text(serde_json::to_string(&send_data).unwrap()))
                .await
                .is_err()
            {
                warn!("client {addr} abruptly disconnected");
                return;
            }
        }
    }
}

async fn connect_mqtt() -> AsyncClient {
    let options = mqtt::CreateOptionsBuilder::new()
        .server_uri("127.0.0.1:1883")
        .client_id("stargazer-demo-app")
        .finalize();

    let client = mqtt::AsyncClient::new(options).unwrap();

    let connect_options = 
            mqtt::ConnectOptionsBuilder::with_mqtt_version(MQTT_VERSION_5)
            .clean_session(true)
            .finalize();

    client.connect(connect_options).await.unwrap();
    client.subscribe_many(&["temperature_sensor", "humidity_sensor", "soil_sensor"], &[0, 0, 0]).await.unwrap();
    client
}