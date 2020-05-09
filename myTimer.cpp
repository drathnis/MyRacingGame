// 
// 
// 

#include "myTimer.h"

MyTimer::MyTimer(milliseconds delay) {

    interval = delay;
    msLast = (milliseconds)0;

}
bool MyTimer::isItTime() {

    

    milliseconds ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        );



    if (ms - msLast >= interval) {
        msLast = ms;
        return true;
    }


    return false;
}

void MyTimer::reset() {

    milliseconds ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        );

    msLast = ms;

}

void MyTimer::setInterval(milliseconds in) {
    interval = in;
}

MyTimer::MyTimer() {
    interval = (milliseconds)100;
    msLast = (milliseconds)0;
}