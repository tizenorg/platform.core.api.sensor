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

#define DEFAULT_INTERVAL 100
#define DEFAULT_LATENCY 0
#define DEFAULT_TEST_COUNT 1
#define DEFAULT_EVENT_COUNT 9999

test_manager::test_manager()
{
}

test_manager::~test_manager()
{

}

bool test_manager::set_data(int argc, char *argv[])
{
}

bool test_manager::test(int argc, char *argv[])
{
	set_data(argc, argv);

	return true;
}

void test_manager::usage(void)
{
	PRINT("usage: sensorctl test <sensor_type> [interval] [count]\n");
	PRINT("\n");

	usage_sensors();

	PRINT("interval_ms:\n");
	PRINT("  If no value for sensor is entered default value is 100ms.\n");
	PRINT("\n");

	PRINT("test count(n):\n");
	PRINT("  test sensors in n times, default is 1.\n");
	PRINT("\n");

	PRINT("event count(n):\n");
	PRINT("  test sensors in n times, default is 9999(infinitly).\n");
	PRINT("\n");
}

