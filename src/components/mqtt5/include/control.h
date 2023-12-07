#ifndef MQTT5_CONTROL_H_
#define MQTT5_CONTROL_H_

#include <esp_err.h>

/**
 * @brief Initialize the mqtt5 module
 */
void init_mqtt5(void);

/**
 * @brief publish mqtt5 message to the broker
 * 
 * @param message the message to publish
 * @param topic the topic to publish to
 * @param qos the qos of the message
 * 
 * @return ESP_OK if successful, otherwise ESP_FAIL
*/
esp_err_t publish_mqtt5_message(char *message, char *topic, int length, int qos);

#endif