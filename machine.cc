/*
 * CS343 A6 Machine Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include "machine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int vmid, unsigned int cost,
                    unsigned int maxStockPerFlavour ) : prt(prt), nameserver(nameServer) {
    id = vmid;
    sodaCost = cost;
    stockCount = maxStockPerFlavour;
    nameserver.VMregister(this);
    prt.print(Printer::Vending, id, 'S', sodaCost);
}

VendingMachine::Status VendingMachine::buy(VendingMachine::Flavours, WATCard&) { return BUY; }

void VendingMachine::main() {}
