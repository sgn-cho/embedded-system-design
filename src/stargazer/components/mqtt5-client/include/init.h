#ifndef MQTT5_CLIENT_INIT_H_
#define MQTT5_CLIENT_INIT_H_

#include <esp_err.h>

/**
 * @brief Initializes the MQTT5 client.
 *
 * @return `ESP_OK` if the MQTT5 client is successfully initialized, 
 * otherwise an error code.
 */
esp_err_t init_mqtt5_client(void);

#endif // MQTT5_CLIENT_INIT_H_
