/*
 * sensorctl
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
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
 *
 */

#pragma once // _SENSOR_TYPES_H_

#include "sensor_log.h"

#define NAME_MAX_TEST 32

struct sensor_info {
	sensor_type_e type;
	char sensor_name[NAME_MAX_TEST];
};

static struct sensor_info sensors[] = {
	{SENSOR_ALL, 						"all"},

	// General Sensors
	{SENSOR_ACCELEROMETER,				"accelerometer"},
	{SENSOR_GRAVITY,					"gravity"},
	{SENSOR_LINEAR_ACCELERATION,		"linear_accel"},
	{SENSOR_MAGNETIC,					"magnetic"},
	{SENSOR_ROTATION_VECTOR,			"rotation_vector"},
	{SENSOR_ORIENTATION,				"orientation", },
	{SENSOR_GYROSCOPE,					"gyroscope", },
	{SENSOR_LIGHT, 						"light", },
	{SENSOR_PROXIMITY, 					"proximity", },
	{SENSOR_PRESSURE, 					"pressure", },
	{SENSOR_TEMPERATURE, 				"temperature", },
	{SENSOR_HUMIDITY,					"humidity", },
	{SENSOR_HRM,						"hrm", },
	{SENSOR_HRM_LED_GREEN,				"hrm_led_green",},
	{SENSOR_HRM_LED_IR,					"hrm_led_ir",},
	{SENSOR_HRM_LED_RED,				"hrm_led_red", },
	{SENSOR_GYROSCOPE_ROTATION_VECTOR,	"gyroscope_rotation_vector", },

	// Gesture Sensors
	{SENSOR_GESTURE_WRIST_UP,			"wristup"},
};

static void usage_sensors(void)
{
	PRINT("The sensor types are:\n");
	int cnt_sensor = sizeof(sensors) / sizeof(struct sensor_info);

	for (int i=0; i<cnt_sensor; ++i)
		PRINT("  %d:\t %s\n", sensors[i].type, sensors[i].sensor_name);

	PRINT("\n");
}

static int get_index_by_name(char *name)
{
	int sensor_index;
	int sensor_count = sizeof(sensors) / sizeof(struct sensor_info);
	for (sensor_index=0; sensor_index<sensor_count; ++sensor_index) {
		if (!strcmp(sensors[sensor_index].sensor_name, name))
			break;
	}

	if (sensor_index == sensor_count) {
		PRINT(KRED"ERROR: sensor name is wrong"RESET"\n");
		usage_sensors();
		return -1;
	}
	return sensor_index;
}


static int get_index_by_type(sensor_type_e type)
{
	int sensor_index;
	int sensor_count = sizeof(sensors) / sizeof(struct sensor_info);
	for (sensor_index=0; sensor_index<sensor_count; ++sensor_index) {
		if (sensors[sensor_index].type == type)
			break;
	}

	if (sensor_index == sensor_count) {
		PRINT(KRED"ERROR: sensor name is wrong"RESET"\n");
		return -1;
	}
	return sensor_index;
}
