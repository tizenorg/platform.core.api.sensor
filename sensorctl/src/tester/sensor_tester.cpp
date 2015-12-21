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

#include <sensor.h>
#include "../sensor_log.h"
#include "../sensor_types.h"

sensor_tester::sensor_tester()
{
}

sensor_tester::~sensor_tester()
{
}

void test_cb(sensor_h sensor, sensor_event_s *event, void *user_data)
{
	sensor_type_e type;
	sensor_get_type(sensor, &type);
	int i;
	int sensor_index;

	int *cnt_event;
	cnt_event = (int *)user_data;

	if (check_loop++ >= *cnt_event) {
		if (mainloop) {
			g_main_loop_quit(mainloop);
			g_main_loop_unref(mainloop);
		}
		mainloop = NULL;
		return;
	}

	PRINT("[%llu] ", event->timestamp);

	int sensor_count = sizeof(sensors) / sizeof(struct sensor_info);
	for (sensor_index=0; sensor_index<sensor_count; ++sensor_index) {
		if (sensors[sensor_index].type == type)
			break;
	}

	PRINT("%s:", sensors[sensor_index].sensor_name);

	for (i=0; i<event->value_count; ++i)
		PRINT(" [%f]", event->values[i]);
	PRINT("\n");
}

void test_sensor(sensor_type_e type, int interval, int latency, int cnt_test, int cnt_event)
{
	sensor_h sensor;
	sensor_listener_h listener;
	bool is_supported;
	int ret;
	int count = 0;

	while (count++ < cnt_test) {
		mainloop = g_main_loop_new(NULL, FALSE);
		check_loop = 0;

		ret = sensor_is_supported(type, &is_supported);
		PRINT("sensor_is_supported[%s] : %d\n", err_str(ret), is_supported);

		ret = sensor_get_default_sensor(type, &sensor);
		PRINT("sensor_get_default_sensor[%s] : %p\n", err_str(ret), sensor);

		ret = sensor_create_listener(sensor, &listener);
		PRINT("sensor_cate_listener ret[%s] : %p\n", err_str(ret), listener);

		ret = sensor_listener_set_event_cb(listener, interval, test_cb, (void *)&cnt_event);
		PRINT("sensor_listener_set_event_cb[%s]\n", err_str(ret));

		//ret = sensor_listener_set_accuracy_cb(listener, test_accuracy_cb, NULL);
		//PRINT("sensor_listener_set_accuracy_cb : %d\n",ret);

		ret = sensor_listener_set_interval(listener, interval);
		PRINT("sensor_listener_set_interval[%s] : %d ms\n", err_str(ret), interval);

		ret = sensor_listener_start(listener);
		PRINT("sensor_listener_start[%s]\n", err_str(ret));

		ret = sensor_listener_set_option(listener, SENSOR_OPTION_ALWAYS_ON);
		PRINT("sensor_listener_set_option[%s]\n", err_str(ret));

		sensor_event_s event;

		ret = sensor_listener_read_data(listener, &event);
		PRINT("sensor_listener_read_data[%s] :", err_str(ret));

		for (int i=0; i<event.value_count; ++i)
			PRINT(" [%f]", event.values[i]);
		PRINT("\n");

		g_main_loop_run(mainloop);

		ret = sensor_listener_stop(listener);
		PRINT("sensor_listener_stop[%s]\n", err_str(ret));
	}

	ret = sensor_listener_unset_event_cb(listener);
	PRINT("sensor_listener_unset_event_cb[%s]\n", err_str(ret));

	ret = sensor_destroy_listener(listener);
	PRINT("sensor_destroy_listener[%s]\n", err_str(ret));
}

void test(int argc, char *argv[])
{
	if (argc == 2) {
		usage_test();
		return;
	}

	if (argc > 2) {
		if (!strcmp(argv[2], "help")) {
			usage_test();
			return;
		}

		if (!strcmp(argv[2], "all")) {
			auto_test();
			return;
		}

		int interval = DEFAULT_INTERVAL;
		int latency = DEFAULT_LATENCY;
		int cnt_test = DEFAULT_TEST_COUNT;
		int cnt_event = DEFAULT_EVENT_COUNT;

		int sensor_index;
		int sensor_count = sizeof(sensors) / sizeof(sensor_type_e);
		for (sensor_index=0; sensor_index<sensor_count; ++sensor_index) {
			if (!strcmp(sensors[sensor_index].sensor_name, argv[2]))
				break;
		}

		if (sensor_index == sensor_count) {
			PRINT("ERROR: sensor name is wrong\n");
			usage_sensors();
			return;
		}

		if (argc >= 4)
			interval = atoi(argv[3]);

		if (argc >= 5)
			cnt_test = atoi(argv[4]);

		if (argc >= 6)
			cnt_event = atoi(argv[5]);

		PRINT("%d %d %d\n", interval, cnt_test, cnt_event);

		test_sensor(sensors[sensor_index].type, interval, latency, cnt_test, cnt_event);
	}
}

