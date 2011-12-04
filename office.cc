/*
 * CS343 A6 Office Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include "office.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : prt(prt), b(bank) {
    for (unsigned int i = 0; i < numCouriers; i++) {
        couriers.push_back(new Courier(prt, bank, *this));
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

        } else {

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

void WATCardOffice::Courier::main() {
    // Print start msg
    prt.print(Printer::Courier, 'S');

    for (;;) {
        _Accept(~Courier) {
            break;
        } else {
            // Get the next queued job
            j = office.requestWork();

            // Withdraw money from the bank, may block here
            b.withdraw(j->args.sid, j->args.amount);

            // Update the WATCard with money obtained from Bank
            j->args.c->deposit(j->args.amount);
        }
    }

    // Print finish msg
    prt.print(Printer::Courier, 'F');
}
