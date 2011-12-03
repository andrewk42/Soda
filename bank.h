/*
 * CS343 A6 Bank Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 * The Bank is a monitor, which behaves like a server, that manages student-account information for all students.
 * Each student’s account initially starts with a balance of $0. The parent calls deposit to endow gifts to a specific
 * student. A courier calls withdraw to transfer money on behalf of the WATCard office for a specific student. The
 * courier waits until enough money has been deposited, which may require multiple deposits.
 */

#ifndef BANK_H
#define BANK_H

_Monitor Bank {
    unsigned int num_students;
    unsigned int *accounts;
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif
