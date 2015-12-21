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

#pragma once // _INJECTOR_H_

struct dbus_event_info {
	int sensor_type;
	char event_name[NAME_MAX_TEST];
	char bus_path[NAME_MAX_TEST];
	char object_path[NAME_MAX_TEST];
	char event_path[NAME_MAX_TEST];
	int command;
};

class injector_interface {
public:
	virtual bool init() = 0;
	virtual bool inject() = 0;
};
