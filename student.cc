/*
 * CS343 A6 Student Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <uC++.h>
#include "mprng.h"
#include "student.h"

#include <iostream>

extern MPRNG mprng;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int studentId,
unsigned int max ) : prt(prt), nameServer(nameServer), office(cardOffice) {
	id = studentId;
	maxPurchases = max;
}

void Student::main() {
    unsigned int numPurchases = mprng(1, maxPurchases);
    VendingMachine::Flavours flavour = (VendingMachine::Flavours)mprng(3);
    prt.print(Printer::Student, id, 'S', flavour, numPurchases);
	
    // Create watcard w/ $5 balance.
    WATCard *card = new WATCard();
    FWATCard watcard = office.create( id, (unsigned int)20, card );
  
    // Obtain vending machine location from name server.
    VendingMachine *vm = nameServer.getMachine(id);
    prt.print(Printer::Student, id, 'V', vm->getId());

    for (unsigned int i = 0; i < numPurchases; i++) {
        yield(mprng(1, 10));
    
        for (;;) {
            VendingMachine::Status status;
            try {
                status = vm->buy( flavour, *watcard() );
            } catch (WATCardOffice::Lost lost) {
                prt.print(Printer::Student, id, 'L');
                delete card;
                card = new WATCard();
                watcard = office.create( id, (unsigned int)20, card );
                continue; 
            }
            if (status == VendingMachine::BUY) {
                prt.print(Printer::Student, id, 'B', (*watcard()).getBalance());
                break;
            } else if (status == VendingMachine::FUNDS) {
                watcard = office.transfer( id, ((unsigned int)5 + vm->cost()), card);
            } else if (status == VendingMachine::STOCK) {
                vm = nameServer.getMachine(id);
            }
        }
  }
  prt.print(Printer::Student, id, 'F');
}
