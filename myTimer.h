/***********************************************************
*myTimer.h
*By: Julian Stanton
*Assignment: Final Project
*Due 5/11/20
*
*Program Description:
*	Simple class for keeping track of non blocking delays that
*	I originally made for arduino projects
*
*************************************************************/


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