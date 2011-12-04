/*
 * CS343 A6 Nameserver Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 * The name server’s function is to manage the vending-machine names. The name server is passed the number
 * of vending machines, NumVendingMachines, and the number of students, NumStudents. It begins by logically
 * distributing the students evenly across the vending machines in a round-robin fashion. That is, student id 0
 * is assigned to the first registered vending-machine, student id 1 is assigned to the second registered vending-
 * machine, etc., until there are no more registered vending-machines, and then start again with the first registered
 * vending-machine. Vending machines call VMregister to register themselves so students can subsequently locate
 * them. A student calls getMachine to find a vending machine, and the name server must cycle through the
 * vending machines separately for each student starting from the initial position via modulo incrementing to
 * ensure a student has a chance to visit every machine. The truck calls getMachineList to obtain an array of
 * pointers to vending machines so it can visit each machine to deliver new soda.
 *
 * The name server prints the following information:
 * 
 * State    Meaning                     Additional Information
 * -----    -------                     ----------------------
 * S        starting
 * R        register vending machine    identifier of registering vending machine
 * N        new vending machine         student requesting vending machine, new vending machine
 * F        finished
 */

#ifndef NAMESERVER_H
#define NAMESERVER_H

#include <uC++.h>
#include <vector>
#include "printer.h"
#include "machine.h"

_Task VendingMachine;

_Task NameServer {
    Printer &prt;

    // currStudent is the student that called getMachine.
    unsigned int numVendingMachines, numStudents, currStudent;

    // Used to keep track of which machine a student goes to next.
    std::vector<VendingMachine*> machines;
    int *nextMachine;

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
