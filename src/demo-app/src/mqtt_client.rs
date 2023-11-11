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

const TOPIC: &str = "sensor_data";
const QOS: i32 = 0;

pub async fn ws_handler(
    ws: WebSocketUpgrade,
    _: Option<TypedHeader<axum::headers::UserAgent>>,
    ConnectInfo(addr): ConnectInfo<SocketAddr>
) -> impl IntoResponse
{
    ws.on_upgrade(move |socket| handle_websocket(socket, addr))
}

async fn handle_websocket(mut socket: WebSocket, addr: SocketAddr) {
    let mut client = connect_mqtt().await.unwrap();
    let mut stream = client.get_stream(10);

    info!("mqtt connection established with {addr}");
    while let Some(message_opt) = stream.next().await {
        if let Some(message) = message_opt {
            if socket
                .send(Message::Text(message.to_string()))
                .await
                .is_err()
            {
                warn!("client {addr} abruptly disconnected");
                return;
            }
        }
    }
}

async fn connect_mqtt() -> Result<AsyncClient, Box<dyn std::error::Error>> {
    let options = mqtt::CreateOptionsBuilder::new()
        .server_uri("127.0.0.1:1883")
        .client_id("stargazer-demo-app")
        .finalize();

    let client = mqtt::AsyncClient::new(options)?;

    let connect_options = 
            mqtt::ConnectOptionsBuilder::with_mqtt_version(MQTT_VERSION_5)
            .clean_session(true)
            .finalize();

    client.connect(connect_options).await?;
    client.subscribe(TOPIC, QOS);

    Ok(client)
}