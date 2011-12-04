/*
 * CS343 A6 Office Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <cassert>
#include "office.h"
#include "mprng.h"

extern MPRNG mprng;

/*****************************************************************************
 * WATCardOffice
 ****************************************************************************/

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : prt(prt), b(bank) {
    // Create each courier task
    for (unsigned int i = 0; i < numCouriers; i++) {
        couriers.push_back(new Courier(i, prt, bank, *this));
    }
}

WATCardOffice::~WATCardOffice() {
    unsigned int i;
    Job *j;

    // Signal each Courier to die
    for (i = 0; i < couriers.size(); i++) {
        j = new Job(Job::Args(0, 0, NULL));
        j->terminate = true;

        requests.push(j);

        _Accept(requestWork);
    }

    // Wait for each Courier to actually die
    for (i = 0; i < couriers.size(); i++) {
        delete couriers[i];
    }
}

void WATCardOffice::main() {
    unsigned int id, amount;

    prt.print(Printer::WATCardOffice, 'S');

    for (;;) {
        _Accept(~WATCardOffice) {
            break;
        } or _When (!requests.empty()) _Accept(requestWork) {
            prt.print(Printer::WATCardOffice, 'W');
        } or _Accept(create) {
            // Ensure non-empty queue
            assert(requests.size() > 0);

            // Ensure non-null pointer
            assert(requests.front() != NULL);

            id = requests.front()->args.sid;
            amount = requests.front()->args.amount;

            prt.print(Printer::WATCardOffice, 'C', id, amount);
        } or _Accept(transfer) {
            // Ensure non-empty queue
            assert(requests.size() > 0);

            // Ensure non-null pointer
            assert(requests.front() != NULL);

            id = requests.front()->args.sid;
            amount = requests.front()->args.amount;

            prt.print(Printer::WATCardOffice, 'T', id, amount);
        }
    }

    prt.print(Printer::WATCardOffice, 'F');
}

FWATCard WATCardOffice::makeJob(unsigned int sid, unsigned int amount, WATCard *card) {
    // Package these args for the job
    Job::Args args(sid, amount, card);

    // Create a new job
    Job *j = new Job(args);

    // Queue this job
    requests.push(j);

    // Return job's result as a future
    return j->result;
}

FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount, WATCard *&card) {
    /* WHAT AM I SUPPOSED TO DO TO *card ??? */

    return makeJob(sid, amount, card);
}

FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card) {
    return makeJob(sid, amount, card);
}

WATCardOffice::Job* WATCardOffice::requestWork() {
    // Ensure non-empty queue
    assert(requests.size() > 0);

    // Get and pop the next queued job
    Job *j = requests.front();

    // Ensure non-null pointer
    assert(j != NULL);

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
        // Get the next queued job
        j = office.requestWork();

        // Detect signal from office to break
        if (j->terminate) break;

        prt.print(Printer::Courier, id, 't', j->args.sid, j->args.amount);

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

        prt.print(Printer::Courier, id, 'T', j->args.sid, j->args.amount);

        delete j;
    }

    // Delete the terminate job
    delete j;

    // Print finish msg
    prt.print(Printer::Courier, id, 'F');
}
