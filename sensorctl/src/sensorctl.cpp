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

#include <stdio.h>
#include <stdlib.h>
#include <sensor.h>
#include <string.h>
#include <glib.h>
#include <signal.h>
#include <gio/gio.h>

#include "sensor_log.h"
#include "tester/tester_manager.h"
#include "injector/injector_manager.h"
#include "info/info_manager.h"

static void good_bye(void)
{
	PRINT("\n"KRED"Good-Bye"RESET"\n");
}

static void signal_handler(int signo)
{
	PRINT("\n"KRED"Received SIGNAL(%d)"RESET"\n", signo);
	exit(EXIT_SUCCESS);

	return;
}

void usage(void)
{
	PRINT("usage: sensorctl <command> <sensor_type> [<args>]\n");

	PRINT("The sensorctl commands are:\n");
	PRINT("  info : print sensor infos\n");
	PRINT("  test : test sensor(s)\n");
	PRINT("  inject : inject the event to sensor\n");
	PRINT("\n");
}

int main(int argc, char *argv[])
{
	atexit(good_bye);

	signal(SIGINT,  signal_handler);
	signal(SIGHUP,  signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGABRT, signal_handler);

	if (argc < 2) {
		usage();
		return 0;
	}

	if (!strcmp(argv[1], "test")) {
		tester_manager manager;// = tester_manager();
		manager.test(argc, argv);
	} else if (!strcmp(argv[1], "inject")) {
		injector_manager manager;// = injector_manager();
		manager.inject(argc, argv);
	} else if (!strcmp(argv[1], "info")) {
		info_manager manager;// = info_manager();
		manager.info(argc, argv);
	} else {
		usage();
		return 0;
	}

	return 0;
}
