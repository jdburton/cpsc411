//timer.cpp, the timer class
//Copyright Ian Parberry, 1999
//
//Unix implementation by James Burton
//Last updated December 1, 2001

#include "Timer.h"

Timer::Timer(){ //constructor
  m_nStartTime=0;
}

void Timer::start(){ //start the timer
	struct timeval t0;
	gettimeofday(&t0,NULL);
	  m_nStartTime=((t0.tv_usec+1000000*t0.tv_sec)+500)/1000;  //time in ms
}

int Timer::time(){ //return the time
	struct timeval t0;
	gettimeofday(&t0,NULL);
  return ((t0.tv_usec+1000000*t0.tv_sec)+500)/1000-m_nStartTime;  //time in ms
}

int Timer::elapsed(int &start,int interval){
  //has interval elapsed from start?
  int current_time=time();
  if(current_time>=start+interval){
    start=current_time; return 1;
  }
  else return 0;
}
