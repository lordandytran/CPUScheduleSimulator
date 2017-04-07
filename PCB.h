#ifndef PCB_H
#define PCB_H

#include <ctime>
#include <sstream>
#include <iomanip>

enum class STATE {NEW, READY, RUNNING, WAITING, TERMINATED};
enum class CYCLE {IDLE, CPU, IO};
unsigned long ID_COUNTER = 0;
unsigned int MAX_EXECUTIONTIME = 120000;

class PCB {
public:
    STATE proc_state;
    unsigned long proc_ID;
    unsigned int priority;
    time_t creation;
    time_t termination;
    CYCLE burst;
    bool IO_Lock;
    unsigned int exec_time;
    unsigned int curr_exec;

    PCB();
    std::string printID();
};
//Function created for redundancy with constructor
PCB* createProcess() {
    return new PCB;
}

PCB::PCB() {
    proc_state = STATE ::NEW;
    proc_ID = ID_COUNTER++;
    priority = (unsigned)(rand() % 100);
    creation = time(0);
    termination = NULL;
    burst = CYCLE::IDLE;
    IO_Lock = true;
    exec_time = (unsigned)(rand() % MAX_EXECUTIONTIME);
    curr_exec = 0;
}

std::string PCB::printID() {
    std::stringstream buffer;
    buffer << "0x" << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << proc_ID;
    return buffer.str();
}

int comparePriority(PCB* p1, PCB* p2) {
    if(p1->priority > p2->priority) {
        return 1;
    }
    if(p1->priority < p2->priority) {
        return -1;
    }
    return 0;
}

int compareSJF(PCB* p1, PCB* p2) {
    if(p1->exec_time < p2->exec_time) {
        return 1;
    }
    if(p1->exec_time > p2->exec_time) {
        return -1;
    }
    return 0;
}

int compareLJF(PCB* p1, PCB* p2) {
    if(p1->exec_time > p2->exec_time) {
        return 1;
    }
    if(p1->exec_time < p2->exec_time) {
        return -1;
    }
    return 0;
}

#endif // PCB_H
