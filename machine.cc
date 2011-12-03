/*
 * CS343 A6 Machine Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include "machine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour ) {
}

VendingMachine::Status VendingMachine::buy(VendingMachine::Flavours, WATCard&) { return BUY; }

void VendingMachine::main() {}
