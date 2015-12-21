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

#include <glib.h>
#include <sensor.h>
#include "../sensor_log.h"
#include "../sensor_types.h"

info_manager::info_manager()
{
}

info_manager::~info_manager()
{
}

bool info_manager::info(int argc, char *argv[])
{
	int sensor_index;

	if (argc == 2) {
		usage();
		return false;
	}

	if ((sensor_index = get_index_by_name(argv[2])) < 0)
		return false;

	sensor_h *sensors;
	int cnt;
	sensor_get_sensor_list(sensors[sensor_index].type, &sensors, cnt);

	sensor_info(sensors, cnt);
	
	free(sensors);
	return true;
}

void info_manager::sensor_info(sensor_h *sensors, int cnt)
{
	sensor_h sensor;
	char *vendor;
	char *name;
	float min_range;
	float max_range;
	float resolution;
	int min_interval;
	int fifo_count;
	int max_batch_count;
	
	for (int i=0; i<cnt; ++i) {
		sensor = sensors[i];

		sensor_get_name(sensor, &name);
		sensor_get_vendor(sensor, &vendor);
		sensor_get_max_range(sensor, &max_range);
		sensor_get_min_range(sensor, &min_range);
		sensor_get_resolution(sensor, &resolution);
		sensor_get_min_interval(sensor, &min_interval);
		sensor_get_fifo_count(sensor, &fifo_count);
		sensor_get_max_batch_count(sensor, &max_batch_count);

		PRINT("-------sensor[%d] information-------\n", i);
		PRINT("vendor : %s\n", vendor);
		PRINT("name : %s\n", name);
		PRINT("min_range : %f\n", min_range);
		PRINT("max_range : %f\n", max_range);
		PRINT("resolution : %f\n", resolution);
		PRINT("min_interval : %d\n", min_interval);
		PRINT("fifo_count : %d\n", fifo_count);
		PRINT("max_batch_count : %d\n", max_batch_count);
		PRINT("--------------------------------\n");
	}
}

void info_manager::usage(void)
{
	PRINT("usage: sensorctl info <sensor_type>\n");
	PRINT("\n");

	usage_sensors();
}

