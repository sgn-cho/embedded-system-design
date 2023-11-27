#include WIFI_INIT_H_
#define WIFI_INIT_H_

#include <esp_err.h>

/**
 * @brief Initializes the Wi-Fi module.
 * 
 * This function initializes the Wi-Fi module by creating a default Wi-Fi station,
 * initializing the Wi-Fi configuration, setting the Wi-Fi mode to station mode,
 * configuring the Wi-Fi station, and starting the Wi-Fi module.
 * 
 * @return esp_err_t Returns `ESP_OK` if the Wi-Fi module is initialized successfully,
 *                   otherwise returns an error code.
 */
esp_err_t wifi_init(void);

#endif // WIFI_INIT_H_
