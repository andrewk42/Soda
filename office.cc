/*
 * CS343 A6 Office Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include "office.h"
#include "mprng.h"

extern MPRNG mprng;

/*****************************************************************************
 * WATCardOffice
 ****************************************************************************/

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : prt(prt), b(bank) {
    for (unsigned int i = 0; i < numCouriers; i++) {
        couriers.push_back(new Courier(i, prt, bank, *this));
    }
}

WATCardOffice::~WATCardOffice() {
    for (unsigned int i = 0; i < couriers.size(); i++) {
        delete couriers[i];
    }
}

void WATCardOffice::main() {
    prt.print(Printer::WATCardOffice, 'S');

    for (;;) {
        _Accept(~WATCardOffice) {
            break;
        } or _When (!requests.empty()) _Accept(requestWork) {
        } or _Accept(create) {
        }
    }

    prt.print(Printer::WATCardOffice, 'F');
}

FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount, WATCard *&card) {
    // Package these args for the job
    Job::Args args(sid, amount, card);

    // Create a new job
    Job *j = new Job(args);

    // Queue this job
    requests.push(j);

    // Return job's result as a future
    return j->result;
}

FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
    return NULL;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
    // Get and pop the next queued job
    Job *j = requests.front();
    requests.pop();

    return j;
}


/*****************************************************************************
 * Courier
 ****************************************************************************/

WATCardOffice::Courier::Courier(unsigned int id, Printer &prt, Bank &b, WATCardOffice &office) :
    id(id), prt(prt), b(b), office(office) {}

void WATCardOffice::Courier::main() {
    // Print start msg
    prt.print(Printer::Courier, id, 'S');

    for (;;) {
        _Accept(~Courier) {
            break;
        } else {
            // Get the next queued job
            j = office.requestWork();

            prt.print(Printer::Courier, id, 't');

            // Withdraw money from the bank, may block here
            b.withdraw(j->args.sid, j->args.amount);

            // Update the WATCard with money obtained from Bank
            j->args.c->deposit(j->args.amount);

            // Potentially lose the WATCard
            if (mprng(5) == 0) {
                // Put the exception in the future
                j->result.exception(new WATCardOffice::Lost());
            } else {
                // Else put the card in the future
                j->result.delivery(j->args.c);
            }

            prt.print(Printer::Courier, id, 'T');

            delete j;
        }
    }

    // Print finish msg
    prt.print(Printer::Courier, id, 'F');
}
