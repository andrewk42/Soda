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
