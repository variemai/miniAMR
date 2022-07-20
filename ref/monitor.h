#ifndef MONITOR_H_
#define MONITOR_H_

struct periodic_info {
	int timer_fd;
	unsigned long long wakeups_missed;
};

static void *monitor(void *arg);
static void wait_period(struct periodic_info *info);
static int make_periodic(unsigned int period, struct periodic_info *info);

#endif // MONITOR_H_
