/*
 * CS343 A6 Nameserver Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <cassert>
#include "nameserver.h"

using namespace std;

NameServer::NameServer( Printer &prt, unsigned int numVMs, unsigned int sNum ) : prt(prt) {
    numVendingMachines = numVMs;
    numStudents = sNum;

    machines = new VendingMachine *[numVendingMachines];
    currMachine = 0;

    nextMachine = new unsigned int[numStudents];
    for (unsigned int i = 0; i < numStudents; i++) {
        nextMachine[i] = i % numVendingMachines;
    }
}

NameServer::~NameServer() {
    delete[] machines;
    delete[] nextMachine;
}

void NameServer::VMregister( VendingMachine *machine ) {
    // Ensure non-null pointer
    assert(machine != NULL);

    prt.print(Printer::NameServer, 'R', currMachine);
    machines[currMachine++] = machine;
}

VendingMachine *NameServer::getMachine(unsigned int sid) { 
    // Ensure reasonable value
    assert(nextMachine[sid] >= 0 && nextMachine[sid] < numVendingMachines);

    currStudent = sid;
    next = nextMachine[sid];
    return machines[next]; 
}

VendingMachine **NameServer::getMachineList() {
    return NULL;
}

void NameServer::main() {
    prt.print(Printer::NameServer, 'S');
    for (;;) {
        _Accept(~NameServer) {
            break;
        } or _When (currMachine != numVendingMachines) _Accept(VMregister) {
        } or _When (currMachine == numVendingMachines) _Accept(getMachine) {
            prt.print(Printer::NameServer, 'N', currStudent, next);
            nextMachine[currStudent] = (nextMachine[currStudent]+1) % numVendingMachines;
        }
    }
    prt.print(Printer::NameServer, 'F');
}
