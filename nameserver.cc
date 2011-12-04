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

    nextMachine = new int[numStudents];
    for (unsigned int i = 0; i < numStudents; i++) {
        nextMachine[i] = i;
    }
    prt.print(Printer::NameServer, 'S');
}

NameServer::~NameServer() {}

void NameServer::VMregister( VendingMachine *machine ) {
    // Ensure non-null pointer
    assert(machine != NULL);

    prt.print(Printer::NameServer, 'R', machines.size());
    machines.push_back(machine);
}

VendingMachine *NameServer::getMachine(unsigned int sid) { 
    currStudent = sid;

    // Ensure reasonable value
    assert(nextMachine[sid] >= 0 && nextMachine[sid] < numVendingMachines);

    int next = nextMachine[sid];
    prt.print(Printer::NameServer, 'N', sid, next);
    prt.print(Printer::Student, sid, 'V', next);
    nextMachine[currStudent] = (nextMachine[currStudent]+1) % numVendingMachines;
    return machines[next]; 
}

void NameServer::main() {
    /*
    for (;;) {
        _Accept(~NameServer) 
            break;
        or _When (machines.size() != numVendingMachines) _Accept(VMregister) { }
        or _When (machines.size() == numVendingMachines) _Accept(getMachine) { 
            nextMachine[currStudent] = nextMachine[currStudent]++ % numVendingMachines;
        }
    }
    */
}
