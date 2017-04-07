#ifndef PCREATE_H
#define PCREATE_H

#include "PCB.h"
#include "procqueue.h"

int MAX_PROCESSES = 5000;

PQueue<PCB*> jobQueue;
PQueue<PCB*> readyQueue;
PQueue<PCB*> deviceQueue;
PQueue<PCB*> terminated;

void wait(unsigned timeout) {
    timeout += std::clock();
    while(std::clock() < timeout) continue;
}

void createProcesses() {
    for(int i = 0; i < MAX_PROCESSES; i++) {
        PCB* proc = new PCB;
        wait((unsigned)(rand() % 5));
        jobQueue.enqueue(proc);
    }
}

void startProcesses() {

}


#endif //PCREATE_H
