/*
 * CS343 A6 Parent Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <uC++.h>
#include "mprng.h"
#include "parent.h"

extern MPRNG mprng;

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) : prt(prt), b(bank) {
    num_students = numStudents;
    delay = parentalDelay;

    prt.print(Printer::Parent, 'S');
}

Parent::~Parent() {}

void Parent::main() {
    unsigned int child, gift;

    MAIN: for (;;) {
        _Accept(~Parent) {
            break MAIN;
        } else {
            // Non-random delay before transferring a gift
            yield(delay);

            // Calculate student to award
            child = mprng(num_students-1);

            // Calculate random gift between [$1, $3]
            gift = mprng(1, 3);

            // Deposit gift with student
            b.deposit(child, gift);
            prt.print(Printer::Parent, 'D', child, gift);
        }
    }

    prt.print(Printer::Parent, 'F');
}
