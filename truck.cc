/*
 * CS343 A6 Truck Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <uC++.h>
#include "truck.h"
#include "mprng.h"

extern MPRNG mprng;

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines,
    unsigned int maxStockPerFlavour) : prt(prt), ns(nameServer), plt(plant),
    num_machines(numVendingMachines), max_stock(maxStockPerFlavour) {}

void Truck::main() {
    unsigned int i;

    prt.print(Printer::Truck, 'S');

    // Obtain vending machine locations
    machine_list = ns.getMachineList();

    for (;;) {
        // Go to Timmies - buy 1 extra large double double, 1 large triple triple
        yield(mprng(1, 10));

        // Pickup cargo from the Plant
        if (plt.getShipment(cargo)) {
            // If here the Plant is closing down and there is no cargo; terminate
            break;
        }

        // Print shipment message, requires total bottles in cargo
        prt.print(Printer::Truck, 'P', cargo[0] + cargo[1] + cargo[2] + cargo[3]);

        // Perform delivery to each machine
        for (i = 0; i < num_machines; i++) {
            
        }
    }

    prt.print(Printer::Truck, 'F');
}
