/*
 * CS343 A6 Parent Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 * The Parent task periodically gives a random amount of money [$1, $3] to a random student. Before each gift
 * is transfered, the parent yields for parentalDelay times (not random). The parent must check for a call to its
 * destructor to know when to terminate. Since it must not block on this call, it is necessary to use a terminating
 * else on the accept statement. (Hence, the parent is busy waiting for the call to its destructor.)
 *
 * The parent prints the following information:
 * State    Meaning     Additional Information
 * -----    ---------   -----------------------
 * S        starting
 * D        deposit     gift student receiving gift, amount of gift
 * F        finished
 */

#include "printer.h"
#include "bank.h"

_Task Parent {
    Printer &prt;
    Bank &b;
    unsigned int num_students, delay;

    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
    ~Parent();
};
