/*
 * Copyright (c) 2016 Samsung Electronics Co., Ltd All Rights Reserved
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

#ifndef __SENSOR_TYPES_INTERNAL_H__
#define __SENSOR_TYPES_INTERNAL_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SENSOR_DATA_VALUE_SIZE
#define SENSOR_DATA_VALUE_SIZE 16
#endif

typedef enum {
	SENSOR_EXT_WEAR_STATUS = 0xA000, /* Checks whether the user is wearing the device or not */
	SENSOR_EXT_WEAR_ON_MONITOR,      /* Detects if the user puts on the device */
	SENSOR_EXT_NO_MOVE_DETECTOR,     /* Detects if the device has been stopped for a while */
	SENSOR_EXT_RESTING_HR,           /* Checks the user's heart-rate with a given interval */
	SENSOR_EXT_STEP_LEVEL_MONITOR,   /* Monitors power-steps, active time, and inactive time */
	SENSOR_EXT_EXERCISE,             /* Monitors walking, running, or hiking exercises */
	SENSOR_EXT_EXERCISE_HR,          /* Monitors the heart-rate during any exercise */
	SENSOR_EXT_WORKOUT,              /* Monitors elliptical, indoor cycling, rowing, stepper workouts */
	SENSOR_EXT_CYCLE_MONITOR,        /* Monitors cycling exercise */
	SENSOR_EXT_STAIR_TRACKER,        /* Monitors stair climbing exercise */
} sensor_type_ex_e;

#ifndef SENSOR_PEDOMETER_DATA_DIFFS_SIZE
#define SENSOR_PEDOMETER_DATA_DIFFS_SIZE	20
#endif

typedef struct {
	int accuracy;
	unsigned long long timestamp;
	int value_count;	/* value_count == 8 */
	float values[SENSOR_DATA_VALUE_SIZE];
	/* values = {step count, walk step count, run step count,
	             moving distance, calorie burned, last speed,
	             last stepping frequency (steps per sec),
	             last step status (walking, running, ...)} */
	/* Additional data attributes (not in sensor_data_t)*/
	int diffs_count;
	struct differences {
		int timestamp;
		int steps;
		int walk_steps;
		int run_steps;
		int walk_up_steps;
		int walk_down_steps;
		int run_up_steps;
		int run_down_steps;
		float distance;
		float calories;
		float speed;
	} diffs[SENSOR_PEDOMETER_DATA_DIFFS_SIZE];
} sensor_pedometer_data_s;

#ifndef SENSOR_EXERCISE_GPS_LOG_SIZE
#define SENSOR_EXERCISE_GPS_LOG_SIZE 100	/* what is the real upper bound? */
#endif

typedef enum {
	SENSOR_EXERCISE_RESULT = 0,
	SENSOR_EXERCISE_AUTO_PAUSE,
	SENSOR_EXERCISE_GPS_STATUS,
	SENSOR_EXERCISE_INITIAL_LOCATION,
} sensor_exercise_callback_e;

typedef struct {
	int accuracy;
	unsigned long long timestamp;
	sensor_exercise_callback_e callback_mode;

	/* State info */
	int32_t auto_pause;
	int32_t gps_status;
	float latitude;
	float longitude;

	/* Exercise result */
	float distance;
	float inc_distance;
	float dec_distance;
	float flat_distance;
	uint32_t inc_time;
	uint32_t dec_time;
	uint32_t flat_time;
	float altitude;
	float max_altitude;
	float min_altitude;
	float speed;
	float max_speed;
	float avg_speed;
	float calorie;
	uint32_t steps;

	/* GPS */
	uint32_t location_count;
	struct _location {
		float latitude;
		float longitude;
		float altitude;
		float speed;
		uint32_t elapsed_time;
		uint32_t accuracy;
		float distance;
	} location[SENSOR_EXERCISE_GPS_LOG_SIZE];
} sensor_exercise_data_s;

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_TYPES_INTERNAL_H__ */
