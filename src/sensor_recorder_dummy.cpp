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

#include <sensor.h>

int sensor_recorder_is_supported(sensor_type_e type, bool *supported)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_start(sensor_type_e type, sensor_recorder_option_h option)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_stop(sensor_type_e type)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_create_option(sensor_recorder_option_h *option)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_destroy_option(sensor_recorder_option_h option)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_option_set_int(sensor_recorder_option_h option, sensor_recorder_option_e attribute, int value)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_create_query(sensor_recorder_query_h *query)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_destroy_query(sensor_recorder_query_h query)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_query_set_int(sensor_recorder_query_h query, sensor_recorder_query_e attribute, int value)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_query_set_time(sensor_recorder_query_h query, sensor_recorder_query_e attribute, time_t t)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_read(sensor_type_e type, sensor_recorder_query_h query, sensor_recorder_data_cb cb, void *user_data)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_read_sync(sensor_type_e type, sensor_recorder_query_h query, sensor_recorder_data_cb cb, void *user_data)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_data_get_time(sensor_recorder_data_h data, time_t *start_time, time_t *end_time)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_data_get_int(sensor_recorder_data_h data, sensor_recorder_data_e key, int *value)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_data_get_double(sensor_recorder_data_h data, sensor_recorder_data_e key, double *value)
{
	return SENSOR_ERROR_NOT_SUPPORTED;
}
