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

#pragma once // _SENSOR_LOG_H_

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

#define PRINT(fmt, args...) \
	do { \
		printf(fmt, ##args); \
	} while(0)

static const char *err_str(int err)
{
	switch (err)
	{
		case SENSOR_ERROR_NONE:
			return KGRN"SENSOR_ERROR_NONE"RESET;
		case SENSOR_ERROR_IO_ERROR:
			return KRED"SENSOR_ERROR_IO_ERROR"RESET;
		case SENSOR_ERROR_INVALID_PARAMETER:
			return KRED"SENSOR_ERROR_INVALID_PARAMETER"RESET;
		case SENSOR_ERROR_NOT_SUPPORTED:
			return KRED"SENSOR_ERROR_NOT_SUPPORTED"RESET;
		case SENSOR_ERROR_PERMISSION_DENIED:
			return KRED"SENSOR_ERROR_PERMISSION_DENIED"RESET;
		case SENSOR_ERROR_OUT_OF_MEMORY:
			return KRED"SENSOR_ERROR_OUT_OF_MEMORY"RESET;
		case SENSOR_ERROR_NOT_NEED_CALIBRATION:
			return KRED"SENSOR_ERROR_NOT_NEED_CALIBRATION"RESET;
		case SENSOR_ERROR_OPERATION_FAILED:
			return KRED"SENSOR_ERROR_OPERATION_FAILED"RESET;
		default:
			return KRED"UNDEFINED ERROR"RESET;
	}
}

static const char *result_str(int err) {
	if (!err) 	return KGRN"[PASS]"RESET;
	else 		return KRED"[FAIL]"RESET;
}
