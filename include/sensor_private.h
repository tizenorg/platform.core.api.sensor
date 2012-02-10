/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
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
 */




#ifndef __SENSOR_PRIVATE_H__
#define __SENSOR_PRIVATE_H__

#ifdef __cplusplus
extern "C"
{
#endif

enum _sensor_ids_index{
    ID_ACCELEOMETER, 
    ID_GEOMAGNETIC,
    ID_GYROSCOPE,
    ID_LIGHT,
    ID_PROXIMITY,
    ID_MOTION,
    ID_NUMBERS
};

#define CB_NUMBERS (SENSOR_MOTION_FACEDOWN+1)
#define CALIB_CB_NUMBERS (SENSOR_ORIENTATION+1)

struct sensor_handle_s {
	int ids[ID_NUMBERS];
//	sensor_type_e type;
    int started[CB_NUMBERS];
	void* cb_func[CB_NUMBERS];
	void* cb_user_data[CB_NUMBERS];
	
	void* calib_func[CALIB_CB_NUMBERS];
	void* calib_user_data[CALIB_CB_NUMBERS];
};

#define SENSOR_INIT(handle) \
    do { \
        handle->ids[ID_ACCELEOMETER] = -1; \
        handle->ids[ID_GEOMAGNETIC] = -1; \
        handle->ids[ID_GYROSCOPE] = -1; \
        handle->ids[ID_LIGHT] = -1; \
        handle->ids[ID_PROXIMITY] = -1; \
        handle->ids[ID_MOTION] = -1; \
        handle->started[SENSOR_ACCELEROMETER] = 0; \
        handle->started[SENSOR_MAGNETIC] = 0; \
        handle->started[SENSOR_ORIENTATION] = 0; \
        handle->started[SENSOR_GYROSCOPE] = 0; \
        handle->started[SENSOR_LIGHT] = 0; \
        handle->started[SENSOR_PROXIMITY] = 0; \
        handle->started[SENSOR_MOTION_SNAP] = 0; \
        handle->started[SENSOR_MOTION_SHAKE] = 0; \
        handle->started[SENSOR_MOTION_DOUBLETAP] = 0; \
        handle->started[SENSOR_MOTION_PANNING] = 0; \
        handle->started[SENSOR_MOTION_FACEDOWN] = 0; \
        handle->cb_func[SENSOR_ACCELEROMETER] = NULL; \
        handle->cb_func[SENSOR_MAGNETIC] = NULL; \
        handle->cb_func[SENSOR_ORIENTATION] = NULL; \
        handle->cb_func[SENSOR_GYROSCOPE] = NULL; \
        handle->cb_func[SENSOR_LIGHT] = NULL; \
        handle->cb_func[SENSOR_PROXIMITY] = NULL; \
        handle->cb_func[SENSOR_MOTION_SNAP] = NULL; \
        handle->cb_func[SENSOR_MOTION_SHAKE] = NULL; \
        handle->cb_func[SENSOR_MOTION_DOUBLETAP] = NULL; \
        handle->cb_func[SENSOR_MOTION_PANNING] = NULL; \
        handle->cb_func[SENSOR_MOTION_FACEDOWN] = NULL; \
        handle->cb_user_data[SENSOR_ACCELEROMETER] = NULL; \
        handle->cb_user_data[SENSOR_MAGNETIC] = NULL; \
        handle->cb_user_data[SENSOR_ORIENTATION] = NULL; \
        handle->cb_user_data[SENSOR_GYROSCOPE] = NULL; \
        handle->cb_user_data[SENSOR_LIGHT] = NULL; \
        handle->cb_user_data[SENSOR_PROXIMITY] = NULL; \
        handle->cb_user_data[SENSOR_MOTION_SNAP] = NULL; \
        handle->cb_user_data[SENSOR_MOTION_SHAKE] = NULL; \
        handle->cb_user_data[SENSOR_MOTION_DOUBLETAP] = NULL; \
        handle->cb_user_data[SENSOR_MOTION_PANNING] = NULL; \
        handle->cb_user_data[SENSOR_MOTION_FACEDOWN] = NULL; \
		handle->calib_func[SENSOR_ACCELEROMETER] = NULL; \
		handle->calib_func[SENSOR_MAGNETIC] = NULL; \
		handle->calib_func[SENSOR_ORIENTATION] = NULL; \
		handle->calib_user_data[SENSOR_ACCELEROMETER] = NULL; \
		handle->calib_user_data[SENSOR_MAGNETIC] = NULL; \
		handle->calib_user_data[SENSOR_ORIENTATION] = NULL; \
    }while(0) \


#ifdef __cplusplus
}
#endif

#endif // __SENSOR_PRIVATE_H__ 
