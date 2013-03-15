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
#include <sensors.h>

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

int main(int argc, char *argv[])
{
	int err;
    sensor_type_e type;
    bool is_supported;
    char* supported_msg;
	
    for(type=0; type<=SENSOR_MOTION_FACEDOWN; type++){
        err = sensor_is_supported(type, &is_supported);

        supported_msg = err < 0 ? "error" : (is_supported ? "support" : "not support");

        printf("%d : %s [%s]\n", type, TYPE_NAME[type], supported_msg);
    }
    return 0;

}
