#include "quakedef.h"

#define MAX_FRAMERATE 72

double realTime = 0.;
double oldRealTime = 0.;
double host_frameTime = 0.;

void host_init(void)
{

}

bool host_filterTime(float timeDiff)
{
	realTime += timeDiff;

	if (realTime - oldRealTime < 1.0 / MAX_FRAMERATE)
		return false;

	COM_dprintf("Frame! %lf\n", realTime);

	host_frameTime = realTime - oldRealTime;
	oldRealTime = realTime;

	return true;
}

void host_frame()
{

}

void host_shutdown(void)
{

}