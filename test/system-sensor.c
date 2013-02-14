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

static GMainLoop *mainloop;

static char* TYPE_NAME[] = {
	"ACCELEROMETER",
	"MAGNETIC",
	"ORIENTATION",
	"GYROSCOPE",
	"LIGHT",
	"PROXIMITY",
	"MOTION_SNAP",
	"MOTION_SHAKE",
	"MOTION_DOUBLETAP",
	"MOTION_PANNING",
	"MOTION_FACEDOWN"
};

static char* SNAP[] = {
	"NONE",
    "LEFT",
    "RIGHT"
};

static char* SHAKE[] = {
	"NONE",
	"DETECTION",
	"CONTINUING",
	"FINISH",
	"BREAK"
};

static void test_calibration_cb(void *user_data)
{
    char* xx = (char*)user_data;
	printf("%s sensor is calibration needed!!!!!!!!!!!!!!!!!!\n", xx);
}

static void test_accelerometer_cb(sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data)
{
	printf("ACCELEROMETER sensor acc=%d x=%f y=%f z=%f\n", accuracy, x, y, z);
}

static void test_magnetic_cb(sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data)
{
	printf("MAGNETIC sensor acc=%d x=%f y=%f z=%f\n", accuracy, x, y, z);
}

static void test_orientation_cb(sensor_data_accuracy_e accuracy, float azimuth, float pitch, float roll, void *user_data)
{
	printf("ORIENTATION sensor acc=%d azimuth=%f pitch=%f roll=%f\n", accuracy, azimuth, pitch, roll);
}

static void test_gyroscope_cb(sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data)
{
	printf("GYROSCOPE sensor acc=%d x=%f y=%f z=%f\n", accuracy, x, y, z);
}

static void test_light_cb(sensor_data_accuracy_e accuracy, float lux, void *user_data)
{
	printf("LIGHT sensor acc=%d lux=%f\n", accuracy, lux);
}

static void test_proximity_cb(sensor_data_accuracy_e accuracy, float distance, void *user_data)
{
	printf("PROXIMITY sensor distance = %fcm\n", distance);
}

static void test_motion_snap_cb        (sensor_motion_snap_e snap, void *user_data)
{
	printf("MOTION_SNAP [%s]\n", SNAP[snap]);
}

static void test_motion_shake_cb       (sensor_motion_shake_e shake, void *user_data)
{
	printf("MOTION_SHAKE [%s]\n", SHAKE[shake]);
}

static void test_motion_doubletap_cb   (void *user_data)
{
	printf("MOTION_DOUBLETAP \n");
}

static void test_motion_panning_cb (int x, int y, void *user_data)
{
	printf("MOTION_PANNING x=[%5d] y=[%5d]\n", x, y);
}

static void test_motion_facedown_cb (void *user_data)
{
	printf("MOTION_FACEDOWN \n");
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
	int i;
	int type;
	sensor_h handle;
    bool is_supported;
	
	float max = 0, min = 0, res = 0;

	if(argc < 2)
	{
		printf("input sensor type\n");
		for(i=0; i<=SENSOR_MOTION_FACEDOWN; i++){
			printf("%d : %s\n", i, TYPE_NAME[i]);
		}
		return 0;
	}

	type = atoi(argv[1]);
    /*
	if(sensor_is_supported(type, &is_supported) != SENSOR_ERROR_NONE){
		printf("unknown error\n");
		return 0;
	}
    if(!is_supported){
		printf("unsupported sensor\n");
		return 0;
    }
    */

    if(type < 0 || type > SENSOR_MOTION_FACEDOWN)
		printf("unknown sensor!\n");
    else
		printf("selected sensor is (%d)%s\n", type, TYPE_NAME[type]);

	signal(SIGINT, sig_quit);
	signal(SIGTERM, sig_quit);
	signal(SIGQUIT, sig_quit);

	mainloop = g_main_loop_new(NULL, FALSE);


    if(type < SENSOR_MOTION_SNAP){
        if(sensor_get_spec(type, &max, &min, &res) == SENSOR_ERROR_NONE){
            printf("max=%f, min=%f, res=%f\n", max, min, res);
        }else{
            printf("Error!!!!\n");
        }
    }

	sensor_create(&handle);

	switch(type){
		case SENSOR_ACCELEROMETER:
			sensor_accelerometer_set_cb(handle, 0, test_accelerometer_cb, TYPE_NAME[type]);
			break;
		case SENSOR_MAGNETIC:
			sensor_magnetic_set_cb(handle, 0, test_magnetic_cb, TYPE_NAME[type]);
			sensor_magnetic_set_calibration_cb(handle, test_calibration_cb, TYPE_NAME[type]);
			break;
		case SENSOR_ORIENTATION:
			sensor_orientation_set_cb(handle, 0, test_orientation_cb, TYPE_NAME[type]);
			sensor_orientation_set_calibration_cb(handle, test_calibration_cb, TYPE_NAME[type]);
			break;
		case SENSOR_GYROSCOPE:
			sensor_gyroscope_set_cb(handle, 0, test_gyroscope_cb, TYPE_NAME[type]);
			break;
		case SENSOR_LIGHT:
			sensor_light_set_cb(handle, 0, test_light_cb, TYPE_NAME[type]);
			break;
		case SENSOR_PROXIMITY:
			sensor_proximity_set_cb(handle, 0, test_proximity_cb, TYPE_NAME[type]);
			break;
		case SENSOR_MOTION_SNAP:
			sensor_motion_snap_set_cb(handle, test_motion_snap_cb, TYPE_NAME[type]);
			break;
		case SENSOR_MOTION_SHAKE:
			sensor_motion_shake_set_cb(handle, test_motion_shake_cb, TYPE_NAME[type]);
			break;
		case SENSOR_MOTION_DOUBLETAP:
			sensor_motion_doubletap_set_cb(handle, test_motion_doubletap_cb, TYPE_NAME[type]);
			break;
		case SENSOR_MOTION_PANNING:
            sensor_motion_panning_set_cb(handle, test_motion_panning_cb, TYPE_NAME[type]);
			break;
		case SENSOR_MOTION_FACEDOWN:
            sensor_motion_facedown_set_cb(handle, test_motion_facedown_cb, TYPE_NAME[type]);
			break;
		default:
			goto _ending;
	}

    printf("Success register callback \n");

	if(sensor_start(handle, type) == SENSOR_ERROR_NONE)
		printf("Success start \n");

	g_main_loop_run(mainloop);
	g_main_loop_unref(mainloop);

	switch(type){
		case SENSOR_ACCELEROMETER:
            sensor_accelerometer_unset_cb(handle);
			break;
		case SENSOR_MAGNETIC:
            sensor_magnetic_unset_calibration_cb(handle);
            sensor_magnetic_unset_cb(handle);
			break;
		case SENSOR_ORIENTATION:
			sensor_orientation_unset_calibration_cb(handle);
            sensor_orientation_unset_cb(handle);
			break;
		case SENSOR_GYROSCOPE:
            sensor_gyroscope_unset_cb(handle);
			break;
		case SENSOR_LIGHT:
            sensor_light_unset_cb(handle);
			break;
		case SENSOR_PROXIMITY:
            sensor_proximity_unset_cb(handle);
			break;
		case SENSOR_MOTION_SNAP:
            sensor_motion_snap_unset_cb(handle);
			break;
		case SENSOR_MOTION_SHAKE:
            sensor_motion_shake_unset_cb(handle);
			break;
		case SENSOR_MOTION_DOUBLETAP:
            sensor_motion_doubletap_unset_cb(handle);
			break;
		case SENSOR_MOTION_PANNING:
            sensor_motion_panning_unset_cb(handle);
			break;
		case SENSOR_MOTION_FACEDOWN:
            sensor_motion_facedown_unset_cb(handle);
			break;

		default:
			goto _ending;
	}

	if(sensor_stop(handle, type) == SENSOR_ERROR_NONE)
		printf("Success stop \n");

_ending:
	sensor_destroy(handle);
	return 0;
}
