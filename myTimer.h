#ifndef _MY_TIMER_H
#define _MY_TIMER_H


#include <chrono>

using namespace std::chrono;

class MyTimer {

private:

	milliseconds msLast;
	milliseconds interval;

public:
	MyTimer();
	MyTimer(milliseconds in);

	bool isItTime();
	void reset();

	void setInterval(milliseconds in);


};


#endif