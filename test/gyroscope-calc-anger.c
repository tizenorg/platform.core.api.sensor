/*
 * 
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 * PROPRIETARY/CONFIDENTIAL
 * 
 * This software is the confidential and proprietary information of SAMSUNG 
 * ELECTRONICS ("Confidential Information"). You agree and acknowledge that 
 * this software is owned by Samsung and you shall not disclose such 
 * Confidential Information and shall use it only in accordance with the terms 
 * of the license agreement you entered into with SAMSUNG ELECTRONICS. SAMSUNG 
 * make no representations or warranties about the suitability of the software, 
 * either express or implied, including but not limited to the implied 
 * warranties of merchantability, fitness for a particular purpose, or 
 * non-infringement. SAMSUNG shall not be liable for any damages suffered by 
 * licensee arising out of or related to this software.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <sensors.h>
#include <time.h>

struct xyz_axis {
    float x,y,z;
};

static struct xyz_axis angles = {0,0,0};
static time_t timestamp = 0;

static GMainLoop *mainloop;

static void test_gyroscope_cb(sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data)
{
    time_t current_timestamp = time(0);
    if(timestamp != 0){
        const float dT = difftime(current_timestamp, timestamp);
        angles.x += x * dT;
        angles.y += y * dT;
        angles.z += z * dT;
        printf("angle x=%f y=%f z=%f\n", angles.x, angles.y, angles.z);
    }
    timestamp = current_timestamp;
}

static void sig_quit(int signo)
{
	if(mainloop)
	{
		g_main_loop_quit(mainloop);
	}
}

int main(int argc, char *argv[])
{
	int type = SENSOR_GYROSCOPE;
	sensor_h handle;
    bool is_supported;
	
	float max = 0, min = 0, res = 0;

	if(sensor_is_supported(type, &is_supported) != SENSOR_ERROR_NONE){
		printf("unknown error\n");
		return 0;
	}
    if(!is_supported){
		printf("unsupported sensor\n");
		return 0;
    }

	signal(SIGINT, sig_quit);
	signal(SIGTERM, sig_quit);
	signal(SIGQUIT, sig_quit);

	mainloop = g_main_loop_new(NULL, FALSE);

	if(sensor_get_spec(type, &max, &min, &res) == SENSOR_ERROR_NONE){
		printf("max=%f, min=%f, res=%f\n", max, min, res);
    }else{
        printf("Error!!!!\n");
    }

	sensor_create(&handle);

    sensor_gyroscope_set_cb(handle, 0, test_gyroscope_cb, NULL);

	if(sensor_start(handle, type) == SENSOR_ERROR_NONE)
		printf("Success start \n");

	g_main_loop_run(mainloop);
	g_main_loop_unref(mainloop);

    sensor_gyroscope_unset_cb(handle);

	if(sensor_stop(handle, type) == SENSOR_ERROR_NONE)
		printf("Success stop \n");

	sensor_destroy(handle);
	return 0;
}
