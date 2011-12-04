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
  FWATCard watcard = office.create( id, (unsigned int)5, card );
  
  // Obtain vending machine location from name server.
  VendingMachine *vm = nameServer.getMachine(id);

  for (unsigned int i = 0; i < numPurchases; i++) {
    yield(mprng(1, 10));
    
    try {
      // Purchase soda. Blocks if no money on card.
      VendingMachine::Status status = vm->buy( flavour, *watcard() );
    } catch (WATCardOffice::Lost) {
    }
  }
}
