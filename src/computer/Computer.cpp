#include "Computer.h"

#include <iostream>

using std::cout;
using std::endl;

Computer::Computer() : accumulator(0), ptr(0), status(standby) {}
Computer::Computer(vector<Instruction> bootCode) : bootCode(bootCode), accumulator(0), ptr(0), status(standby) {}

void Computer::setBootCode(vector<Instruction> bc) { bootCode = bc; }
int Computer::getAccumulator() { return accumulator; }
int Computer::getStatus() { return status; }

void Computer::run() {
    while (status != errored && status != stopped) {
        // cout << bootCode[ptr].getOp() << " " << bootCode[ptr].getArg() << endl;
        step();
    }
}

void Computer::step() {
    if (ptr == bootCode.size()) {
        status = stopped;
        return;
    }

    Instruction& currIns = bootCode[ptr];
    // cout << currIns.getOp() << " " << currIns.getArg() << endl;

    if (currIns.getVisited()) {
        // Used to exit out once we've found the first repeated instruction
        status = errored;
        return;
    } else {
        currIns.setVisited();
    }

    opcode op = currIns.getOp();
    switch (op) {
        case 0:
            // NOP
            ptr++;
            break;
        case 1:
            // ACC
            acc(currIns.getArg());
            ptr++;
            break;
        case 2:
            // JMP
            jmp(currIns.getArg());
            break;
    }
}

void Computer::restart() {
    bootCode.clear();
    status = stopped;
    accumulator = 0;
    ptr = 0;
}

void Computer::acc(int inc) { accumulator += inc; }
void Computer::jmp(int idx) { ptr = ptr + idx; }
