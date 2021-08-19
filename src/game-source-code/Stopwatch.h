#ifndef STOPWATCH_H_
#define STOPWATCH_H_
#include <ctime>

class Stopwatch
{
public:
	Stopwatch();
	void start();
	void stop();
	float getTimeElapsed();
	bool isRunning() const;
private:
	 float startTime_;
	 float elapsedTime_;
	 float finalTime_;
	 bool running_;
	 float getProcessTime();
};

#endif
