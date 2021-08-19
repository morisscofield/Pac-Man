#include "Stopwatch.h"

Stopwatch::Stopwatch() : startTime_(0), elapsedTime_(0), finalTime_(0), running_(false)
{

}

void Stopwatch::start()
{
	startTime_ = getProcessTime();
	running_ = true;
}

void Stopwatch::stop()
{
	finalTime_ = getTimeElapsed();
	running_ = false;
}

bool Stopwatch::isRunning() const
{
	return running_;
}

float Stopwatch::getTimeElapsed()
{
	if(!running_)
		return finalTime_;

	elapsedTime_ = getProcessTime();
	elapsedTime_ -= startTime_;
	return elapsedTime_;

}

float Stopwatch::getProcessTime()
{
	clock_t time = clock();
	return static_cast <double> (time) / CLOCKS_PER_SEC;
}
