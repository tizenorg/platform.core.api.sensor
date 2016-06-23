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

#include <Json.h>
#include <ErrorTypes.h>
#include <DBusClient.h>
#include <ProviderTypes.h>
#include <ScopeMutex.h>
#include <map>
#include <string>
#include <memory>

#include "include/sensor_log.h"

static ctx::DBusClient dbusClient;
static GMutex info_mutex;

static std::map<sensor_type_e, std::string> sensor_keys = {
	{SENSOR_HRM,                              SUBJ_SENSOR_HEART_RATE},
	{SENSOR_HUMAN_PEDOMETER,                  SUBJ_SENSOR_PEDOMETER},
	{SENSOR_HUMAN_SLEEP_MONITOR,              SUBJ_SENSOR_SLEEP_MONITOR},
	{SENSOR_PRESSURE,                         SUBJ_SENSOR_PRESSURE},
};

static std::map<sensor_recorder_option_e, std::string> option_keys = {
	{SENSOR_RECORDER_OPTION_RETENTION_PERIOD, KEY_RETENTION},
	{SENSOR_RECORDER_OPTION_INTERVAL,         KEY_INTERVAL}
};

static std::map<sensor_recorder_query_e, std::string> query_keys = {
	{SENSOR_RECORDER_QUERY_START_TIME,        KEY_START_TIME},
	{SENSOR_RECORDER_QUERY_END_TIME,          KEY_END_TIME},
	{SENSOR_RECORDER_QUERY_ANCHOR_TIME,       KEY_ANCHOR},
	{SENSOR_RECORDER_QUERY_TIME_INTERVAL,     KEY_INTERVAL},
};

static std::map<sensor_recorder_data_e, std::string> data_keys = {
	{SENSOR_RECORDER_DATA_STEPS,              KEY_STEPS},
	{SENSOR_RECORDER_DATA_WALK_STEPS,         KEY_WALK_STEPS},
	{SENSOR_RECORDER_DATA_RUN_STEPS,          KEY_RUN_STEPS},
	{SENSOR_RECORDER_DATA_DISTANCE,           KEY_DISTANCE},
	{SENSOR_RECORDER_DATA_CALORIE,            KEY_CALORIES},
	{SENSOR_RECORDER_DATA_HEART_RATE,         ""},
	{SENSOR_RECORDER_DATA_SLEEP_STATE,        ""},
	{SENSOR_RECORDER_DATA_PRESSURE,           KEY_PRESSURE},
	{SENSOR_RECORDER_DATA_MAX_PRESSURE,       KEY_MAX_PRESSURE},
	{SENSOR_RECORDER_DATA_MIN_PRESSURE,       KEY_MIN_PRESSURE},
	{SENSOR_RECORDER_DATA_AVERAGE_PRESSURE,   KEY_AVG_PRESSURE}
};

static sensor_error_e convert_error(int error)
{
	switch (error) {
	case ERR_NONE:
	case ERR_INVALID_PARAMETER:
	case ERR_OUT_OF_MEMORY:
	case ERR_PERMISSION_DENIED:
	case ERR_NOT_SUPPORTED:
	case ERR_NO_DATA:
		return (sensor_error_e)error;
	case ERR_ALREADY_STARTED:
		return SENSOR_ERROR_NOT_AVAILABLE;
	default:
		break;
	}
	return SENSOR_ERROR_OPERATION_FAILED;
}

typedef struct {
	ctx::Json *json;
	int index;
} tuple_info;

typedef struct {
	sensor_type_e type;
	sensor_recorder_data_cb cb;
	void *user_data;
} callback_info;

class DBusListener : public ctx::IDBusClientListener {
public:
	void onPublish(std::string subject, int reqId, int error, ctx::Json event);
	void setCallbackInfo(int reqid, callback_info *info);

private:
	std::map<int, std::shared_ptr<callback_info>> infos;
};

void DBusListener::onPublish(std::string subject, int reqId, int error, ctx::Json event)
{
	bool ret = false;
	int size = 0;
	tuple_info data;

	{
		ctx::ScopeMutex sm(&info_mutex);
		if (infos.find(reqId) == infos.end())
			return;
	}

	ret = event.get(NULL, KEY_RESULT_SIZE, &size);

	if (!ret)
		return;

	if (size == 0) {
		infos[reqId]->cb(infos[reqId]->type, (sensor_recorder_data_h)&data, 0, SENSOR_ERROR_NO_DATA, infos[reqId]->user_data);
		goto CLEAN;
	}

	data.json = &event;

	for (int i = 0; i < size; ++i) {
		data.index = i;
		ret = infos[reqId]->cb(infos[reqId]->type, (sensor_recorder_data_h)&data, (size - (i + 1)), convert_error(error), infos[reqId]->user_data);

		if (!ret)
			break;
	}

CLEAN:
	_D("Succeeded to call DBusListener::onPublish() with reqId[%d]", reqId);

	infos.erase(reqId);
}

void DBusListener::setCallbackInfo(int reqId, callback_info *info)
{
	infos[reqId] = std::shared_ptr<callback_info>(info);
}

int sensor_recorder_is_supported(sensor_type_e type, bool *supported)
{
	int ret = SENSOR_ERROR_NONE;

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (!supported)
		return SENSOR_ERROR_INVALID_PARAMETER;

	ret = dbusClient.isSupported(sensor_keys[type]);

	if (ret == ERR_NONE)
		*supported = true;
	else if (ret == ERR_NOT_SUPPORTED)
		*supported = false;
	else
		return convert_error(ret);

	_D("sensor[%#x] is %s", type, (*supported ? "supported" : "not supported"));

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_start(sensor_type_e type, sensor_recorder_option_h option)
{
	int ret = SENSOR_ERROR_NONE;
	ctx::Json operation;

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;

	operation.set(NULL, KEY_OPERATION, VAL_START);

	if (option)
		operation.set(NULL, KEY_OPTION, *static_cast<ctx::Json *>(option));

	ret = dbusClient.write(sensor_keys[type], operation.str(), NULL);

	_D("Started to record sensor[%#x] data with operation : %s", type, operation.str().c_str());

	return convert_error(ret);
}

int sensor_recorder_stop(sensor_type_e type)
{
	int ret = SENSOR_ERROR_NONE;
	ctx::Json operation;

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;

	operation.set(NULL, KEY_OPERATION, VAL_STOP);

	ret = dbusClient.write(sensor_keys[type], operation.str(), NULL);

	_D("Stopped to record sensor[%#x] data with operation : %s", type, operation.str().c_str());

	return convert_error(ret);
}

int sensor_recorder_create_option(sensor_recorder_option_h *option)
{
	if (!option)
		return SENSOR_ERROR_INVALID_PARAMETER;

	*option = static_cast<sensor_recorder_option_h>(new(std::nothrow) ctx::Json());

	if (!*option) {
		_D("Failed to create option handle");
		return SENSOR_ERROR_OUT_OF_MEMORY;
	}

	_D("Created option handle[%p]", *option);

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_destroy_option(sensor_recorder_option_h option)
{
	if (!option)
		return SENSOR_ERROR_INVALID_PARAMETER;

	delete static_cast<ctx::Json *>(option);
	option = NULL;

	_D("Destroyed option handle");

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_option_set_int(sensor_recorder_option_h option, sensor_recorder_option_e attribute, int value)
{
	if (!option)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (attribute < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (option_keys.find(attribute) == option_keys.end())
		return SENSOR_ERROR_INVALID_PARAMETER;

	static_cast<ctx::Json *>(option)->set(NULL, option_keys[attribute].c_str(), value);

	_D("Set attribute[%d] with value[%d] to option[%p]", attribute, value, option);

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_create_query(sensor_recorder_query_h *query)
{
	if (!query)
		return SENSOR_ERROR_INVALID_PARAMETER;

	*query = static_cast<sensor_recorder_query_h>(new(std::nothrow) ctx::Json());

	if (!*query) {
		_D("Failed to create query handle");
		return SENSOR_ERROR_OUT_OF_MEMORY;
	}

	_D("Created query handle[%p]", *query);

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_destroy_query(sensor_recorder_query_h query)
{
	if (!query)
		return SENSOR_ERROR_INVALID_PARAMETER;

	delete static_cast<ctx::Json *>(query);
	query = NULL;

	_D("Destroyed query handle");

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_query_set_int(sensor_recorder_query_h query, sensor_recorder_query_e attribute, int value)
{
	if (!query)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (attribute < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (query_keys.find(attribute) == query_keys.end())
		return SENSOR_ERROR_INVALID_PARAMETER;

	static_cast<ctx::Json *>(query)->set(NULL, query_keys[attribute].c_str(), (int)value);

	_D("Set attribute[%d] with value[%d] to query[%p]", attribute, value, query);

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_query_set_time(sensor_recorder_query_h query, sensor_recorder_query_e attribute, time_t t)
{
	if (!query)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (attribute < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (query_keys.find(attribute) == query_keys.end())
		return SENSOR_ERROR_INVALID_PARAMETER;

	static_cast<ctx::Json *>(query)->set(NULL, query_keys[attribute].c_str(), (int64_t)t);

	_D("Set attribute[%d] with value[%ld] to query[%p]", attribute, t, query);

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_read(sensor_type_e type, sensor_recorder_query_h query, sensor_recorder_data_cb cb, void *user_data)
{
	int ret = SENSOR_ERROR_NONE;
	int reqId = 0;
	callback_info *info = NULL;

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (!query || !cb)
		return SENSOR_ERROR_INVALID_PARAMETER;

	/* Lazy creating listener */
	static DBusListener listener;

	dbusClient.addListener(sensor_keys[type], &listener);

	{
		ctx::ScopeMutex sm(&info_mutex);

		ret = dbusClient.read(sensor_keys[type], *static_cast<ctx::Json *>(query), &reqId, NULL);

		if (ret != SENSOR_ERROR_NONE)
			return convert_error(ret);

		info = new(std::nothrow) callback_info();
		if (!info) {
			_D("Failed to create callback info");
			return SENSOR_ERROR_OUT_OF_MEMORY;
		}

		info->type = type;
		info->cb = cb;
		info->user_data = user_data;

		listener.setCallbackInfo(reqId, info);
	}

	_D("succeeded to read sensor[%#x] data with query : %s", type, static_cast<ctx::Json *>(query)->str().c_str());

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_read_sync(sensor_type_e type, sensor_recorder_query_h query, sensor_recorder_data_cb cb, void *user_data)
{
	int ret = SENSOR_ERROR_NONE;
	int reqId = 0;
	int size = 0;
	ctx::Json output;
	tuple_info data;

	if (type <= SENSOR_ALL)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (!query || !cb)
		return SENSOR_ERROR_INVALID_PARAMETER;

	ret = dbusClient.readSync(sensor_keys[type], *static_cast<ctx::Json *>(query), &reqId, &output);

	if (ret != ERR_NONE)
		return convert_error(ret);

	ret = output.get(NULL, KEY_RESULT_SIZE, &size);

	if (!ret)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (size == 0)
		return SENSOR_ERROR_NO_DATA;

	data.json = &output;

	for (int i = 0; i < size; ++i) {
		data.index = i;
		ret = cb(type, (sensor_recorder_data_h)&data, (size - (i + 1)), SENSOR_ERROR_NONE, user_data);

		if (!ret)
			break;
	}

	_D("succeeded to read sensor[%#x] data with query : %s", type, static_cast<ctx::Json *>(query)->str().c_str());

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_data_get_time(sensor_recorder_data_h data, time_t *start_time, time_t *end_time)
{
	int64_t start = 0, end = 0;
	tuple_info *tuple = NULL;
	ctx::Json *json = NULL;

	if (!data || !start_time || !end_time)
		return SENSOR_ERROR_INVALID_PARAMETER;

	tuple = static_cast<tuple_info *>(data);
	json = tuple->json;

	if (!json)
		return SENSOR_ERROR_INVALID_PARAMETER;

	if (!json->getAt(NULL, KEY_START_TIME, tuple->index, &start))
		return SENSOR_ERROR_INVALID_PARAMETER;

	if (!json->getAt(NULL, KEY_END_TIME, tuple->index, &end))
		return SENSOR_ERROR_INVALID_PARAMETER;

	*start_time = static_cast<time_t>(start / 1000);
	*end_time = static_cast<time_t>(end / 1000);

	_D("Get start_time[%ld] and end_time[%ld] from data[%p]", *start_time, *end_time, data);

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_data_get_int(sensor_recorder_data_h data, sensor_recorder_data_e key, int *value)
{
	tuple_info *tuple = NULL;
	ctx::Json *json = NULL;

	if (!data || !value)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (key < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (data_keys.find(key) == data_keys.end())
		return SENSOR_ERROR_INVALID_PARAMETER;

	tuple = static_cast<tuple_info *>(data);
	json = tuple->json;

	if (!json)
		return SENSOR_ERROR_INVALID_PARAMETER;

	if (!json->getAt(NULL, data_keys[key].c_str(), tuple->index, value))
		return SENSOR_ERROR_INVALID_PARAMETER;

	_D("Get value[%d] from data[%p]", *value, data);

	return SENSOR_ERROR_NONE;
}

int sensor_recorder_data_get_double(sensor_recorder_data_h data, sensor_recorder_data_e key, double *value)
{
	tuple_info *tuple = NULL;
	ctx::Json *json = NULL;

	if (!data || !value)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (key < 0)
		return SENSOR_ERROR_INVALID_PARAMETER;
	if (data_keys.find(key) == data_keys.end())
		return SENSOR_ERROR_INVALID_PARAMETER;

	tuple = static_cast<tuple_info *>(data);
	json = tuple->json;

	if (!json)
		return SENSOR_ERROR_INVALID_PARAMETER;

	if (!json->getAt(NULL, data_keys[key].c_str(), tuple->index, value))
		return SENSOR_ERROR_INVALID_PARAMETER;

	_D("Get value[%f] from data[%p]", *value, data);

	return SENSOR_ERROR_NONE;
}
