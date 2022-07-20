/*
 * Copyright (C) 2009 Chris Simmonds (chris@2net.co.uk)
 *
 * This is a demonstration of periodic threads using the Linux timerfd
 * interface which was introduced in GNU libc 2.8 and kernel 2.6.25.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <limits.h>
#include "monitor.h"
#include "proto.h"

int some_val = 1;

static int make_periodic(unsigned int period, struct periodic_info *info)
{
	int ret;
	unsigned int ns;
	unsigned int sec;
	int fd;
	struct itimerspec itval;

	/* Create the timer */
	fd = timerfd_create(CLOCK_MONOTONIC, 0);
	info->wakeups_missed = 0;
	info->timer_fd = fd;
	if (fd == -1)
		return fd;

	/* Make the timer periodic */
	sec = period / 1000000;
	ns = (period - (sec * 1000000)) * 1000;
	itval.it_interval.tv_sec = sec;
	itval.it_interval.tv_nsec = ns;
	itval.it_value.tv_sec = sec;
	itval.it_value.tv_nsec = ns;
	ret = timerfd_settime(fd, 0, &itval, NULL);
	return ret;
}

static void wait_period(struct periodic_info *info)
{
	unsigned long long missed;
	int ret;

	/* Wait for the next timer event. If we have missed any the
	   number is written to "missed" */
	ret = read(info->timer_fd, &missed, sizeof(missed));
	if (ret == -1) {
		perror("read timer");
		return;
	}

	info->wakeups_missed += missed;
}


static void *monitor(void *arg)
{
	struct periodic_info info;

	printf("Thread 1 period 200ms\n");
	make_periodic(200000, &info);
	while (1) {
		wait_period(&info);
        fprintf(stderr,"%llu\n",its);
	}
	return NULL;
}

