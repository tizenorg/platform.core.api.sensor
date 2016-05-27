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
typedef void *sensor_record_filter_h;

/**
 * @brief   Sensor record handle.
 * @details
 * @since_tizen 3.0
 */
typedef void *sensor_record_h;

/*
 * @brief   Enumeration for options of sensor recorder errors
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORD_ERROR_NONE = 0,
} sensor_record_error_e;


/*
 * @brief   Enumeration for options of sensor records
 * @see     #SENSOR_RECORDER_START
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORD_OPTION_ALL = 0, //?
} sensor_record_option_e;

/*
 * @brief   Enumeration for sensor record types
 * @see     #SENSOR_RECORDER_START
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORD_EXERCISE = 0,
	SENSOR_RECORD_PEDOMETER,
	SENSOR_RECORD_SLEEP_MONITOR,
	SENSOR_RECORD_HRM,
} sensor_record_type_e;

/*
 * @brief   Enumeration for filters of sensor records
 * @see     #SENSOR_RECORDER_FILTER_SET_INT
 * @since_tizen 3.0
 */
typedef enum
{
	SENSOR_RECORD_FILTER_START_TIME = 0,
	SENSOR_RECORD_FILTER_END_TIME,
	SENSOR_RECORD_FILTER_ANCHOR_TIME,
	SENSOR_RECORD_FILTER_RESULT_SIZE,
	SENSOR_RECORD_FILTER_TIME_INTERVAL,
} sensor_record_filter_e;


/**
 * @brief   Checks whether a given sensor record type is supported
 * @details
 * @since_tizen 3.0
 *
 * @param[in]   type        A sensor type to check
 * @param[out]  supported   If supported, @c true; Otherwise @c false
 *
 * @return  #SENSOR_ERROR_NONE on success; Otherwise a negative error value
 * @retval  #SENSOR_ERROR_NONE                 Successful
 * @retval  #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 */
int sensor_recorder_is_supported(sensor_record_type_e type);

/**
 * @brief   Starts recording the sensor events.
 * @details
 * @since_tizen 3.0
 *
 * @param[in]  type    A sensor type to start recording events
 * @param[in]  option  Option
 *
 * @return  #SENSOR_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_ERROR_NONE                 Successful
 * @retval  #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_start(sensor_record_type_e type, sensor_record_option_e option);

/**
 * @brief   Stops recording the sensor events.
 * @details
 * @since_tizen 3.0
 *
 * @param[in]  type    A sensor type to stop recording events
 *
 * @return  #SENSOR_ERROR_NONE on success, otherwise a negative error value
 * @retval  #SENSOR_ERROR_NONE                 Successful
 * @retval  #SENSOR_ERROR_INVALID_PARAMETER    Invalid parameter
 * @retval  #SENSOR_ERROR_OPERATION_FAILED     Operation failed
 */
int sensor_recorder_stop(sensor_record_type_e type);

int sensor_recorder_create_filter(sensor_record_filter_h *filter);
int sensor_recorder_destroy_filter(sensor_record_filter_h filter);

int sensor_recorder_filter_set_int(sensor_record_filter_h filter, sensor_record_filter_e filter_type, int value);
int sensor_recorder_filter_unset_int(sensor_record_filter_h filter, sensor_record_filter_e filter_type);

typedef void (*sensor_recorder_cb)(sensor_record_type_e type, sensor_record_h record, sensor_record_error_e error, void *data);

int sensor_recorder_read_sync(sensor_type_t type, sensor_record_filter_h filter, sensor_record_h **records);
int sensor_recorder_read(sensor_type_t type, sensor_record_filter_h filter, sensor_recorder_cb cb, void *data);

int sensor_recorder_record_get_int(sensor_record_h record, const char *key, int *value);
int sensor_recorder_record_get_double(sensor_record_h record, const char *key, double *value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_RECORDER_H__ */
