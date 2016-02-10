//timer.h, header file for timer.cpp
//Copyright Ian Parberry, 1999

//Unix implementation by James Burton
//Last updated December 1, 2001

#include <time.h>
#include <sys/time.h>

#ifndef __timer_h__
#define __timer_h__

class Timer{ //game timer class
  private:
    int m_nStartTime; //time that timer was started
  public:
    Timer(); //constructor
    virtual void start(); //start the timer
    virtual int time(); //return the time in ms
    //has interval ms elapsed since start?
    int elapsed(int &start,int interval);
};

#endif
