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

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_RECORDER_MODULE
 * @{
 */

/**
 * @brief   Sensor recorder handle.
 * @details
 * @since_tizen 3.0
 */
typedef void *sensor_recorder_h;

/**
 * @brief   Sensor recorder filter handle.
 * @details
 * @since_tizen 3.0
 */
typedef void *sensor_recorder_filter_h;

/**
 * @brief   Sensor data handle.
 * @details
 * @since_tizen 3.0
 */
typedef void *sensor_data_h;

/*
 * @brief   Enumeration for options of sensor recorder errors
 * @details
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORDER_ERROR_NONE                  = TIZEN_ERROR_NONE,                 /**< Successful */
	SENSOR_RECORDER_ERROR_INVALID_PARAMETER     = TIZEN_ERROR_INVALID_PARAMETER,    /**< Invalid parameter */
	SENSOR_RECORDER_ERROR_NOT_SUPPORTED         = TIZEN_ERROR_NOT_SUPPORTED,        /**< Not supported */
	SENSOR_RECORDER_ERROR_PERMISSION_DENIED     = TIZEN_ERROR_PERMISSION_DENIED,    /**< Permission denied */
	SENSOR_RECORDER_ERROR_OUT_OF_MEMORY         = TIZEN_ERROR_OUT_OF_MEMORY,        /**< Out of memory */
	SENSOR_RECORDER_ERROR_OPERATION_FAILED      = TIZEN_ERROR_SENSOR | 0x06,        /**< Operation failed */
} sensor_recorder_error_e;

/*
 * @brief   Enumeration for options of sensor records
 * @details
 * @see     #SENSOR_RECORDER_START
 * @since_tizen 3.0
 */
typedef enum
{
} sensor_recorder_option_e;

/*
 * @brief   Enumeration for sensor record types
 * @details
 * @see     #SENSOR_RECORDER_START
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORDER_EXERCISE = 0,
	SENSOR_RECORDER_HUMAN_PEDOMETER,
	SENSOR_RECORDER_HUMAN_SLEEP_MONITOR,
	SENSOR_RECORDER_HRM,
} sensor_recorder_type_e;

/*
 * @brief   Enumeration for filters of sensor records
 * @details
 * @see     #SENSOR_RECORDER_FILTER_SET_INT
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORDER_FILTER_START_TIME = 0,
	SENSOR_RECORDER_FILTER_END_TIME,
	SENSOR_RECORDER_FILTER_ANCHOR_TIME,
	SENSOR_RECORDER_FILTER_RESULT_SIZE,
	SENSOR_RECORDER_FILTER_TIME_INTERVAL,
} sensor_recorder_filter_e;


/**
 * @brief   Checks whether a given sensor record type is supported
 * @details
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
 * @details
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
 * @details
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
 * @brief   Creates recorder filter handle
 * @details
 * @since_tizen 3.0
 *
 * @param[out]  filter  A filter handle
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_create_filter(sensor_recorder_filter_h *filter);

/**
 * @brief   Destroys recorder filter handle
 * @details
 * @since_tizen 3.0
 *
 * @param[in]  filter A filter handle
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_destroy_filter(sensor_recorder_filter_h filter);

/**
 * @brief   Sets an integer value to a filter
 * @details
 * @since_tizen 3.0
 *
 * @param[in]  filter      A filter handle
 * @param[in]  filter_type A filter type
 * @param[in]  value       A value
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_filter_set_int(sensor_recorder_filter_h filter, sensor_recorder_filter_e filter_type, int value);

/**
 * @brief   Unsets an value to a filter
 * @details
 * @since_tizen 3.0
 *
 * @param[in]  filter      A filter handle
 * @param[in]  filter_type A filter type
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_filter_unset_int(sensor_recorder_filter_h filter, sensor_recorder_filter_e filter_type);

/**
 * @brief    Callback
 * @details
 * @since_tizen 3.0
 *
 * @param[out]  type   A sensor type
 * @param[out]  data   A record data
 * @param[out]  error  An error
 * @param[out]  data   A user data
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
typedef void (*sensor_recorder_cb)(sensor_recorder_type_e type, sensor_data_h data, sensor_recorder_error_e error, void *data);

/**
 * @brief    read a record synchronously
 * @details
 * @since_tizen 3.0
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_read_sync(sensor_type_t type, sensor_recorder_filter_h filter, sensor_data_h **records);

/**
 * @brief    read a sensor record asynchronously
 * @details
 * @since_tizen 3.0
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_read(sensor_type_t type, sensor_recorder_filter_h filter, sensor_recorder_cb cb, void *data);

/**
 * @brief    Gets a integer value from a record
 * @details
 * @since_tizen 3.0
 *
 * @return  #SENSOR_RECORDER_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_RECORDER_ERROR_NONE                 Successful
 * @retval  #SENSOR_RECORDER_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_RECORDER_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_data_get_int(sensor_data_h data, const char *key, int *value);

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
int sensor_recorder_data_get_double(sensor_data_h data, const char *key, double *value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_RECORDER_H__ */
