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
#include <math.h>

#define RADIAN_VALUE (57.2957)
#define PITCH_MIN       35
#define PITCH_MAX       145


static GMainLoop *mainloop;

const float Alpha = 0.8;

struct three_axis_s{
    float x,y,z;
};

struct three_axis_s gravitys = {0,0,0};
struct three_axis_s linear_accelation = {0,0,0};

enum {
    ROTATE_0,
    ROTATE_90,
    ROTATE_180,
    ROTATE_270,
    ROTATE_ERROR
};

static int current_rotate = -1;

static void test_accelerometer_cb(sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data)
{
    double atan_v, norm_z, raw_z;
    int acc_theta, acc_pitch;
    int rotate;

    atan_v = atan2(y, x);
    acc_theta = (int)(atan_v * (RADIAN_VALUE) + 270)%360;
    raw_z = (double)(z/(0.004 * 9.81));

    if(raw_z > 250){
        norm_z = 1.0;
    }else if(raw_z < -250){
        norm_z = -1.0;
    }else{
        norm_z = ((double)raw_z)/250;
    }

    acc_pitch = (int)( acos(norm_z) *(RADIAN_VALUE));

    if( (acc_pitch>35) && (acc_pitch<145) ) {
        if ((acc_theta >= 315 && acc_theta <=359) || (acc_theta >=0 && acc_theta < 45)){
            rotate = ROTATE_0;
        }
        else if(acc_theta >= 45 && acc_theta < 135){
            rotate = ROTATE_90;
        }
        else if(acc_theta >=135 && acc_theta < 225){
            rotate = ROTATE_180;
        }
        else if(acc_theta >=225 && acc_theta < 315){
            rotate = ROTATE_270;
        }
        else {
            rotate = ROTATE_ERROR;
        }
    }else{
        rotate = ROTATE_ERROR;
    }

    if(rotate != ROTATE_ERROR && current_rotate != rotate){
        current_rotate = rotate;
        printf("rotation is %d\n", rotate * 90);
    }
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
	int type = SENSOR_ACCELEROMETER;
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

    sensor_accelerometer_set_cb(handle, 0, test_accelerometer_cb, NULL);

	if(sensor_start(handle, type) == SENSOR_ERROR_NONE)
		printf("Success start \n");

	g_main_loop_run(mainloop);
	g_main_loop_unref(mainloop);

    sensor_accelerometer_unset_cb(handle);

	if(sensor_stop(handle, type) == SENSOR_ERROR_NONE)
		printf("Success stop \n");

	sensor_destroy(handle);
	return 0;
}
