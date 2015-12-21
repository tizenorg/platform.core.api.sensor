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

inject_manager::inject_manager()
{
}

inject_manager::~inject_manager()
{
}

bool injector_manager::set_data(int argc, char *argv[])
{

}

bool injector_manager::inject(int argc, char *argv[])
{
	set_data(argc, argv);

	return true;
}

void inject_manager::usage(void)
{
	PRINT("usage: sensorctl inject <sensor_type> [<event_type>] [options]\n");
	PRINT("\n");

	usage_sensors();
}

