/***
Event Header. Contains CPU Event structure.
***/

#ifndef CPUEVENT_H
#define CPUEVENT_H
#include <iostream>

#include "LinkedListQueue.h"

using namespace std;

const int NUMEVENTS = 20; //Number of CPU events

//CPU Events class. Contains timings for each event
class CPUEvent {

public:

	int process; //the job ID
	int burst;
	int arrival;
	int rrtemp; // helper temporary integer for round robin algorithm

	CPUEvent();
//	~Event();
	
	void setProccess(int);
	void setBurst(int);
	void setArrival(int);
	int getProcess();
	int getBurst();
	int getArrival();
	bool compareBurstShort(CPUEvent, CPUEvent);
	bool compareBurstLong(CPUEvent, CPUEvent);

};

//Constructor
CPUEvent::CPUEvent() {
	process = burst = arrival = 0;
}

//Setters and Getters
void CPUEvent::setProccess(int p) {
	process = p;
}

void CPUEvent::setBurst(int b) {
	burst = b;
}

void CPUEvent::setArrival(int a) {
	arrival = a;
}

int CPUEvent::getProcess() {
	return process;
}

int CPUEvent::getBurst() {
	return burst;
}

int CPUEvent::getArrival() {
	return arrival;
}

/***comparison functions to pass to priority queues***/
bool CPUEvent::compareBurstShort(CPUEvent a, CPUEvent b) {
	if (a.burst <= b.burst)
		return true;
	return false;
}

bool CPUEvent::compareBurstLong(CPUEvent a, CPUEvent b) {
	if (a.burst >= b.burst)
		return true;
	return false;
}

#endif
