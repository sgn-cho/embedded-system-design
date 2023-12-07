#ifndef TEMPERATURE_MEASUREMENT_H_
#define TEMPERATURE_MEASUREMENT_H_

#include <esp_err.h>

typedef struct measurement_config
{
	/**
	 * Measurements interval in ms
	 */
	uint32_t interval_ms;
	/**
	 * Offset in ms to utc time of measured samples. Counted as: utc_timestamp % utc_offset_ms
	 */
	uint32_t utc_offset_ms;
} measurement_config_t;

/**
 * Data structure for passing measured values
 */
typedef struct measurement_values
{
	/**
	 * Temperature in C.
	 */
	float temperature;
	/**
	 * Humidity in %
	 */
	float humidity;
	/**
	 * UTC timestamp in ms when the sample was taken
	 */
	uint64_t utc_timestamp;
} measurement_values_t;

esp_err_t init_measurement(measurement_config_t config);
void task_temperature_measurement(void *params);

#endif