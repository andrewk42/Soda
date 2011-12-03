/*
 * CS343 A6 Student Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include "student.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int studentId,
unsigned int max ) : prt(prt), nameServer(nameServer), cardOffice(cardOffice) {
	id = studentId;
	maxPurchases = max;
}

void Student::main() {
  unsigned int numPurchases, flavour;
	
  unsigned int numPurchases = mprng(1, maxPurchases);
  unsigned int flavour = mprng(3);
	
  // Create watcard w/ $5 balance.
  WATCard watcard = new WATCard();
  FWATCard watcard = cardOffice.create( id, 5, WATCard *card );
  
  // Obtain vending machine location from name server.
  VendingMachine *vm = nameServer.getMachine( id );

  for (int i = 0; i < numPurchases; i++) {
    yield(mprng(1, 10));
    
    // Purchase soda. Blocks if no money on card.
    Status vm.buy( flavour, watcard );

  }
}
