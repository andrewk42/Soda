/*
 * CS343 A6 Office Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 * The WATCardOffice is an administrator task used by a student to transfer funds from its bank account to their
 * WATCard to buy a soda. Initially, the WATCard office creates a fixed-sized courier pool with numCouriers
 * courier tasks to communicate with the bank. (Additional couriers may not be created after the WATCardOffice
 * begins.) A student performs an asynchronous call to create to create a “real” WATCard through the output
 * parameter card with an initial balance. A future WATCard is returned and sufficient funds are subsequently
 * obtained from the bank (see Parent task) via a courier to satisfy the transfer request. A student performs an
 * asynchronous call to transfer when its WATCard indicates there is insufficient funds to buy a soda. A future
 * WATCard is returned and sufficient funds are subsequently obtained from the bank (see Parent task) via a
 * courier to satisfy the transfer request. The WATCard office is empowered to transfer funds from a student’s
 * bank-account to its WATCard by sending a request through a courier to the bank. Each courier task calls
 * requestWork, blocks until a Job request is ready, and then receives the next Job request as the result of the call.
 * As soon as the request is satisfied (i.e., money is obtained from the bank), the courier updates the student’s
 * WATCard. There is a 1 in 6 chance a courier loses a student’s WATCard after the update. When the card is lost,
 * the exception WATCardOffice::Lost is inserted into the future rather than making the future available.
 *
 * The WATCard office prints the following information:
 * State    Meaning                         Additional Information
 * -----    -------                         ----------------------
 * S        starting
 * W        courier rendezvous complete
 * C        creation rendezvous complete    student id, transfer amount
 * T        transfer rendezvous complete    student id, transfer amount
 * F        finished
 *
 *   If a courier has lost a student’s WATCard during a transfer (see WATCardOffice::Courier), the
 * exception WATCardOffice::Lost is raised when the future value is accessed. In this case, the student must delete
 * the old WATCard and create a new WATCard via the WATCardOffice with a $5 balance. Note, a courier can lose
 * a student’s WATCard during the transfer for the new create so this issue can occur repeatedly.
 *   When a WATCard is created it has a $0 balance. The courier calls WATCard::deposit after a funds transfer.
 * The typedef FWATCard is a future pointer to a student’s WATCard for synchronizing access to the WATCard between
 * the student and the courier.
 *   A courier calls Bank::withdraw to transfer money on behalf of the WATCard office for a specific student. The
 * courier waits until enough money has been deposited, which may require multiple deposits.
 *
 * A courier prints the following information:
 * State    Meaning                         Additional Information
 * -----    -------                         ----------------------
 * S        starting
 * t        start funds transfer            student requesting transfer, amount of transfer
 * T        complete funds transfer         student requesting transfer, amount of transfer
 * F        finished
 */

#ifndef OFFICE_H
#define OFFICE_H

#include <vector>
#include <queue>
#include "card.h"
#include "printer.h"
#include "bank.h"

_Task WATCardOffice {
    struct Job {				    // marshalled arguments and return future
        struct Args {
            unsigned int sid, amount;
            WATCard *c;

            Args(unsigned int sid, unsigned int amount, WATCard *c) : sid(sid), amount(amount), c(c) {}
        };

        Args args;				    // call arguments (YOU DEFINE "Args")
        FWATCard result;			// return future
        Job( Args args ) : args( args ) {}
    };

    // Worker Task
    _Task Courier { 
        Printer &prt;
        Bank &b;
        WATCardOffice &office;
        Job *j;

        void main();
      public:
        Courier(Printer &prt, Bank &b, WATCardOffice &office) : prt(prt), b(b), office(office) {}
        ~Courier() {}
    };

    Printer &prt;
    Bank &b;
    std::vector<Courier*> couriers;
    std::queue<Job*> requests;

    void main();
  public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    FWATCard create( unsigned int sid, unsigned int amount, WATCard *&card );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};



#endif
