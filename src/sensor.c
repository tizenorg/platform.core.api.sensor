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




#include <stdlib.h>
#include <string.h>

#include <sensor.h>
#include <sensor_accel.h>
#include <sensor_geomag.h>
#include <sensor_light.h>
#include <sensor_proxi.h>
#include <sensor_motion.h>
#include <sensor_gyro.h>
#include <sensors.h>
#include <sensor_private.h>
#include <dlog.h>

#define _DEBUG 1

#ifdef _DEBUG
#undef LOG_TAG
#define LOG_TAG "TIZEN_SYSTEM_SENSOR"
#include <stdio.h>
#include <libgen.h>
static char* _DONT_USE_THIS_ARRAY_DIRECTLY[] = {
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

#define _MSG_SENSOR_ERROR_IO_ERROR "Io Error"
#define _MSG_SENSOR_ERROR_INVALID_PARAMETER "Invalid Parameter"
#define _MSG_SENSOR_ERROR_OUT_OF_MEMORY "Out of Memory"
#define _MSG_SENSOR_ERROR_NOT_NEED_CALIBRATION "Not need calibration"
#define _MSG_SENSOR_ERROR_NOT_SUPPORTED "Not supported"
#define _MSG_SENSOR_ERROR_OPERATION_FAILED "Operation failed"

#define TYPE_NAME(type) _DONT_USE_THIS_ARRAY_DIRECTLY[type]

#define DEBUG_PRINT(txt) LOGD("%s : " txt, __FUNCTION__)
#define DEBUG_PRINTF(fmt, ...) LOGD("%s : " fmt, __FUNCTION__, __VA_ARGS__)
#define ERROR_PRINT(err) LOGD("[%s]" _MSG_##err "(0x%08x)", __FUNCTION__, err)
#define ERROR_PRINTF(err, fmt, ...) LOGD("[%s]" _MSG_##err "(0x%08x) : " fmt, __FUNCTION__, err, __VA_ARGS__)
#else
#define TYPE_NAME(type) ""
#define DEBUG_PRINT(txt)
#define DEBUG_PRINTF(fmt, ...)
#define ERROR_PRINT(err)
#define ERROR_PRINTF(err)
#endif
	
#define RETURN_VAL_IF(expr, err) \
	do { \
		if (expr) { \
            ERROR_PRINT(err); \
			return (err); \
		} \
	} while(0)

#define RETURN_ERROR(err) \
    do { \
        ERROR_PRINT(err); \
        return err; \
    } while(0)


#define RETURN_IF_NOT_HANDLE(handle) \
	RETURN_VAL_IF(handle == NULL, SENSOR_ERROR_INVALID_PARAMETER)

#define RETURN_IF_NOT_TYPE(type) \
	RETURN_VAL_IF(type > SENSOR_MOTION_FACEDOWN || type < 0, SENSOR_ERROR_INVALID_PARAMETER)

#define RETURN_IF_MOTION_TYPE(type) \
	RETURN_VAL_IF(type > SENSOR_PROXIMITY && type <= SENSOR_MOTION_FACEDOWN, SENSOR_ERROR_INVALID_PARAMETER)

#define RETURN_IF_ERROR(val) \
	RETURN_VAL_IF(val < 0, val)

sensor_data_accuracy_e _accu_table[] = {
	SENSOR_ACCURACY_UNDEFINED,
	SENSOR_ACCURACY_BAD,
	SENSOR_ACCURACY_NORMAL,
	SENSOR_ACCURACY_GOOD,
	SENSOR_ACCURACY_VERYGOOD,
};

sensor_type_t _TYPE[] = {
	ACCELEROMETER_SENSOR,
	GEOMAGNETIC_SENSOR,
	GEOMAGNETIC_SENSOR,
	GYROSCOPE_SENSOR,
	LIGHT_SENSOR,
	PROXIMITY_SENSOR,
	MOTION_SENSOR,
	MOTION_SENSOR,
	MOTION_SENSOR,
	MOTION_SENSOR,
	MOTION_SENSOR,
};

int _DTYPE[] = {
	ACCELEROMETER_BASE_DATA_SET,
	GEOMAGNETIC_RAW_DATA_SET,
	GEOMAGNETIC_BASE_DATA_SET,
	GYRO_BASE_DATA_SET,
	LIGHT_LUX_DATA_SET,
	PROXIMITY_DISTANCE_DATA_SET,
	MOTION_SENSOR,
	MOTION_SENSOR,
	MOTION_SENSOR,
	MOTION_SENSOR,
	MOTION_SENSOR,
};

int _EVENT[] = {
	ACCELEROMETER_EVENT_RAW_DATA_REPORT_ON_TIME,
	GEOMAGNETIC_EVENT_RAW_DATA_REPORT_ON_TIME, 
	GEOMAGNETIC_EVENT_ATTITUDE_DATA_REPORT_ON_TIME,
	GYROSCOPE_EVENT_RAW_DATA_REPORT_ON_TIME,
	LIGHT_EVENT_LUX_DATA_REPORT_ON_TIME, 
    PROXIMITY_EVENT_DISTANCE_DATA_REPORT_ON_TIME,
	MOTION_ENGINE_EVENT_SNAP,
	MOTION_ENGINE_EVENT_SHAKE,
	MOTION_ENGINE_EVENT_DOUBLETAP,
	MOTION_ENGINE_EVENT_PANNING,
	MOTION_ENGINE_EVENT_TOP_TO_BOTTOM,
};

int _CALIBRATION[] = {
	ACCELEROMETER_EVENT_CALIBRATION_NEEDED,
	GEOMAGNETIC_EVENT_CALIBRATION_NEEDED,
	GEOMAGNETIC_EVENT_CALIBRATION_NEEDED,
};

int _sensor_ids[] = {
    ID_ACCELEOMETER,
    ID_GEOMAGNETIC,
    ID_GEOMAGNETIC,
    ID_GYROSCOPE,
    ID_LIGHT,
    ID_PROXIMITY,
    ID_MOTION,
    ID_MOTION,
    ID_MOTION,
    ID_MOTION,
    ID_MOTION
};

#define _SID(id) (_sensor_ids[id])
#define _ACCU(accuracy) (_accu_table[accuracy + 1])

static int _sensor_connect(sensor_h handle, sensor_type_e type)
{
    int id = 0;
    bool support = true;

	RETURN_IF_NOT_TYPE(type);

    if(handle->ids[_SID(type)] < 0){
        sensor_is_supported(type, &support); 
        if(!support)
            return SENSOR_ERROR_NOT_SUPPORTED;

        id = sf_connect(_TYPE[type]);

        DEBUG_PRINTF("%s sensor connect legacy=[%d] type=[%d]", TYPE_NAME(type), type, _TYPE[type]);
        if(id < 0){
            return id == -2 ? SENSOR_ERROR_IO_ERROR : SENSOR_ERROR_OPERATION_FAILED;
        }
        DEBUG_PRINTF("%s sensor id created [%d]", TYPE_NAME(type), id);
        handle->ids[_SID(type)] = id;
    }
    return SENSOR_ERROR_NONE;
}

static void _sensor_callback (unsigned int event_type, sensor_event_data_t* event, void* udata)
{
	int i = 0;
	int data_num = 0;
	sensor_data_t *data = NULL;
    sensor_panning_data_t *panning_data = NULL;
	int motion = 0;
    int nid = 0;
//    bool proximity = 0;

	sensor_h sensor = (sensor_h)udata;

	switch(event_type)
	{
		case MOTION_ENGINE_EVENT_SNAP: 
            nid = SENSOR_MOTION_SNAP;
            break;
		case MOTION_ENGINE_EVENT_SHAKE:
            nid = SENSOR_MOTION_SHAKE;
            break;
		case MOTION_ENGINE_EVENT_DOUBLETAP:
            nid = SENSOR_MOTION_DOUBLETAP;
            break;
		case MOTION_ENGINE_EVENT_PANNING:
            nid = SENSOR_MOTION_PANNING;
            break;
		case MOTION_ENGINE_EVENT_TOP_TO_BOTTOM:
            nid = SENSOR_MOTION_FACEDOWN;
            break;
		case ACCELEROMETER_EVENT_RAW_DATA_REPORT_ON_TIME :
            nid = SENSOR_ACCELEROMETER;
            break;
		case GEOMAGNETIC_EVENT_RAW_DATA_REPORT_ON_TIME :
            nid = SENSOR_MAGNETIC;
            break;
		case GEOMAGNETIC_EVENT_ATTITUDE_DATA_REPORT_ON_TIME :
            nid = SENSOR_ORIENTATION;
            break;
		case GYROSCOPE_EVENT_RAW_DATA_REPORT_ON_TIME :
            nid = SENSOR_GYROSCOPE;
            break;
		case LIGHT_EVENT_LUX_DATA_REPORT_ON_TIME :
            nid = SENSOR_LIGHT;
            break;
		case PROXIMITY_EVENT_DISTANCE_DATA_REPORT_ON_TIME :
            nid = SENSOR_PROXIMITY;
            break;
	}

    if(sensor->cb_func[nid] == NULL || sensor->started[nid] == 0)
        return;
	
	switch(event_type)
	{
		case MOTION_ENGINE_EVENT_SNAP:
		case MOTION_ENGINE_EVENT_SHAKE:
			motion = *(int*)event->event_data;
			break;
		case MOTION_ENGINE_EVENT_PANNING:
            panning_data = (sensor_panning_data_t *)event->event_data;
            break;
		case MOTION_ENGINE_EVENT_DOUBLETAP:
			motion = *(int*)event->event_data;
            if(motion != MOTION_ENGIEN_DOUBLTAP_DETECTION)
                return;
            break;
		case MOTION_ENGINE_EVENT_TOP_TO_BOTTOM:
			motion = *(int*)event->event_data;
            if(motion != MOTION_ENGIEN_TOP_TO_BOTTOM_DETECTION)
                return;
            break;

		case ACCELEROMETER_EVENT_RAW_DATA_REPORT_ON_TIME :
		case GEOMAGNETIC_EVENT_RAW_DATA_REPORT_ON_TIME :
		case GEOMAGNETIC_EVENT_ATTITUDE_DATA_REPORT_ON_TIME :
		case GYROSCOPE_EVENT_RAW_DATA_REPORT_ON_TIME :
		case LIGHT_EVENT_LUX_DATA_REPORT_ON_TIME :
        case PROXIMITY_EVENT_DISTANCE_DATA_REPORT_ON_TIME :
			data = (sensor_data_t*)(event->event_data);
			data_num = (event->event_data_size)/sizeof(sensor_data_t);
			break;
            /*
		case PROXIMITY_EVENT_CHANGE_STATE :
            proximity = *(int*)(event->event_data) == PROXIMITY_STATE_FAR ? 0 : 1;
            break;
            */
		default:
			DEBUG_PRINTF("unknown typed sensor happen!! event=%d\n", event_type);
			return;

	}

	switch(event_type)
	{
		case MOTION_ENGINE_EVENT_SNAP:
			((sensor_motion_snap_event_cb)sensor->cb_func[nid])(motion, sensor->cb_user_data[nid]);
			break;
		case MOTION_ENGINE_EVENT_SHAKE:
			((sensor_motion_shake_event_cb)sensor->cb_func[nid])(motion, sensor->cb_user_data[nid]);
			break;
		case MOTION_ENGINE_EVENT_DOUBLETAP:
			((sensor_motion_doubletap_event_cb)sensor->cb_func[nid])(sensor->cb_user_data[nid]);
			break;
		case MOTION_ENGINE_EVENT_TOP_TO_BOTTOM:
			((sensor_motion_facedown_event_cb)sensor->cb_func[nid])(sensor->cb_user_data[nid]);
			break;
		case MOTION_ENGINE_EVENT_PANNING:
			((sensor_motion_panning_event_cb)sensor->cb_func[nid])(panning_data->x, panning_data->y, 
                sensor->cb_user_data[nid]);
            break;
		case ACCELEROMETER_EVENT_RAW_DATA_REPORT_ON_TIME :
			for(i=0; i<data_num; i++){
				((sensor_accelerometer_event_cb)sensor->cb_func[nid])
					(_ACCU(data[i].data_accuracy), 
					 data[i].values[0],  data[i].values[1], data[i].values[2], 
					 sensor->cb_user_data[nid]);
			}
			break;
		case GEOMAGNETIC_EVENT_RAW_DATA_REPORT_ON_TIME :
			for(i=0; i<data_num; i++){
				((sensor_magnetic_event_cb)sensor->cb_func[nid])
					(_ACCU(data[i].data_accuracy), 
					 data[i].values[0],  data[i].values[1], data[i].values[2], 
					 sensor->cb_user_data[nid]);
			}
			break;
		case GEOMAGNETIC_EVENT_ATTITUDE_DATA_REPORT_ON_TIME :
			for(i=0; i<data_num; i++){
				((sensor_orientation_event_cb)sensor->cb_func[nid])
					(_ACCU(data[i].data_accuracy), 
					 data[i].values[0],  data[i].values[1], data[i].values[2], 
					 sensor->cb_user_data[nid]);
			}
			break;
		case GYROSCOPE_EVENT_RAW_DATA_REPORT_ON_TIME :
			for(i=0; i<data_num; i++){
				((sensor_gyroscope_event_cb)sensor->cb_func[nid])
					(_ACCU(data[i].data_accuracy), 
					 data[i].values[0],  data[i].values[1], data[i].values[2], 
					 sensor->cb_user_data[nid]);
			}
			break;
		case LIGHT_EVENT_LUX_DATA_REPORT_ON_TIME :
			for(i=0; i<data_num; i++){
				((sensor_light_event_cb)sensor->cb_func[nid])
					(_ACCU(data[i].data_accuracy), 
					 data[i].values[0], 
					 sensor->cb_user_data[nid]);
			}
			break;
		case PROXIMITY_EVENT_DISTANCE_DATA_REPORT_ON_TIME :
			for(i=0; i<data_num; i++){
				((sensor_proximity_event_cb)sensor->cb_func[nid])
					(_ACCU(data[i].data_accuracy), 
					 data[i].values[0], 
					 sensor->cb_user_data[nid]);
			}
			break;
	}
}

int sensor_is_supported(sensor_type_e type, bool* supported)
{
    DEBUG_PRINT("sensor_is_support");

	RETURN_IF_NOT_TYPE(type);

    if(supported == NULL)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);

    *supported = !(sf_is_sensor_event_available(_TYPE[type], _EVENT[type]) < 0);
    DEBUG_PRINTF("%s sensor available function return [%d]", TYPE_NAME(type), *supported);

    return SENSOR_ERROR_NONE;
}

int sensor_get_spec(sensor_type_e type, float* max, float* min, float* resolution)
{
    sensor_data_properties_t properties;
    
    DEBUG_PRINT("sensor_get_spec");

    RETURN_IF_MOTION_TYPE(type); 

	RETURN_IF_NOT_TYPE(type);

    if(sf_get_data_properties(_DTYPE[type], &properties) < 0)
        RETURN_ERROR(SENSOR_ERROR_NOT_SUPPORTED);

	*max = properties.sensor_max_range;
	*min = properties.sensor_min_range;
	*resolution = properties.sensor_resolution;

	DEBUG_PRINTF("success get %s's format max=%f, min=%f, res=%f\n", TYPE_NAME(type), *max, *min, *resolution);

	return SENSOR_ERROR_NONE;
}


int sensor_create(sensor_h* handle)
{
	struct sensor_handle_s* sensor = NULL;

    DEBUG_PRINT("sensor_create");

    if(handle == NULL)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);

	sensor = (struct sensor_handle_s*)malloc( sizeof(struct sensor_handle_s) );
	if(sensor==NULL)
        RETURN_ERROR(SENSOR_ERROR_OUT_OF_MEMORY);
	else
	{
        SENSOR_INIT(sensor);

		*handle = (sensor_h)sensor;

		return SENSOR_ERROR_NONE;
	}
}

int sensor_destroy(sensor_h handle)
{

    int i=0;
    bool failed = false;
	RETURN_IF_NOT_HANDLE(handle);

    DEBUG_PRINT("sensor_destroy");

    for(i=0; i<ID_NUMBERS; i++){
        if( handle->ids[i] >= 0 ){
            if(sf_disconnect(handle->ids[i]) < 0)
                failed = true;
            else
                handle->ids[i] = -1;
        }
    }

    free(handle);
    handle = NULL;

    return SENSOR_ERROR_NONE;
}

int sensor_start(sensor_h handle, sensor_type_e type)
{
    int err;
    DEBUG_PRINT("sensor_start");
	RETURN_IF_NOT_HANDLE(handle);
    RETURN_IF_NOT_TYPE(type);

    if( (err = _sensor_connect(handle, type)) != SENSOR_ERROR_NONE){
        return err;
    }

	if (sf_start(handle->ids[_SID(type)], 0) < 0) {
        RETURN_ERROR(SENSOR_ERROR_IO_ERROR);
    } else {
        handle->started[type] = 1;
        return SENSOR_ERROR_NONE;
    }
}

int sensor_stop(sensor_h handle, sensor_type_e type)
{
    DEBUG_PRINT("sensor_stop");
	RETURN_IF_NOT_HANDLE(handle);
    RETURN_IF_NOT_TYPE(type);
	if (sf_stop(handle->ids[_SID(type)]) < 0) {
        RETURN_ERROR(SENSOR_ERROR_IO_ERROR);
    } else {
        handle->started[type] = 0;
        return SENSOR_ERROR_NONE;
    }
}

static void _sensor_calibration (unsigned int event_type, sensor_event_data_t* event, void* udata)
{
	sensor_h sensor = (sensor_h)udata;

	switch (event_type) {
		case ACCELEROMETER_EVENT_CALIBRATION_NEEDED:
            if(sensor->calib_func[SENSOR_ACCELEROMETER] != NULL){
                ((sensor_calibration_cb)sensor->calib_func[SENSOR_ACCELEROMETER])(sensor->calib_user_data[SENSOR_ACCELEROMETER]);
            }
            break;
		case GEOMAGNETIC_EVENT_CALIBRATION_NEEDED:
            if(sensor->calib_func[SENSOR_MAGNETIC] != NULL){
                ((sensor_calibration_cb)sensor->calib_func[SENSOR_MAGNETIC])(sensor->calib_user_data[SENSOR_MAGNETIC]);
            }
            if(sensor->calib_func[SENSOR_ORIENTATION] != NULL){
                ((sensor_calibration_cb)sensor->calib_func[SENSOR_ORIENTATION])(sensor->calib_user_data[SENSOR_ORIENTATION]);
            }
			break;
		default:
			DEBUG_PRINTF("not calibration event happened in calibration callback!! event=%d", event_type);
			return;
	}
}

static int _sensor_set_calibration_cb(sensor_h handle, sensor_type_e type, sensor_calibration_cb callback, void *user_data)
{
	int ret, err;

    DEBUG_PRINTF("%s sensor register calibration callback", TYPE_NAME(type));

	RETURN_IF_NOT_HANDLE(handle);
    switch(type){
        case SENSOR_ACCELEROMETER:
        case SENSOR_MAGNETIC:
        case SENSOR_ORIENTATION:
            break;
        default:
            RETURN_ERROR(SENSOR_ERROR_NOT_NEED_CALIBRATION);
    }

    ret = sf_is_sensor_event_available( _TYPE[type], _CALIBRATION[type] );
    if (ret != 0 ){
        DEBUG_PRINTF("Unsupported calibration ret=[%d] error=[%d] legacy=[%d] type=[%d] cal_id=[%d]", ret, SENSOR_ERROR_NOT_NEED_CALIBRATION, type, _TYPE[type], _CALIBRATION[type]);
        RETURN_ERROR(SENSOR_ERROR_NOT_NEED_CALIBRATION);
    }

    if( (err = _sensor_connect(handle, type)) != SENSOR_ERROR_NONE){
        return err;
    }
	
	handle->calib_func[type] = callback;
	handle->calib_user_data[type] = user_data;

    DEBUG_PRINTF("type : %s / id : %d / event : %x ", TYPE_NAME(type), handle->ids[_SID(type)], _CALIBRATION[type]);

	ret = sf_register_event(handle->ids[_SID(type)], _CALIBRATION[type], NULL, _sensor_calibration, handle);
	if(ret < 0){
		handle->calib_func[type] = NULL;
		handle->calib_user_data[type] = NULL;
        if(ret == -2)
            RETURN_ERROR(SENSOR_ERROR_IO_ERROR);
        else
            RETURN_ERROR(SENSOR_ERROR_OPERATION_FAILED);
	}

    return SENSOR_ERROR_NONE;
}

static int _sensor_unset_calibration_cb(sensor_h handle, sensor_type_e type)
{
	int ret;

    DEBUG_PRINTF("%s sensor register calibration callback", TYPE_NAME(type));

	RETURN_IF_NOT_HANDLE(handle);
	switch (type) {
		case SENSOR_ACCELEROMETER:
		case SENSOR_MAGNETIC:
		case SENSOR_ORIENTATION:
			break;
		default:
			RETURN_ERROR(SENSOR_ERROR_NOT_NEED_CALIBRATION);
	}

    if(handle->calib_func[type] == NULL)
        return SENSOR_ERROR_NONE;

	ret = sf_unregister_event(handle->ids[_SID(type)], _CALIBRATION[type]);

    if (ret < 0){
        if(ret == -2)
            RETURN_ERROR(SENSOR_ERROR_IO_ERROR);
        else
            RETURN_ERROR(SENSOR_ERROR_OPERATION_FAILED);
    }

    handle->calib_func[type] = NULL;
    handle->calib_user_data[type] = NULL;

    return SENSOR_ERROR_NONE;
}


static int _sensor_set_data_cb (sensor_h handle, sensor_type_e type, int rate, void* cb, void* user_data)
{
    int err = 0;
	event_condition_t condition;

	RETURN_IF_NOT_HANDLE(handle);
    RETURN_IF_NOT_TYPE(type);

    DEBUG_PRINTF("sensor register callback %s", TYPE_NAME(type));

    if(rate < 0){
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);
    }
	
	if(rate > 0){
		condition.cond_op = CONDITION_EQUAL;
		condition.cond_value1 = rate;
	}

	handle->cb_func[type] = cb; 
	handle->cb_user_data[type] = user_data;

    if( (err = _sensor_connect(handle, type)) != SENSOR_ERROR_NONE){
        DEBUG_PRINTF("%s sensor connect error handle=[%d] legacy=[%d] err=[%d]", TYPE_NAME(type), handle, type, err);
        return err;
    }

    err = sf_register_event(handle->ids[_SID(type)], _EVENT[type],
				(rate > 0 ? &condition : NULL), _sensor_callback, handle);

    DEBUG_PRINTF("%s sensor register function return [%d] event=[%d]", TYPE_NAME(type), err, _EVENT[type]);

    if(err < 0){
        handle->cb_func[type] = NULL;
        handle->cb_user_data[type] = NULL;
        if(err == -2)
            RETURN_ERROR(SENSOR_ERROR_IO_ERROR);
        else
            RETURN_ERROR(SENSOR_ERROR_OPERATION_FAILED);
    }

    return SENSOR_ERROR_NONE;
}

static int _sensor_unset_data_cb (sensor_h handle, sensor_type_e type)
{
    int error;
    DEBUG_PRINTF("sensor unregister callback %s", TYPE_NAME(type));
	RETURN_IF_NOT_HANDLE(handle);
    if (handle->ids[_SID(type)] < 0 )
        return SENSOR_ERROR_INVALID_PARAMETER;

    error = sf_unregister_event(handle->ids[_SID(type)], _EVENT[type]);

    if (error < 0){
        if(error == -2)
            RETURN_ERROR(SENSOR_ERROR_IO_ERROR);
        else
            RETURN_ERROR(SENSOR_ERROR_OPERATION_FAILED);
    }

    handle->cb_func[type] = NULL;
    handle->cb_user_data[type] = NULL;
    return SENSOR_ERROR_NONE;
}

int sensor_accelerometer_set_cb (sensor_h handle, 
		int rate, sensor_accelerometer_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_ACCELEROMETER, rate, (void*) callback, user_data);
}

int sensor_accelerometer_unset_cb              (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_ACCELEROMETER);
}

int sensor_magnetic_set_cb (sensor_h handle, 
		int rate, sensor_magnetic_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_MAGNETIC, rate, (void*) callback, user_data);
}

int sensor_magnetic_unset_cb                   (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_MAGNETIC);
}

int sensor_magnetic_set_calibration_cb         (sensor_h handle, sensor_calibration_cb callback, void *user_data)
{
    return _sensor_set_calibration_cb(handle, SENSOR_MAGNETIC, callback, user_data);
}
int sensor_magnetic_unset_calibration_cb       (sensor_h handle)
{
    return _sensor_unset_calibration_cb(handle, SENSOR_MAGNETIC);
}

int sensor_orientation_set_cb (sensor_h handle, 
		int rate, sensor_orientation_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_ORIENTATION, rate, (void*) callback, user_data);
}

int sensor_orientation_unset_cb                (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_ORIENTATION);
}
int sensor_orientation_set_calibration_cb      (sensor_h handle, sensor_calibration_cb callback, void *user_data)
{
    return _sensor_set_calibration_cb(handle, SENSOR_ORIENTATION, callback, user_data);
}
int sensor_orientation_unset_calibration_cb    (sensor_h handle)
{
    return _sensor_unset_calibration_cb(handle, SENSOR_ORIENTATION);
}

int sensor_gyroscope_set_cb (sensor_h handle, 
		int rate, sensor_gyroscope_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_GYROSCOPE, rate, (void*) callback, user_data);
}

int sensor_gyroscope_unset_cb                  (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_GYROSCOPE);
}

int sensor_light_set_cb (sensor_h handle, 
		int rate, sensor_light_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_LIGHT, rate, (void*) callback, user_data);
}

int sensor_light_unset_cb                      (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_LIGHT);
}

int sensor_proximity_set_cb (sensor_h handle, int interval_ms, sensor_proximity_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_PROXIMITY, interval_ms, (void*) callback, user_data);
}

int sensor_proximity_unset_cb                  (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_PROXIMITY);
}

static int _sensor_read_data(sensor_h handle, sensor_type_e type, 
		sensor_data_accuracy_e* accuracy, float* values, int values_size)
{
    int err = 0;
	sensor_data_t data;

	RETURN_IF_NOT_HANDLE(handle);
    if(type > SENSOR_PROXIMITY && type <= SENSOR_MOTION_DOUBLETAP)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);
	RETURN_IF_NOT_TYPE(type);

    DEBUG_PRINTF("sensor read data %s", TYPE_NAME(type));

    if( (err = _sensor_connect(handle, type)) != SENSOR_ERROR_NONE)
        return err;
	if ( sf_get_data(handle->ids[_SID(type)], _DTYPE[type], &data) < 0 )
    {
        RETURN_ERROR(SENSOR_ERROR_IO_ERROR);
    }

	// this error will never happen. but it exist for more safe code.. 
	if(values_size > 12 || values_size < 0)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);
	
    if(accuracy != NULL)
        *accuracy = _ACCU(data.data_accuracy);
	memcpy(values, data.values, values_size * sizeof(float));

	return SENSOR_ERROR_NONE;
}

int sensor_accelerometer_read_data (sensor_h handle, 
		sensor_data_accuracy_e* accuracy, float* x, float* y, float* z)
{
	float values[3] = {0,0,0};
	int err = _sensor_read_data(handle, SENSOR_ACCELEROMETER, accuracy, values, 3);
    if(err < 0) return err;

    if(x == NULL || y == NULL || z == NULL)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);

    *x = values[0];
    *y = values[1];
    *z = values[2];

	return SENSOR_ERROR_NONE;
}

int sensor_magnetic_read_data      (sensor_h handle, sensor_data_accuracy_e* accuracy, float* x, float* y, float* z)
{
	float values[3] = {0,0,0};
	int err = _sensor_read_data(handle, SENSOR_MAGNETIC, accuracy, values, 3);
    if(err < 0) return err;

    if(x == NULL || y == NULL || z == NULL)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);

    *x = values[0];
    *y = values[1];
    *z = values[2];

	return SENSOR_ERROR_NONE;
}

int sensor_orientation_read_data   (sensor_h handle, sensor_data_accuracy_e* accuracy, float* azimuth, float* pitch, float* roll)
{
	float values[3] = {0,0,0};
	int err = _sensor_read_data(handle, SENSOR_ORIENTATION, accuracy, values, 3);
    if(err < 0) return err;

    if(azimuth == NULL || pitch == NULL || roll == NULL)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);

    *azimuth = values[0];
    *pitch = values[1];
    *roll = values[2];

	return SENSOR_ERROR_NONE;
}

int sensor_gyroscope_read_data     (sensor_h handle, sensor_data_accuracy_e* accuracy, float* x, float* y, float* z)
{
	float values[3] = {0,0,0};
	int err = _sensor_read_data(handle, SENSOR_GYROSCOPE, accuracy, values, 3);
    if(err < 0) return err;

    if(x == NULL || y == NULL || z == NULL)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);

    *x = values[0];
    *y = values[1];
    *z = values[2];

	return SENSOR_ERROR_NONE;
}

int sensor_light_read_data         (sensor_h handle, sensor_data_accuracy_e* accuracy, float* lux)
{
	float values[1] = {0};
	int err = _sensor_read_data(handle, SENSOR_LIGHT, accuracy, values, 1);
    if(err < 0) return err;

    if(lux == NULL)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);

    *lux = values[0];

	return SENSOR_ERROR_NONE;
}

int sensor_proximity_read_data     (sensor_h handle, sensor_data_accuracy_e* accuracy, float* distance)
{
	float values[1] = {0};
    int err = _sensor_read_data(handle, SENSOR_PROXIMITY, accuracy, values, 1);
    if(err < 0) return err;

    if(distance == NULL)
        RETURN_ERROR(SENSOR_ERROR_INVALID_PARAMETER);

    *distance = values[0];

	return SENSOR_ERROR_NONE;
}


int sensor_motion_snap_set_cb    (sensor_h handle, sensor_motion_snap_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_MOTION_SNAP, 0, (void*) callback, user_data);
}

int sensor_motion_snap_unset_cb                (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_MOTION_SNAP);
}

int sensor_motion_shake_set_cb   (sensor_h handle, sensor_motion_shake_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_MOTION_SHAKE, 0, (void*) callback, user_data);
}

int sensor_motion_shake_unset_cb (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_MOTION_SHAKE);
}

int sensor_motion_doubletap_set_cb    (sensor_h handle, sensor_motion_doubletap_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_MOTION_DOUBLETAP, 0, (void*) callback, user_data);
}

int sensor_motion_doubletap_unset_cb (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_MOTION_DOUBLETAP);
}

int sensor_motion_panning_set_cb    (sensor_h handle, sensor_motion_panning_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_MOTION_PANNING, 0, (void*) callback, user_data);
}

int sensor_motion_panning_unset_cb (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_MOTION_PANNING);
}

int sensor_motion_facedown_set_cb    (sensor_h handle, sensor_motion_facedown_event_cb callback, void *user_data)
{
	return _sensor_set_data_cb(handle, SENSOR_MOTION_FACEDOWN, 0, (void*) callback, user_data);
}

int sensor_motion_facedown_unset_cb (sensor_h handle)
{
    return _sensor_unset_data_cb(handle, SENSOR_MOTION_FACEDOWN);
}
