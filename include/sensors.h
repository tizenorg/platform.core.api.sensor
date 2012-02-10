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




#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <tizen_error.h>
#include <tizen_type.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MODULE
 * @{
 */

/**
 * @brief The sensor handle.
 */
typedef struct sensor_handle_s* sensor_h;

/**
* @brief	Enumerations of sensor data accuracy.
*/
typedef enum
{
	SENSOR_DATA_ACCURACY_UNDEFINED   = -1,  /**< Undefined accuracy */
	SENSOR_DATA_ACCURACY_BAD         = 0,   /**< Bad accuracy */
	SENSOR_DATA_ACCURACY_NORMAL      = 1,   /**< Normal accuracy */
	SENSOR_DATA_ACCURACY_GOOD        = 2,   /**< Good accuracy */
	SENSOR_DATA_ACCURACY_VERYGOOD    = 3    /**< Very good accuracy */
} sensor_data_accuracy_e;


/**
* @brief	Enumerations of error code for sensor.
*/
typedef enum
{
	SENSOR_ERROR_NONE                  = TIZEN_ERROR_NONE,                   /**< Successful */
    SENSOR_ERROR_IO_ERROR              = TIZEN_ERROR_IO_ERROR,             /**< I/O error */
	SENSOR_ERROR_INVALID_PARAMETER     = TIZEN_ERROR_INVALID_PARAMETER,    /**< Invalid parameter */
	SENSOR_ERROR_OUT_OF_MEMORY         = TIZEN_ERROR_SYSTEM_CLASS | 0x02,  /**< Out of memory */
	SENSOR_ERROR_NOT_NEED_CALIBRATION  = TIZEN_ERROR_SYSTEM_CLASS | 0x03,  /**< Sensor doesn't need calibration */
	SENSOR_ERROR_NOT_SUPPORTED         = TIZEN_ERROR_SYSTEM_CLASS | 0x04,  /**< Unsupported sensor in current device */
    SENSOR_ERROR_OPERATION_FAILED      = TIZEN_ERROR_SYSTEM_CLASS | 0x06,  /**< Operation failed */

} sensor_error_e;


/**
* @brief	Enumerations of sensor type.
*/
typedef enum
{
	SENSOR_ACCELEROMETER,                    /**< Accelerometer */
	SENSOR_MAGNETIC,                         /**< Magnetic sensor */
	SENSOR_ORIENTATION,                      /**< Orientation sensor */
	SENSOR_GYROSCOPE,                        /**< Gyroscope sensor */
	SENSOR_LIGHT,                            /**< Light sensor */
	SENSOR_PROXIMITY,                        /**< Proximity sensor */
	SENSOR_MOTION_SNAP,                      /**< Snap motion sensor */
	SENSOR_MOTION_SHAKE,                     /**< Shake motion sensor */
	SENSOR_MOTION_DOUBLETAP,                 /**< Double tap motion sensor */
    SENSOR_MOTION_PANNING,                   /**< Panning motion sensor */
    SENSOR_MOTION_FACEDOWN                   /**< Face to down motion sensor */
} sensor_type_e;
/**
 * @}
 */


/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SNAP_MODULE
 * @{
 */

/**
 * @brief	Enumerations of snap motion event.
 */
typedef enum
{
	SENSOR_MOTION_SNAP_NONE,            /**< No Snap */
	SENSOR_MOTION_SNAP_LEFT,            /**< Snap left to right */
	SENSOR_MOTION_SNAP_RIGHT,           /**< Snap right to left */
} sensor_motion_snap_e;
/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SHAKE_MODULE
 * @{
 */

/**
 * @brief	Enumerations of shake motion event.
 */
typedef enum
{
	SENSOR_MOTION_SHAKE_NONE,                /**< No Shake */
	SENSOR_MOTION_SHAKE_DETECTED,            /**< Shake motion detected */
	SENSOR_MOTION_SHAKE_CONTINUING,          /**< Shake motion continuing */
	SENSOR_MOTION_SHAKE_FINISHED,            /**< Shake motion finished */
	SENSOR_MOTION_SHAKE_BROKEN,              /**< Shake motion broken */
} sensor_motion_shake_e;
/**
 * @}
 */


/**
 * @}
*/

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MODULE
 * @{
 */

/**
 * @brief Called when the current sensor reading falls outside of a defined normal range.
 *
 * @details When something is artificially influencing, such as ferrous metal objects or 
 * electromagnetic fields (car electrical systems, automobile engines, steel pitons, etc.), this callback is called.
 * One way of implementing this callback is to notice a user to make big 8-like gesture with device.
 *
 * @param[in] user_data	The user data passed from the callback registration function
 *
 * @see sensor_magnetic_set_calibration_cb()
 * @see sensor_magnetic_unset_calibration_cb()
 * @see sensor_orientation_set_calibration_cb()
 * @see sensor_orientation_unset_calibration_cb()
 */
typedef void (*sensor_calibration_cb)(void *user_data);
/**
 * @}
 */


/**
 * @addtogroup CAPI_SYSTEM_SENSOR_ACCELEROMETER_MODULE
 * @{
 */

/**
 * @brief Called when an accelerometer event occurs.
 *
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] x             The acceleration minus Gx on the x-axis in [m/s^2]
 * @param[in] y             The acceleration minus Gy on the y-axis in [m/s^2]
 * @param[in] z             The acceleration minus Gz on the z-axis in [m/s^2]
 * @param[in] user_data     The user data passed from the callback registration function
 *
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_accelerometer_set_cb().
 *
 * @see sensor_accelerometer_set_cb()
 * @see sensor_accelerometer_unset_cb()
 */
typedef void (*sensor_accelerometer_event_cb)(
		sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data);
/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_GYROSCOPE_MODULE
 * @{
 */

/**
 * @brief Called when a gyroscope event occurs.
 *
 * @remark
 * Measure the rate of rotation around X, Y and Z axis in radians/second values.
 * All values is observed by positive value in the counter-clockwise direction.
 *
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] x             Angular speed around the x-axis in degree per second
 * @param[in] y             Angular speed around the y-axis in degree per second
 * @param[in] z             Angular speed around the z-axis in degree per second
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_gyroscope_set_cb().
 * @see sensor_gyroscope_set_cb()
 * @see sensor_gyroscope_unset_cb()
 */
typedef void (*sensor_gyroscope_event_cb)(
		sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data);
/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_LIGHT_MODULE
 * @{
 */

/**
 * @brief Called when a light event occurs.
 *
 * @remark
 * You should use lux between min and max values obtained \n
 * with #sensor_get_spec().
 *
 * @param[in] accuracy      The accuracy of @a level, @a y, and @a z values
 * @param[in] lux           The ambient light level in SI lux units \n
 *			@a lux is between min and max values obtained with #sensor_get_spec().\n
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_light_set_cb().
 * @see sensor_light_set_cb()
 * @see sensor_light_unset_cb()
 */
typedef void (*sensor_light_event_cb)(
		sensor_data_accuracy_e accuracy, float lux, void *user_data);
/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MAGNETIC_MODULE
 * @{
 */

/**
 * @brief Called when a magnetic event occurs.
 *
 * @remark @a x, @a y, and @a z values are in micro-Teslas(uT) and measure the ambient magnetic field in the X, Y and Z axis.
 *
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] x             Micro-Tesla value from ambient magnetic field on the x-axis
 * @param[in] y             Micro-Tesla value from ambient magnetic field on the y-axis
 * @param[in] z             Micro-Tesla value from ambient magnetic field on the z-axis
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_magnetic_set_cb().
 * @see sensor_magnetic_set_cb()
 * @see sensor_magnetic_unset_cb()
 */
typedef void (*sensor_magnetic_event_cb)(
		sensor_data_accuracy_e accuracy, float x, float y, float z, void *user_data);
/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_ORIENTATION_MODULE
 * @{
 */

/**
 * @brief Called when an orientation event occurs.
 *
 * @remark  All values are angles in degrees.
 *
 * @param[in] accuracy      The accuracy of @a x, @a y, and @a z values
 * @param[in] azimuth       The angle between the magnetic north direction and the y-axis, around the z-axis [0 ~ 359]. \n
 *                          0 = North, 90 = East, 180 = South, 270 = West
 * @param[in] pitch         The rotation around x-axis [-180 ~ 180], with positive values when the z-axis moves \n
 *                          toward the y-axis
 * @param[in] roll          The rotation around y-axis [-90 ~ 90], with positive values when the x-axis moves \n
 *                          toward the z-axis
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_orientation_set_cb().
 * @see sensor_orientation_set_cb()
 * @see sensor_orientation_unset_cb()
 */
typedef void (*sensor_orientation_event_cb)(
		sensor_data_accuracy_e accuracy, float azimuth, float pitch, float roll, void *user_data);
/**
 * @}
 */

/**
 * @addtogroup CAPI_SYSTEM_SENSOR_PROXIMITY_MODULE
 * @{
 */

/**
 * @brief Called when a proximity event occurs.
 *
 * @param[in]  distance       The distance measured in centemeters
 * @param[in]   user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_proximity_set_cb().
 * @see sensor_proximity_set_cb()
 * @see sensor_proximity_unset_cb()
 */
typedef void (*sensor_proximity_event_cb)(sensor_data_accuracy_e accuracy, float distance, void *user_data);
/**
 * @}
 */



/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SNAP_MODULE
 * @{
 */

/**
 * @brief Called when a snap motion event occurs.
 * @image html phone_snap.png
 *
 * @param[in] snap          The type of motion snap
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_snap_set_cb().
 * @see sensor_motion_snap_set_cb()
 * @see sensor_motion_snap_unset_cb()
 */
typedef void (*sensor_motion_snap_event_cb) (sensor_motion_snap_e snap, void *user_data);
/**
 * @}
 */


/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SHAKE_MODULE
 * @{
 */

/**
 * @brief Called when a shake motion event occurs.
 *
 * @param[in] shake         The type of motion shake
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_shake_set_cb().
 * @see sensor_motion_shake_set_cb()
 * @see sensor_motion_shake_unset_cb()
 */
typedef void (*sensor_motion_shake_event_cb) (sensor_motion_shake_e shake, void *user_data);
/**
 * @}
 */


/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_DOUBLETAP_MODULE
 * @{
 */

/**
 * @brief Called when a double tap motion event occurs.
 *
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_doubletap_set_cb().
 * @see sensor_motion_doubletap_set_cb()
 * @see sensor_motion_doubletap_unset_cb()
 */
typedef void (*sensor_motion_doubletap_event_cb) (void *user_data);
/**
 * @}
 */


/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_PANNING_MODULE
 * @{
 */

/**
 * @brief Called when a panning tap motion event occurs.
 * @image html phone_panning.png
 *
 * @param[in] x             1/10 angle on x-axis
 * @param[in] y             1/10 angle on y-axis
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_panning_set_cb().
 * @see sensor_motion_panning_set_cb()
 * @see sensor_motion_panning_unset_cb()
 */
typedef void (*sensor_motion_panning_event_cb) (int x, int y, void *user_data);
/**
 * @}
 */


/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_FACEDOWN_MODULE
 * @{
 */

/**
 * @brief Called when a facedown tap motion event occurs.
 * @details
 * This event occurs when device is flipped as follows:
 * @image html phone_facedown.png
 * This motion event will fire only when the device is flipped from face to back.
 * It will not occur when the device is flipped from back to face.
 *
 * @param[in] user_data     The user data passed from the callback registration function
 * @pre sensor_start() will invoke this callback if you register this callback using sensor_motion_facedown_set_cb().
 * @see sensor_motion_facedown_set_cb()
 * @see sensor_motion_facedown_unset_cb()
 */
typedef void (*sensor_motion_facedown_event_cb) (void *user_data);
/**
 * @}
 */


/**
 * @addtogroup CAPI_SYSTEM_SENSOR_MODULE
 * @{
 */


/**
 * @brief Checks whether the given sensor type is available on a device.
 * @details
 * You need to check availability of a sensor first because this sensor may not be supported on the device.
 *
 * @param[in]   type        The sensor type to check
 * @param[out]  supported   @c true if this sensor type is supported, otherwise @c false
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 *
 */
int sensor_is_supported(sensor_type_e type, bool *supported);


/**
 * @brief Gets data specification for a sensor type, except motion sensors.
 *
 * @remark When the given @a type is one of the motion sensors, this function returns #SENSOR_ERROR_INVALID_PARAMETER.
 *
 * @param[in]   type         The sensor type to check
 * @param[out]  max          The maximum range of the sensor in the sensor's unit 
 * @param[out]  min          The minimum range of the sensor in the sensor's unit
 * @param[out]  resolution   The resolution of the sensor
 *
 * @return      0 on success, otherwise a negative error value.
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED         The sensor type is not supported in current device
 *
 * @pre #sensor_is_supported()
 */
int sensor_get_spec(sensor_type_e type, float *max, float *min, float *resolution);


/**
 * @brief Creates a sensor handle.
 *
 * @remarks @a sensor must be released sensor_destroy() by you.
 *
 * @param[out] sensor	A new sensor handle to the sensors
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE               Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval      #SENSOR_ERROR_OUT_OF_MEMORY      Out of memory
 *
 * @see sensor_destroy()
 */
int sensor_create(sensor_h *sensor);


/**
 * @brief Destroys the sensor handle and releases all its resources.
 *
 * @remark After this function is called, the attached sensor will be detached and 
 *		the corresponding sensor connection will be released.
 *
 * @param[in] sensor	The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 *
 * @see sensor_create()
 */
int sensor_destroy(sensor_h sensor);


/**
 * @brief Starts sensor server for the given sensor handle and sensor type.
 * @details
 * After this function is called, sensor events will occur and 
 * the specific sensor type related callback function will be called. An application can read sensor data.
 *
 * @param[in] sensor  The sensor handle
 * @param[in] type    The sensor type
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_NOT_SUPPORTED         The sensor type is not supported in current device
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @pre call sensor_create() before using this function.
 * @post This function invokes sensor_calibration_cb(), sensor_accelerometer_event_cb(), sensor_magnetic_event_cb(),
 * sensor_orientation_event_cb(), sensor_gyroscope_event_cb(), sensor_light_event_cb(),
 * sensor_proximity_event_cb(), sensor_motion_snap_event_cb(), sensor_motion_shake_event_cb(),
 * sensor_motion_doubletap_event_cb(), sensor_motion_panning_event_cb(), or sensor_motion_facedown_event_cb().
 *
 * @see sensor_stop()
 */
int sensor_start(sensor_h sensor, sensor_type_e type);


/**
 * @brief Stops sensor server for the given sensor handle and type.
 * @details The given @a type event will not occur any more and the callback functions also won't be called.
 *
 * @param[in]   sensor  The sensor handle
 * @param[in]   type    The sensor type
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 *
 * @see sensor_start()
 */
int sensor_stop(sensor_h sensor, sensor_type_e type);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_ACCELEROMETER_MODULE
 * @{
 */


/**
 * @brief	Registers a callback function to be invoked when an accelerometer event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered at (in milliseconds) \n
 *							If @a rate is zero, it uses default value(100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_accelerometer_event_cb() will be invoked.
 *
 * @see sensor_accelerometer_event_cb()
 * @see sensor_accelerometer_unset_cb()
 */
int sensor_accelerometer_set_cb(sensor_h sensor, int interval_ms, sensor_accelerometer_event_cb callback, void *user_data);


/**
 * @brief	Unregister the accelerometer callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                    Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER       Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_accelerometer_set_cb()
 */
int sensor_accelerometer_unset_cb(sensor_h sensor);


/**
 * @brief	Gets sensor data from the accelerometer sensor.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  x           The acceleration minus Gx on the x-axis in meters per second squared (m/s^2)
 * @param[out]  y           The acceleration minus Gy on the y-axis in meters per second squared (m/s^2)
 * @param[out]  z           The acceleration minus Gz on the z-axis in meters per second squared (m/s^2)
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 */
int sensor_accelerometer_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *x, float *y, float *z);


/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_GYROSCOPE_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when a gyroscope event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered in (in milliseconds) \n
 *                          If @a interval_ms is zero, it uses default value (100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post	sensor_gyroscope_event_cb() will be invoked
 *
 * @see sensor_gyroscope_event_cb()
 * @see sensor_gyroscope_unset_cb()
 */
int sensor_gyroscope_set_cb(sensor_h sensor, int interval_ms, sensor_gyroscope_event_cb callback, void *user_data);

/**
 * @brief	Unregister the gyroscope callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see	sensor_gyroscope_set_cb()
 */
int sensor_gyroscope_unset_cb(sensor_h sensor);

/**
 * @brief
 * Gets sensor data from the gyroscope sensor.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  x           The angular speed around the x-axis in degree per second
 * @param[out]  y           The angular speed around the y-axis in degree per second
 * @param[out]  z           The angular speed around the z-axis in degree per second
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 * @see	sensor_start()
 */
int sensor_gyroscope_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *x, float *y, float *z);

/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_LIGHT_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when a light event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered in (in milliseconds) \n
 *                          If @a interval_ms is zero, it uses default value (100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_light_event_cb() will be invoked.
 *
 * @see sensor_light_event_cb()
 * @see	sensor_light_unset_cb()
 */
int sensor_light_set_cb(sensor_h sensor, int interval_ms, sensor_light_event_cb callback, void *user_data);

/**
 * @brief	Unregister the light callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_light_set_cb()
 */
int sensor_light_unset_cb(sensor_h sensor);

/**
 * @brief	Gets sensor data from the light sensor.
 *
 * @remark
 * You should use lux between min and max values obtained \n
 * with #sensor_get_spec().
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  lux       The ambient light level in SI lux units \n
 *			@a lux is between min and max values obtained with #sensor_get_spec().\n
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @pre In order to read sensor data, an application should call sensor_start().
 * @see #sensor_data_accuracy_e
 * @see sensor_start()
 */
int sensor_light_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *lux);

/**
 * @}
 * 
 * @addtogroup CAPI_SYSTEM_SENSOR_MAGNETIC_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when a magnetic event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered in (in milliseconds) \n
 *                          If @a interval_ms is zero, it uses default value (100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_magnetic_event_cb() will be invoked.
 *
 * @see sensor_magnetic_event_cb()
 * @see	sensor_magnetic_unset_cb()
 */
int sensor_magnetic_set_cb(sensor_h sensor, int interval_ms, sensor_magnetic_event_cb callback, void *user_data);

/**
 * @brief	Unregister the magnetic callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR                I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_magnetic_set_cb()
 */
int sensor_magnetic_unset_cb(sensor_h sensor);

/**
 * @brief Gets sensor data from the magnetic sensor.
 *
 * @remark All values are in micro-Teslas (uT) and measure the ambient magnetic field in the X, Y and Z axis.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  x           Micro-Tesla value on the x-axis
 * @param[out]  y           Micro-Tesla value on the y-axis
 * @param[out]  z           Micro-Tesla value on the z-axis
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 *
 * @see sensor_start()
 */
int sensor_magnetic_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *x, float *y, float *z);

/**
 * @brief	Registers a callback function to be invoked when the current sensor reading falls outside of a defined normal range.
 *
 * @param[in]   sensor     The sensor handle
 * @param[in]   callback   The callback function to register
 * @param[in]   user_data  The user data to be passed to the callback function
 *
 * @return		0 on success, otherwise a negative error value
 * @retval		#SENSOR_ERROR_NONE                  Successful
 * @retval		#SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval		#SENSOR_ERROR_IO_ERROR              I/O error
 * @retval		#SENSOR_ERROR_OPERATION_FAILED      Operation failed
 * @retval		#SENSOR_ERROR_NOT_NEED_CALIBRATION	Sensor doesn't need calibration
 *
 * @post sensor_calibration_cb() will be invoked.
 *
 * @see sensor_calibration_cb()
 * @see	sensor_magnetic_unset_calibration_cb()
 */
int sensor_magnetic_set_calibration_cb(sensor_h sensor, sensor_calibration_cb callback, void *user_data);

/**
 * @brief	Unregisters the magnetic calibration callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 * @retval		#SENSOR_ERROR_NOT_NEED_CALIBRATION	Sensor doesn't need calibration
 * @see sensor_magnetic_set_calibration_cb()
 */
int sensor_magnetic_unset_calibration_cb(sensor_h sensor);

/**
 * @}
 * 
 * @addtogroup CAPI_SYSTEM_SENSOR_ORIENTATION_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when an orientation event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered in (in milliseconds) \n
 *                          If @a interval_ms is zero, it uses default value (100ms)
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function 
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_orientation_event_cb() will be invoked.
 *
 * @see sensor_orientation_event_cb()
 * @see sensor_orientation_unset_cb()
*/
int sensor_orientation_set_cb(sensor_h sensor, int interval_ms, sensor_orientation_event_cb callback, void *user_data);

/**
 * @brief	Unregister the orientation callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_orientation_set_cb()
 */
int sensor_orientation_unset_cb(sensor_h sensor);

/**
 * @brief	Registers a callback function to be invoked when the current sensor reading falls outside of a defined normal range.
 *
 * @param[in]   sensor     The sensor handle
 * @param[in]   callback   The callback function to register
 * @param[in]   user_data  The user data to be passed to the callback function 
 *
 * @return		0 on success, otherwise a negative error value
 * @retval  	#SENSOR_ERROR_NONE                  Successful
 * @retval  	#SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 * @retval		#SENSOR_ERROR_NOT_NEED_CALIBRATION	Sensor doesn't need calibration
 *
 * @post sensor_calibration_cb() will be invoked.
 *
 * @see sensor_calibration_cb()
 * @see sensor_orientation_unset_calibration_cb()
 */
int sensor_orientation_set_calibration_cb(sensor_h sensor, sensor_calibration_cb callback, void *user_data);

/**
 * @brief	Unregister the orientation calibration callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 * @retval		#SENSOR_ERROR_NOT_NEED_CALIBRATION	Sensor doesn't need calibration
 *
 * @see sensor_orientation_set_calibration_cb()
 */
int sensor_orientation_unset_calibration_cb(sensor_h sensor);

/**
 * @brief Gets sensor data from the orientation sensor.
 *
 * @remark
 * All values are angles in degrees.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  azimuth     The angle in degrees between the magnetic north direction and the y-axis, \n
 *                          around the z-axis [0 ~ 359]. 0=North, 90=East, 180=South, 270=West
 * @param[out]  pitch       The rotation in degrees around x-axis [-180 ~ 180], with positive values when the \n
 *                          z-axis moves toward the y-axis
 * @param[out]  roll        The rotation in degrees around y-axis [-90 ~ 90], with positive values when the \n
 *                          x-axis moves toward the z-axis
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 * @see sensor_start()
 */
int sensor_orientation_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *azimuth, float *pitch, float *roll);

/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_PROXIMITY_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when a proximity event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   interval_ms	The interval sensor events are delivered in (in milliseconds) \n
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_proximity_event_cb() will be invoked.
 *
 * @see sensor_proximity_event_cb()
 * @see sensor_proximity_unset_cb()
 */
int sensor_proximity_set_cb(sensor_h sensor, int interval_ms, sensor_proximity_event_cb callback, void *user_data);

/**
 * @brief	Unregister the proximity callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_proximity_set_cb()
 */
int sensor_proximity_unset_cb(sensor_h sensor);

/**
 * @brief Gets sensor data from the Proximity sensor.
 *
 * @remark
 * All values are angles in degrees.
 *
 * @param[in]   sensor      The sensor handle
 * @param[out]  accuracy    The accuracy of this data
 * @param[out]  distance    The distance measured in centemeters
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 *
 * @pre In order to read sensor data, an application should call sensor_start().
 * @see sensor_start()
 */
int sensor_proximity_read_data(sensor_h sensor, sensor_data_accuracy_e *accuracy, float *distance);
/**
 * @}
 *
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_MODULE
 * @{
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_DOUBLETAP_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when a motion doubletap event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_doubletap_event_cb() will be invoked.
 *
 * @see sensor_motion_doubletap_event_cb()
 * @see	sensor_motion_doubletap_unset_cb()
 */
int sensor_motion_doubletap_set_cb(sensor_h sensor, sensor_motion_doubletap_event_cb callback, void *user_data);

/**
 * @brief	Unregister the doubletap callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see	sensor_motion_doubletap_set_cb()
 */
int sensor_motion_doubletap_unset_cb(sensor_h sensor);

/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SNAP_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when a motion snap event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_snap_event_cb() will be invoked.
 *
 * @see sensor_motion_snap_event_cb()
 * @see sensor_motion_snap_unset_cb() 
 */
int sensor_motion_snap_set_cb(sensor_h sensor, sensor_motion_snap_event_cb callback, void *user_data);

/**
 * @brief	Unregister the snap callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_motion_snap_set_cb() 
 */
int sensor_motion_snap_unset_cb(sensor_h sensor);

/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_SHAKE_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when a motion shake event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback	The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_shake_event_cb() will be invoked.
 *
 * @see sensor_motion_shake_event_cb()
 * @see sensor_motion_shake_unset_cb()
 */
int sensor_motion_shake_set_cb(sensor_h sensor, sensor_motion_shake_event_cb callback, void *user_data);

/**
 * @brief	Unregister the callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_motion_shake_set_cb()
 */
int sensor_motion_shake_unset_cb(sensor_h sensor);

/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_PANNING_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when a motion panning event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_panning_event_cb() will be invoked.
 *
 * @see sensor_motion_panning_event_cb()
 * @see	sensor_motion_panning_unset_cb()
 */
int sensor_motion_panning_set_cb(sensor_h sensor, sensor_motion_panning_event_cb callback, void *user_data);

/**
 * @brief	Unregister the callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see	sensor_motion_panning_set_cb()
 */
int sensor_motion_panning_unset_cb(sensor_h sensor);

/**
 * @}
 *
 * @addtogroup CAPI_SYSTEM_SENSOR_MOTION_FACEDOWN_MODULE
 * @{
 */

/**
 * @brief	Registers a callback function to be invoked when a motion facedown event occurs.
 *
 * @param[in]   sensor      The sensor handle
 * @param[in]   callback    The callback function to register
 * @param[in]   user_data   The user data to be passed to the callback function
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR              I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @post sensor_motion_facedown_event_cb() will be invoked.
 *
 * @see sensor_motion_facedown_event_cb()
 * @see sensor_motion_facedown_unset_cb()
 */
int sensor_motion_facedown_set_cb(sensor_h sensor, sensor_motion_facedown_event_cb callback, void *user_data);

/**
 * @brief	Unregister the facedown callback function.
 *
 * @param[in]   sensor     The sensor handle
 *
 * @return      0 on success, otherwise a negative error value
 * @retval      #SENSOR_ERROR_NONE                  Successful
 * @retval      #SENSOR_ERROR_INVALID_PARAMETER     Invalid parameter
 * @retval      #SENSOR_ERROR_IO_ERROR				I/O error
 * @retval      #SENSOR_ERROR_OPERATION_FAILED      Operation failed
 *
 * @see sensor_motion_facedown_set_cb()
 */
int sensor_motion_facedown_unset_cb(sensor_h sensor);

/**
 * @}
 *
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

