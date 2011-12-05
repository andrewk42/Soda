/*
 * CS343 A6 Plant Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <uC++.h>
#include "plant.h"
#include "mprng.h"

extern MPRNG mprng;

// Epic (disgusting) init list
BottlingPlant::BottlingPlant(Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments) :
        prt(prt), ns(nameServer), num_machines(numVendingMachines), max_shipped(maxShippedPerFlavour),
        max_stock(maxStockPerFlavour), delay(timeBetweenShipments) {

    truck = new Truck( prt, ns, *this, num_machines, max_stock );

    stock[0] = stock[1] = stock[2] = stock[3] = 0;

    closing = false;
}

BottlingPlant::~BottlingPlant() {
    // Set signal for Truck
    closing = true;

    // Let the truck call getShipment one more time
    _Accept(getShipment);

    // Wait for Truck to crash
    delete truck;
}

bool BottlingPlant::getShipment(unsigned int cargo[]) {
    cargo[0] = stock[0];
    cargo[1] = stock[1];
    cargo[2] = stock[2];
    cargo[3] = stock[3];

    return closing;
}

void BottlingPlant::main() {
    prt.print(Printer::BottlingPlant, 'S');

    for (;;) {
        // Either terminate or begin a production run
        _Accept(~BottlingPlant) {
            break;
        } else {
            // Simulate generation time
            yield(delay);

            int total = 0;

            // Generate new stock of each flavour
            for (unsigned int i = 0; i < 4; i++) {
                int newStock = mprng(max_shipped);
                stock[i] += newStock;
                total += newStock;
            }

            prt.print(Printer::BottlingPlant, 'G', total);

            // Wait for the Truck to pickup this stock
            _Accept(getShipment);

            stock[0] = stock[1] = stock[2] = stock[3] = 0;
            prt.print(Printer::BottlingPlant, 'P');
        }
    }

    prt.print(Printer::BottlingPlant, 'F');
}
