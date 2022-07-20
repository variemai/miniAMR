#ifndef MONITOR_H_
#define MONITOR_H_

struct periodic_info {
	int timer_fd;
	unsigned long long wakeups_missed;
};

static unsigned long long its = 0;
static unsigned long long accumulator = 0;
static double avg_times_p = 0.0;

static void *monitor(void *arg);
static void wait_period(struct periodic_info *info);
static int make_periodic(unsigned int period, struct periodic_info *info);

#endif // MONITOR_H_
