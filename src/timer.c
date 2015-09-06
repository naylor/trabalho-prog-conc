#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

#include "timer.h"

/*
 * Timer Reference: http://www.cplusplus.com/reference/ctime/
 *
 */

timer* start_timer() {
	timer* t = malloc(sizeof(timer));
	gettimeofday(&t->timeval_start, NULL);
	#ifdef __linux__
	#endif
	t->clock_start = clock();
	return t;
}

void stop_timer(timer* t) {
	gettimeofday(&t->timeval_end, NULL);
	#ifdef __linux__
	#endif
	t->clock_end = clock();

	//timeval diff
	t->timeval_diff = (t->timeval_end.tv_sec - t->timeval_start.tv_sec) * 1000.0; // sec to ms
	t->timeval_diff += (t->timeval_end.tv_usec - t->timeval_start.tv_usec) / 1000.0; // us to ms
	#ifdef __linux__
	#else
		t->timespec_diff = 0;
	#endif
	//clock diff
	t->clock_diff = t->clock_end - t->clock_start;
	t->clock_diff_time = ((float) t->clock_diff / CLOCKS_PER_SEC * 1000.0);

	if (1) {
		printf("[timeval] %.9fms\n", t->timeval_diff);
		#ifdef __linux__
		#endif
		printf("[clock] %d ticks -> %.9fms\n", (int) t->clock_diff, t->clock_diff_time);
	}
}
