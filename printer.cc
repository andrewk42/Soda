/*
 * CS343 A6 Printer Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <uC++.h>
#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) {
    unsigned int i;

    // Initialize private members
    num_students = numStudents;
    num_machines = numVendingMachines;
    num_couriers = numCouriers;

    for (i = 0; i < (5 + numStudents + numVendingMachines + numCouriers); i++) {
        buffer.push_back(BufferSlot());
    }

    // Print static table headers
    cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";

    // Print dynamic table headers
    for (i = 0; i < numStudents; i++) cout << "Stud:" << i << '\t';
    for (i = 0; i < numVendingMachines; i++) cout << "Mach:" << i << '\t';
    for (i = 0; i < numCouriers-1; i++) cout << "Cour:" << i << '\t';
    cout << "Cour:" << numCouriers-1 << endl;

    // Print table header underlines
    unsigned int num_headers = 5 + numStudents + numVendingMachines + numCouriers;

    for (i = 0; i < num_headers-1; i++) cout << "*******\t";
    cout << "*******" << endl;
}

void Printer::print(Kind kind, char state) {
    print(kind, state, -1, -1);
}

void Printer::print(Kind kind, char state, int value1) {
    print(kind, state, value1, -1);
}

void Printer::print(Kind kind, char state, int value1, int value2) {
    switch (kind) {
        case Parent:
            realPrint(0, state, value1, value2);
            return;
        case WATCardOffice:
            realPrint(1, state, value1, value2);
            return;
        case NameServer:
            realPrint(2, state, value1, value2);
            return;
        case Truck:
            realPrint(3, state, value1, value2);
            return;
        case BottlingPlant:
            realPrint(4, state, value1, value2);
            return;
        default:
            cerr << "Fatal: invalid call to Printer::print()" << endl;
            abort();
    }
}

void Printer::print(Kind kind, unsigned int lid, char state) {
    print(kind, lid, state, -1, -1);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1) {
    print(kind, lid, state, value1, -1);
}

void Printer::print(Kind kind, unsigned int lid, char state, int value1, int value2) {
    switch (kind) {
        case Student:
            realPrint(5 + lid, state, value1, value2);
            return;
        case Vending:
            realPrint(5 + num_students + lid, state, value1, value2);
            return;
        case Courier:
            realPrint(5 + num_students + num_machines + lid, state, value1, value2);
            return;
        default:
            cerr << "Fatal: invalid call to Printer::print()" << endl;
            abort();
    }
}

void Printer::realPrint(unsigned int id, char state, int value1, int value2) {
    // Print a line if this call is about to overwrite nonprinted values
    if (buffer[id].state != '\0' && (state != buffer[id].state ||
        value1 != buffer[id].arg1 || value2 != buffer[id].arg2)) {
        flush();
    }

    // Check if this is the finish state, special case
    if (state == 'F') {
        for (unsigned int i = 0; i < buffer.size(); i++) {
            // Print 'F' for the finished item, "..." for the rest
            if (i == id) cout << 'F';
            else cout << "...";

            if (i != buffer.size()-1) cout << '\t';
        }

        cout << endl;

        clearSlot(id);

        return;
    }

    // Normal behaviour
    buffer[id].state = state;

    if (value1 != -1) buffer[id].arg1 = value1;
    if (value2 != -1) buffer[id].arg2 = value2;
}

void Printer::clearSlot(int id) {
    buffer[id].state = '\0';
    buffer[id].arg1 = buffer[id].arg2 = -1;
}

void Printer::flush() {
    // Print something for every item in the buffer
    for (unsigned int i = 0; i < buffer.size(); i++) {
        // Skip this item if it is empty
        if (buffer[i].state == '\0') {
            cout << '\t';
            continue;
        }

        cout << buffer[i].state;

        // Print non-empty arguments
        if (buffer[i].arg1 != -1) cout << ':' << buffer[i].arg1;
        if (buffer[i].arg2 != -1) cout << ',' << buffer[i].arg2;

        // Print the tab if not the last column
        if (i != buffer.size()-1) cout << '\t';

        // Reset this item now that we've printed
        clearSlot(i);
    }

    cout << endl;
}
