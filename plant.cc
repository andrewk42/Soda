/*
 * CS343 A6 Plant Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <uC++.h>
#include "plant.h"

// Epic init list
BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
        prt(prt), ns(nameServer), num_machines(numVendingMachines), max_shipped(maxShippedPerFlavour),
        delay(timeBetweenShipments) {}

void BottlingPlant::main() {
    prt.print(Printer::BottlingPlant, 'S');


    prt.print(Printer::BottlingPlant, 'F');
}
