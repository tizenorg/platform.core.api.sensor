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

#include <stdlib.h>
#include <sensor.h>
#include <sensor_log.h>

int sensor_recorder_is_supported(sensor_type_e type, bool *supported)
{
	_D("Called : sensor[%#x]", type);

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (!supported)
		return SENSOR_ERROR_INVALID_PARAMETER;

	*supported = false;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_start(sensor_type_e type, sensor_recorder_option_h option)
{
	_D("Called : sensor[%#x] with option[%d]", type, option);

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_stop(sensor_type_e type)
{
	_D("Called : sensor[%#x]", type);

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NOT_SUPPORTED;
}

int sensor_recorder_create_option(sensor_recorder_option_h *option)
{
	_D("Called : option[%#x]", *option);

	if (!option)
		return SENSOR_ERROR_INVALID_PARAMETER;

	*option = (sensor_recorder_option_h)malloc(sizeof(sensor_recorder_option_h));
	if (!*option)
		return SENSOR_ERROR_OUT_OF_MEMORY;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_destroy_option(sensor_recorder_option_h option)
{
	_D("Called : option[%#x]", option);

	if (!option)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_option_set_int(sensor_recorder_option_h option, sensor_recorder_option_e attribute, int value)
{
	_D("Called : attribute[%d] with value[%d] to option[%#x]", attribute, value, option);

	if (!option)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (attribute < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_create_query(sensor_recorder_query_h *query)
{
	_D("Called : query[%#x]", *query);

	if (!query)
		return SENSOR_ERROR_INVALID_PARAMETER;

	*query = (sensor_recorder_query_h)malloc(sizeof(sensor_recorder_query_h));
	if (!*query)
		return SENSOR_ERROR_OUT_OF_MEMORY;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_destroy_query(sensor_recorder_query_h query)
{
	_D("Called : query[%#x]", query);

	if (!query)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_query_set_int(sensor_recorder_query_h query, sensor_recorder_query_e attribute, int value)
{
	_D("Called : attribute[%d] with value[%d] to query[%#x]", attribute, value, query);

	if (!query)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (attribute < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_query_set_time(sensor_recorder_query_h query, sensor_recorder_query_e attribute, time_t t)
{
	_D("Called : attribute[%d] with time[%d] to query[%#x]", attribute, time(&t), query);

	if (!query)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (attribute < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (t < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_read(sensor_type_e type, sensor_recorder_query_h query, sensor_recorder_data_cb cb, void *user_data)
{
	_D("Called : query[%#x]", query);

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (!query || !cb)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_read_sync(sensor_type_e type, sensor_recorder_query_h query, sensor_recorder_data_cb cb, void *user_data)
{
	_D("Called : query[%#x]", query);

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (!query || !cb)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_data_get_time(sensor_recorder_data_h data, time_t *start_time, time_t *end_time)
{
	_D("Called : data[%#x]", data);

	if (!data || !start_time || !end_time)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_data_get_int(sensor_recorder_data_h data, sensor_recorder_data_e key, int *value)
{
	_D("Called : key[%d], data[%#x]", key, data);

	if (!data || !value)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (key < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_data_get_double(sensor_recorder_data_h data, sensor_recorder_data_e key, double *value)
{
	_D("Called : key[%d], data[%#x]", key, data);

	if (!data || !value)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (key < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;

	return SENSOR_ERROR_NONE;
}
