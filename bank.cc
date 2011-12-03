/*
 * CS343 A6 Bank Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <uC++.h>
#include "bank.h"

Bank::Bank(unsigned int numStudents) : num_students(numStudents) {
    accounts = new unsigned int[num_students];

    for (unsigned int i = 0; i < num_students; i++) {
        accounts[i] = 0;
    }
}

Bank::~Bank() {
    delete accounts;
}

void Bank::deposit(unsigned int id, unsigned int amount) {
    accounts[id] += amount;
}

void withdraw(unsigned int id, unsigned int amount) {
    // Something involving futures?
    // Probably internal scheduling, since we don't know if we want to wait until we see accounts[id]
}
