/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef __TIZEN_SYSTEM_SENSOR_DOC_H__
#define __TIZEN_SYSTEM_SENSOR_DOC_H__

 /**
 * @ingroup CAPI_SYSTEM_FRAMEWORK
 * @defgroup CAPI_SYSTEM_SENSOR_MODULE Sensor
 * @brief The @ref CAPI_SYSTEM_SENSOR_MODULE API provides sensor types and sensor information
 *
 * @section CAPI_SYSTEM_SENSOR_MODULE_HEADER Required Header
 *   \#include <sensor.h>
 *
 * @section CAPI_SYSTEM_SENSOR_MODULE_OVERVIEW Overview
 * This Sensor API provides sensor types and sensor error types to make use of sensors in the
 * device. A variety of hardware/virtual sensors are typically available on
 * mobile devices.
 * This Sensor API also provides functions for sensor information, such as name, vendor.
 *
 * @section CAPI_SYSTEM_SENSOR_MODULE_FEATURE Related Features
 * This API is related with the following features:\n
 *  - http://tizen.org/feature/sensor.accelerometer\n
 *  - http://tizen.org/feature/sensor.barometer\n
 *  - http://tizen.org/feature/sensor.gyroscope\n
 *  - http://tizen.org/feature/sensor.magnetometer\n
 *  - http://tizen.org/feature/sensor.photometer\n
 *  - http://tizen.org/feature/sensor.proximity\n
 *  - http://tizen.org/feature/sensor.tiltmeter\n
 *  - http://tizen.org/feature/sensor.ultraviolet\n
 *  - http://tizen.org/feature/sensor.temperature\n
 *  - http://tizen.org/feature/sensor.humidity\n
 *  - http://tizen.org/feature/sensor.linear_acceleration\n
 *  - http://tizen.org/feature/sensor.rotation_vector\n
 *  - http://tizen.org/feature/sensor.gravity\n
 *  - http://tizen.org/feature/sensor.heart_rate_monitor\n
 *  - http://tizen.org/feature/sensor.heart_rate_monitor.led_green\n
 *  - http://tizen.org/feature/sensor.heart_rate_monitor.led_ir\n
 *  - http://tizen.org/feature/sensor.heart_rate_monitor.led_red\n
 *  - http://tizen.org/feature/sensor.gyroscope.uncalibrated\n
 *  - http://tizen.org/feature/sensor.magnetometer.uncalibrated\n
 *  - http://tizen.org/feature/sensor.gyroscope_rotation_vector\n
 *  - http://tizen.org/feature/sensor.geomagnetic_rotation_vector\n
 *  - http://tizen.org/feature/sensor.pedometer\n
 *  - http://tizen.org/feature/sensor.sleep_monitor\n
 *  - http://tizen.org/feature/sensor.sleep_detector\n
 *  - http://tizen.org/feature/sensor.stress_monitor\n
 *
 * It is recommended to design feature related codes in your application for reliability.\n
 *
 * You can check if a device supports the related features for this API by using @ref CAPI_SYSTEM_SYSTEM_INFO_MODULE, thereby controlling the procedure of your application.\n
 *
 * To ensure your application is only running on the device with specific features, please define the features in your manifest file using the manifest editor in the SDK.\n
 *
 * More details on featuring your application can be found from <a href="https://developer.tizen.org/development/tools/native-tools/manifest-text-editor#feature"><b>Feature Element</b>.</a>
 *
 */

 /**
 * @ingroup CAPI_SYSTEM_SENSOR_MODULE
 * @defgroup CAPI_SYSTEM_SENSOR_LISTENER_MODULE Sensor Listener
 * @brief The @ref CAPI_SYSTEM_SENSOR_LISTENER_MODULE API provides functions to start/stop sensors and receive sensor events.
 *
 * @section CAPI_SYSTEM_SENSOR_LISTENER_MODULE_HEADER Required Header
 *   \#include <sensor.h>
 *
 * @section CAPI_SYSTEM_SENSOR_MODULE_OVERVIEW Overview
 * This Sensor API provides functions to make use of sensors in the
 * device.  A variety of hardware/virtual sensors are typically available on
 * mobile devices.
 *
 */

 /**
 * @ingroup CAPI_SYSTEM_SENSOR_MODULE
 * @defgroup CAPI_SYSTEM_SENSOR_RECORDER_MODULE Sensor Recorder
 * @brief The @ref CAPI_SYSTEM_SENSOR_RECORDER_MODULE API provides functions to start/stop recording sensor events and read the recorded data.
 *
 * @section CAPI_SYSTEM_SENSOR_RECORDER_MODULE_HEADER Required Header
 *   \#include <sensor.h>
 *
 * @section CAPI_SYSTEM_SENSOR_MODULE_OVERVIEW Overview
 * This Sensor API provides functions to record sensors events in the device.
 * Several sensors are typically available on mobile devices.
 *
 */

/**
 * @ingroup CAPI_SYSTEM_SENSOR_MODULE
 * @defgroup CAPI_SYSTEM_SENSOR_UTILITY_MODULE Sensor Utility
 * @brief The @ref CAPI_SYSTEM_SENSOR_UTILITY_MODULE API provides utility functions.
 *
 * @section CAPI_SYSTEM_SENSOR_UTILITY_MODULE_HEADER Required Header
 * \#include <sensor.h>
 *
 * @section CAPI_SYSTEM_SENSOR_UTILITY_MODULE_OVERVIEW Overview
 * This Sensor API provides utility functions.
 *
 */


#endif // __TIZEN_SYSTEM_SENSORS_DOC_H__
