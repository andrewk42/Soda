/*
 * CS343 A6 Machine Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <cassert>
#include "machine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int vmid, unsigned int cost,
                    unsigned int maxStockPerFlavour ) : prt(prt), nameserver(nameServer) {
    id = vmid;
    sodaCost = cost;
    maxStock = maxStockPerFlavour;

    for (int i = 0; i < 4; i++) {
        stockCount[i] = 0;
    }

    nameserver.VMregister(this);
}

VendingMachine::~VendingMachine() {}

VendingMachine::Status VendingMachine::buy(VendingMachine::Flavours flavour, WATCard &watcard) {
    if (watcard.getBalance() < sodaCost) {
        return FUNDS;
    } else if (stockCount[flavour] == 0) {
        return STOCK;
    } else {
        watcard.withdraw(sodaCost);
        stockCount[flavour]--;
        prt.print(Printer::Vending, id, 'B', flavour, stockCount[flavour]);
        return BUY;
    }
}

unsigned int *VendingMachine::inventory() {
    prt.print(Printer::Vending, id, 'r');
    return stockCount;
}

void VendingMachine::restocked() {
    for (int i = 0; i < 4; i++) {
        assert(stockCount[i] <= maxStock);
    }
    prt.print(Printer::Vending, id, 'R');
}

_Nomutex unsigned int VendingMachine::cost() {
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
    return id;
}

void VendingMachine::main() {
    prt.print(Printer::Vending, id, 'S', sodaCost);
    for (;;) {
        _Accept(~VendingMachine) {
            break;
        } or _Accept(buy) {
        } or _Accept(inventory) {
            _Accept(restocked);
        }
    }
    prt.print(Printer::Vending, id, 'F');
}
