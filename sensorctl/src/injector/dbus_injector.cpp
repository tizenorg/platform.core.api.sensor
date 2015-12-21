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

#define SENSORD_BUS_NAME            "org.tizen.system.sensord"
#define SENSORD_OBJECT_PATH         "/Org/Tizen/System/SensorD"
#define SENSORD_INTERFACE_NAME      SENSORD_BUS_NAME
#define WRISTUP_ALGO                "algo"

struct dbus_event_info {
	int sensor_type;
	char event_name[NAME_MAX_TEST];
	char bus_path[NAME_MAX_TEST];
	char object_path[NAME_MAX_TEST];
	char event_path[NAME_MAX_TEST];
	int command;
};

static struct dbus_event_info dbus_events[] = {
	{SENSOR_GESTURE_WRIST_UP, "auto",
		SENSORD_BUS_NAME, SENSORD_OBJECT_PATH, WRISTUP_ALGO, 0},
	{SENSOR_GESTURE_WRIST_UP, "green",
		SENSORD_BUS_NAME, SENSORD_OBJECT_PATH, WRISTUP_ALGO, 1},
	{SENSOR_GESTURE_WRIST_UP, "purple",
		SENSORD_BUS_NAME, SENSORD_OBJECT_PATH, WRISTUP_ALGO, 2},
	{SENSOR_GESTURE_WRIST_UP, "red",
		SENSORD_BUS_NAME, SENSORD_OBJECT_PATH, WRISTUP_ALGO, 3}
};

dbus_injector::dbus_injector()
	: m_connection(NULL)
{
#ifndef GLIB_VERSION_2_36
	g_type_init();
#endif
}

dbus_injector::~dbus_injector()
{
	if (m_connection) {
		g_dbus_connection_close_sync(m_connection, NULL, NULL);
		g_object_unref(m_connection);
		m_connection = NULL;
	}
}

bool dbus_injector::dbus_init()
{
	GError *error = NULL;
	gchar *gaddr;

	gaddr = g_dbus_address_get_for_bus_sync(G_BUS_TYPE_SYSTEM, NULL, &error);

	if (!gaddr) {
		PRINT("Failed to get dbus address : %s", error->message);
		g_error_free(error);
		error = NULL;
		return false;
	}

	m_connection = g_dbus_connection_new_for_address_sync(gaddr,
			(GDBusConnectionFlags)(G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT
			| G_DBUS_CONNECTION_FLAGS_MESSAGE_BUS_CONNECTION),
			NULL, NULL, &error);
	g_free(gaddr);

	if (!m_connection) {
		PRINT("Failed to get dbus connection : %s", error->message);
		g_error_free(error);
		error = NULL;
		return false;
	}

	PRINT("G-DBUS connected[%s]\n",
			g_dbus_connection_get_unique_name(m_connection));
}

bool dbus_injector::init(int argc, char *argv[])
{
	int sensor_index;
	if ((sensor_index = get_index_by_name(argv[2])) < 0)
		return false;

	int count_event = sizeof(dbus_events)/sizeof(dbus_event_info);

	for (int i=0; i<count_event; ++i) {
		if (sensors[sensor_index].type == dbus_events[i].sensor_type) {
			if (!strcmp(dbus_events[i].event_name, argv[3])) {
				event_num = i;
				return true;
			}
		}
	}

	return false;
}

bool dbus_injector::inject()
{
	g_dbus_connection_call(m_connection,
			dbus_events[event].bus_path, dbus_events[event].object_path, 
			dbus_events[event].bus_path, dbus_events[event].event_path,
			g_variant_new("(i)", command), NULL, G_DBUS_CALL_FLAGS_NONE, -1, NULL, NULL, NULL);

	return true;
}

