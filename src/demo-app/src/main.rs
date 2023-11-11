use std::net::SocketAddr;

use axum::{
    response::Html,
    routing::get,
    Router
};

mod mqtt_client;
use mqtt_client::ws_handler;

#[tokio::main]
async fn main() {
    let app = Router::new()
        .route("/", get(main_handler))
        .route("/sensor", get(ws_handler));

    let addr = SocketAddr::from(([127, 0, 0, 1], 3000));
    axum::Server::bind(&addr)
        .serve(app.into_make_service_with_connect_info::<SocketAddr>())
        .await
        .unwrap();
}

async fn main_handler() -> Html<&'static str> {
    Html(include_str!("./assets/sensor_data.html"))
}