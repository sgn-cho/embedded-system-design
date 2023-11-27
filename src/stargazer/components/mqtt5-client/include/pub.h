#ifndef MQTT5_CLIENT_PUB_H_
#define MQTT5_CLIENT_PUB_H_

/**
 * @brief Publishes an MQTTv5 message.
 *
 * This function publishes an MQTTv5 message with the specified parameters.
 *
 * @param message The message to be published.
 * @param topic The topic to which the message will be published.
 * @param length The length of the message.
 * @param qos The quality of service level for the message (0 for at most once).
 * @param retain Whether the message should be retained by the broker.
 * @return esp_err_t Returns `ESP_OK` if the message is published successfully, 
 *         otherwise returns `ESP_FAIL`.
 */
esp_err_t publish_mqtt5_message(
    char *message,
    char *topic,
    int length,
    int qos,
    int retain
);

#endif // MQTT5_CLIENT_PUB_H_
