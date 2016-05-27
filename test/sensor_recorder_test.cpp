static GMainLoop *mainloop;

static void recorder_cb(sensor_recorder_type_e type, sensor_data_h data, sensor_recorder_error_e error, void *data)
{
	int status;
	if (error < 0) {
		printf("Failed to read data");
		return 0;
	}

	sensor_recorder_get_int(data, EXERCISE_ATTR_STATUS, &status);

	if (mainloop)
		g_main_loop_quit(mainloop);
}

int main(int argc, char *argv[])
{
	sensor_recorder_h recorder;
	sensor_recorder_filter_h filter;
	/* start : a month ago, end : now, anchor : 7 am, interval : 24h, size : 30(1 month) */
	int start, end, anchor, interval, size;
	int type;

	type = SENSOR_RECORDER_EXERCISE;
	mainloop = g_main_loop_new(NULL, FALSE);

	if (sensor_recorder_is_supported(type) < 0) {
		printf("sensor is not supported\n");
		return 0;
	}

	/* if start buttion is pressed */
	if (sensor_recorder_start(type,  SENSOR_RECORDER_OPTION_NONE) < 0) {
		printf("Failed to start recorder\n");
		return 0;
	}

	if (sensor_recorder_create_filter(&filter) < 0) {
		printf("Failed to create filter\n");
		return 0;
	}

	sensor_recorder_filter_set_int(filter, SENSOR_RECORDER_FILTER_START_TIME, start);
	sensor_recorder_filter_set_int(filter, SENSOR_RECORDER_FILTER_END_TIME, end);
	sensor_recorder_filter_set_int(filter, SENSOR_RECORDER_FILTER_ANCHOR_TIME, anchor);
	sensor_recorder_filter_set_int(filter, SENSOR_RECORDER_FILTER_TIME_INTERVAL, interval);
	sensor_recorder_filter_set_int(filter, SENSOR_RECORDER_FILTER_RESULT_SIZE, size);

	if (sensor_recorder_read(type, filter, recorder_cb, NULL) < 0) {
		printf("Failed to read data\n");
		return 0;
	}

	if (sensor_recorder_destroy_filter(filter) < 0) {
		printf("Failed to create filter\n");
		return 0;
	}

	g_main_loop_run(mainloop);
	g_main_loop_unref(mainloop);
	mainloop = NULL;

	/* if stop buttion is pressed */
	if (sensor_recorder_stop(type) < 0) {
		printf("Failed to stop recorder\n");
		return 0;
	}

	return 0;
}

