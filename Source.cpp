/*CPU Event Scheduler Simulation*/
/*Randomly creates CPU events and prioritizes them.*/
/*Will output to console time of events and the wait time of the user*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>

#include "LinkedListQueue.h"
#include "CPUEvent.h"

using namespace std;

/****Function Prototypes****/
//Randomly assigns values to simulate CPU events
void populate(CPUEvent*);
//FCFS Schedule Algorithm
void firstComeFirstServe(CPUEvent*);
//Round Robin Algorithm
void roundRobin(CPUEvent *, int);
//Event Priority Algorithm
void eventpriority(CPUEvent*);
//SJF Algorithm
void shortestJobFirst(CPUEvent*);
//LJF Algorithm
void longestJobFirst(CPUEvent*);


int main() {
	cout << "Hi\n" << endl;

	//Seeds the random number generator
	srand(time(NULL));

	//Creates and array of CPU events
	CPUEvent schedule[NUMEVENTS];

	//randomly assigns values to simulate CPU events
	populate(schedule);
	
	//Asks for time quantum for Round Robin Algorithm
	int quant;
	cout << "Input Time Quantum: ";
	cin >> quant;
	while (quant < 1) {
		cout << "Invalid Time Quantum" << endl;
		cout << "Input Time Quantum: ";
		cin >> quant;
	}


	//Goes through scheduling algorithms to see runtimes and displays stats
	firstComeFirstServe(schedule);
	roundRobin(schedule, quant);
	eventpriority(schedule);
	shortestJobFirst(schedule);
	longestJobFirst(schedule);
	
	cout << "All simulations complete!\n" << endl;

	return 0;
}

//randomly assigns values to simulate CPU events
void populate(CPUEvent *arr) {
	int i;
	LinkedListQueue<int> q;
	for (i = 0; i < NUMEVENTS; i++) {
		arr[i].setProccess(i);
		arr[i].setBurst(rand() % 101); //Burst set between 0 and 100 ms
		arr[i].rrtemp = arr[i].burst; //used in round robin algorithm
		q.enqueue(i);
	}
	//Then shuffles array to simulate time of event read
	random_shuffle(&arr[0], &arr[NUMEVENTS]);

	//dequeues Queue to shuffled array for a simulated arrival time
	int temp;
	for (i = 0; i < NUMEVENTS; i++) {
		arr[i].setArrival(q.dequeue(temp));
	}
}


void firstComeFirstServe(CPUEvent *arr) {
	//Writes output to FCFSoutput.txt
	ofstream myfile;
	myfile.open("FCFSoutput.txt");

	LinkedListQueue<CPUEvent> q;

	myfile << "First Come, First Serve Algorithm: \n" << endl;
	int i;
	for (i = 0; i < NUMEVENTS; i++) {
		q.enqueue(arr[i]);
	}
	myfile << "Process\t" << "Burst Time\t" << "Arrival Time" << endl;
	CPUEvent temp;
	double wait = 0;
	while (q.size != 1) {
		temp = q.dequeue(temp);
		myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;
		wait = wait + (double)temp.burst;
	}
	//Algorithm does not count last burst time, so last value must be dequeued
	temp = q.dequeue(temp);
	myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;

	myfile << "\nAverage wait time: " << wait / NUMEVENTS << "ms" << endl;
	myfile.close();
}

void roundRobin(CPUEvent *arr, int quant) {
	//Writes output to RoundRobinoutput.txt
	ofstream myfile;
	myfile.open("RoundRobinoutput.txt");

	myfile << "Round Robin Algorithm" << endl;
	LinkedListQueue<CPUEvent> q;

	myfile << "\nTime Quantum: " << quant << " ms"<< endl;

	int i;
	for (i = 0; i < NUMEVENTS; i++) {
		q.enqueue(arr[i]);
	}

	myfile << "Process\t" << "Burst Time\t" << "Arrival Time" << endl;
	CPUEvent temp;
	double wait = 0;
	while(q.size != 1) {
		temp = q.dequeue(temp);
		myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;
		if (temp.burst < quant)
			wait = wait + temp.burst;
		else if (temp.rrtemp >= quant)
			wait = wait + quant;
		else
			wait = wait + temp.rrtemp;
		temp.rrtemp -= quant;
		if (temp.rrtemp > 0) {
			q.enqueue(temp);
		}
	}
	//Algorithm does not count last burst time, so last value must be dequeued
	temp = q.dequeue(temp);
	myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;

	myfile << "\nAverage wait time: " << wait / NUMEVENTS << "ms" << endl;
	myfile.close();
}

void eventpriority(CPUEvent *arr) {
	//Writes output to EventPriorityoutput.txt
	ofstream myfile;
	myfile.open("EventPriorityoutput.txt.txt");

	myfile << "Event Priority Algorithm: \n" << endl;
	LinkedListQueue<CPUEvent> q;

	//randomly creates a user priority list
	int userP[NUMEVENTS];
	int i;
	for (i = 0; i < NUMEVENTS; i++) {
		userP[i] = i;
	}
	random_shuffle(&userP[0], &userP[NUMEVENTS]);

	myfile << "User Priority: ";
	int j;
	for (i = 0; i < NUMEVENTS; i++) {
		myfile << userP[i] << ", ";
		for (j = 0; j < NUMEVENTS; j++) {
			if (userP[i] == arr[j].process) {
				q.enqueue(arr[j]);
			}
		}
	}

	myfile << "\nProcess\t" << "Burst Time\t" << "Arrival Time" << endl;
	CPUEvent temp;
	double wait = 0;
	while (q.size != 1) {
		temp = q.dequeue(temp);
		myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;
		wait = wait + (double)temp.burst;
	}
	//Algorithm does not count last burst time, so last value must be dequeued
	temp = q.dequeue(temp);
	myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;

	myfile << "\nAverage wait time: " << wait / NUMEVENTS << "ms" << endl;
	myfile.close();
}

void shortestJobFirst(CPUEvent *arr) {
	int i,j, first, min;
	CPUEvent temp1;
	for (i = 0; i < NUMEVENTS - 1; i++) {
		min = i;
		for (j = i + 1; j < NUMEVENTS; j++) {
			if (arr[j].burst < arr[min].burst) {
				min = j;
			}
		}
		temp1 = arr[i];
		arr[i] = arr[min];
		arr[min] = temp1;
	}
	//Writes output to ShortestJobFirstoutput.txt
	ofstream myfile;
	myfile.open("ShortestJobFirstoutput.txt");

	LinkedListQueue<CPUEvent> q;

	myfile << "Shortest Job First Algorithm: \n" << endl;

	for (i = 0; i < NUMEVENTS; i++) {
		q.enqueue(arr[i]);
	}
	myfile << "Process\t" << "Burst Time\t" << "Arrival Time" << endl;
	CPUEvent temp;
	double wait = 0;
	while (q.size != 1) {
		temp = q.dequeue(temp);
		myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;
		wait = wait + (double)temp.burst;
	}
	//Algorithm does not count last burst time, so last value must be dequeued
	temp = q.dequeue(temp);
	myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;

	myfile << "\nAverage wait time: " << wait / NUMEVENTS << "ms" << endl;
	myfile.close();
}

void longestJobFirst(CPUEvent *arr) {
	int i, j, first, max;
	CPUEvent temp1;
	for (i = 0; i < NUMEVENTS - 1; i++) {
		max = i;
		for (j = i + 1; j < NUMEVENTS; j++) {
			if (arr[j].burst > arr[max].burst) {
				max = j;
			}
		}
		temp1 = arr[i];
		arr[i] = arr[max];
		arr[max] = temp1;
	}
	//Writes output to LongesttJobFirstoutput.txt
	ofstream myfile;
	myfile.open("LongestJobFirstoutput.txt");

	LinkedListQueue<CPUEvent> q;

	myfile << "Longest Job First Algorithm: \n" << endl;

	for (i = 0; i < NUMEVENTS; i++) {
		q.enqueue(arr[i]);
	}
	myfile << "Process\t" << "Burst Time\t" << "Arrival Time" << endl;
	CPUEvent temp;
	double wait = 0;
	while (q.size != 1) {
		temp = q.dequeue(temp);
		myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;
		wait = wait + (double)temp.burst;
	}
	//Algorithm does not count last burst time, so last value must be dequeued
	temp = q.dequeue(temp);
	myfile << temp.process << "\t" << temp.burst << "\t\t" << temp.arrival << endl;

	myfile << "\nAverage wait time: " << wait / NUMEVENTS << "ms" << endl;
	myfile.close();
}