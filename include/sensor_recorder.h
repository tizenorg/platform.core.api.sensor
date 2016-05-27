/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __SENSOR_RECORDER_H__
#define __SENSOR_RECORDER_H__

#include <tizen.h>
#include <sensor.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_RECORDER_MODULE
 * @{
 */

/**
 * @brief   Option handle to control the recording options and policies.
 * @details TBD
 * @since_tizen 3.0
 */
typedef void *sensor_recorder_option_h;

/**
 * @brief   Query handle to filter and aggregate the recorded sensor data.
 * @details TBD
 * @since_tizen 3.0
 */
typedef void *sensor_recorder_query_h;

/**
 * @brief   Data handle containing retrieved sensor records.
 * @details TBD
 * @since_tizen 3.0
 */
typedef void *sensor_recorder_data_h;

/*
 * @brief   Enumeration for sensor record types
 * @details TBD
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORDER_HRM = SENSOR_HRM,	/**< It tracks the user's heart-rates */
	SENSOR_RECORDER_PEDOMETER = SENSOR_HUMAN_PEDOMETER,	/**< It tracks the user's walking and running */
	SENSOR_RECORDER_SLEEP_STATE = SENSOR_HUMAN_SLEEP_STATE,	/**< It tracks the user's sleep states */
	SENSOR_RECORDER_EXERCISE = SENSOR_HUMAN_EXERCISE,	/**< It tracks the user's physical exercise */
} sensor_recorder_type_e;

/*
 * @brief   Enumeration for options of sensor records
 * @details TBD
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORDER_OPTION_INTERVAL;	/**< Desired interval between data records */
} sensor_recorder_option_e;

/*
 * @brief   Enumeration for filters of sensor records
 * @details TBD
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORDER_QUERY_START_TIME = 0,	/**< Start time of the data to be queried (Epoch); 30 days ago if unspecified */
	SENSOR_RECORDER_QUERY_END_TIME,	/**< End time of the data to be queried (Epoch); The current time if unspecified */
	SENSOR_RECORDER_QUERY_ANCHOR_TIME,	/**< TBD (Epoch); 7 AM today if unspecified */
	SENSOR_RECORDER_QUERY_TIME_INTERVAL,	/**< TBD (seconds); 24 hours if unspecified */
	SENSOR_RECORDER_QUERY_RESULT_SIZE,	/**< TBD */
} sensor_recorder_query_e;

/**
 * @brief   Checks whether a given sensor record type is supported
 * @details TBD
 * @since_tizen 3.0
 *
 * @param[in]   type        A sensor type to check
 * @param[out]  supported   If supported, @c true; Otherwise @c false
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success; Otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 */
int sensor_recorder_is_supported(sensor_recorder_type_e type);

/**
 * @brief   Starts recording the sensor events.
 * @details TBD
 * @since_tizen 3.0
 *
 * @param[in]  type    A sensor type to start recording events
 * @param[in]  option  Option
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_start(sensor_recorder_type_e type, sensor_recorder_option_e option);

/**
 * @brief   Stops recording the sensor events.
 * @details TBD
 * @since_tizen 3.0
 *
 * @param[in]  type    A sensor type to stop recording events
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_stop(sensor_recorder_type_e type);

/**
 * @brief   TBD
 * @details TBD
 * @since_tizen 3.0
 *
 * @param[out]  option TBD
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_create_option(sensor_recorder_option_h *option);

/**
 * @brief   TBD
 * @details TBD
 * @since_tizen 3.0
 *
 * @param[out]  option TBD
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_destroy_option(sensor_recorder_option_h option);

/**
 * @brief   Sets an option attribute
 * @details TBD
 * @since_tizen 3.0
 *
 * @param[in]  option      An option handle
 * @param[in]  attribute   An option attribute
 * @param[in]  value       A value
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_option_set_int(sensor_recorder_option_h query, sensor_recorder_option_e attribute, int value);

/**
 * @brief   Creates recorder query handle
 * @details TBD
 * @since_tizen 3.0
 *
 * @param[out]  query A query handle
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_create_query(sensor_recorder_query_h *query);

/**
 * @brief   Destroys recorder query handle
 * @details TBD
 * @since_tizen 3.0
 *
 * @param[in]  query A query handle
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_destroy_query(sensor_recorder_query_h query);

/**
 * @brief   Sets an integer value to a query
 * @details TBD
 * @since_tizen 3.0
 *
 * @param[in]  query       A query handle
 * @param[in]  attribute   A query attribute
 * @param[in]  value       A value
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_query_set_int(sensor_recorder_query_h query, sensor_recorder_query_e attribute, int value);

/**
 * @brief    Callback
 * @details  TBD
 * @since_tizen 3.0
 *
 * @param[out]  type   A sensor type
 * @param[out]  data   A record data
 * @param[out]  error  An error
 * @param[out]  user_data   A user data
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
typedef void (*sensor_recorder_cb)(sensor_recorder_type_e type, sensor_recorder_data_h data, sensor_error_e error, void *user_data);

/**
 * @brief    Reads recorded data asynchronously
 * @details  TBD
 * @since_tizen 3.0
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_read(sensor_recorder_type_e type, sensor_recorder_query_h query, sensor_recorder_cb cb, void *user_data);

/**
 * @brief    Reads recorded data synchronously
 * @details  TBD
 * @since_tizen 3.0
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_read_sync(sensor_recorder_type_e type, sensor_recorder_query_h filter, sensor_recorder_cb cb, void *user_data);

/**
 * @brief    Gets an integer value from a record
 * @details  TBD
 * @since_tizen 3.0
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_data_get_int(sensor_recorder_data_h data, const char *key, int *value);

/**
 * @brief    Gets a double value from a record
 * @details
 * @since_tizen 3.0
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_data_get_double(sensor_recorder_data_h data, const char *key, double *value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_RECORDER_H__ */
