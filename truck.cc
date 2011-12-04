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
    unsigned int i, *inventory, j, bottles_missing, not_replenished = 0;
    bool unsuccessful = false;

    prt.print(Printer::Truck, 'S');

    // Obtain vending machine locations
    machine_list = ns.getMachineList();

    MAIN: for (;;) {
        // Go to Timmies - buy 1 extra large double double, 1 large triple triple
        yield(mprng(1, 10));

        // Pickup cargo from the Plant
        if (plt.getShipment(cargo)) {
            // If here the Plant is closing down and there is no cargo; terminate
            break MAIN;
        }

        // Print shipment message, requires total bottles in cargo
        prt.print(Printer::Truck, 'P', cargo[0] + cargo[1] + cargo[2] + cargo[3]);

        // Perform delivery to each machine
        STOCKING: for (i = 0; i < num_machines; i++) {
            // Print begin delivery message
            prt.print(Printer::Truck, 'd', i, cargo[0] + cargo[1] + cargo[2] + cargo[3]);

            // Get the current machine's inventory
            inventory = machine_list[i]->inventory();

            // For each soda flavour in this machine
            for (j = 0; j < 4; j++) {
                // Calculate how much of this flavour this machine needs
                bottles_missing = max_stock - inventory[j];

                // Check if we can fully restock
                if (bottles_missing > cargo[j]) {
                    // Give as much as we can
                    inventory[j] += cargo[j];
                    cargo[j] = 0;

                    // Remember we were unsuccessful, and how many are still missing
                    unsuccessful = true;
                    not_replenished += bottles_missing - cargo[j];
                } else {
                    // Give machine the missing amount
                    inventory[j] += bottles_missing;
                    cargo[j] -= bottles_missing;
                }
            }

            // Report if unsuccessful
            if (unsuccessful) {
                prt.print(Printer::Truck, 'U', i, not_replenished);
            }

            // Notify this machine that restocking is complete
            machine_list[i]->restocked();

            // Reset flaggy stuff
            unsuccessful = false;
            not_replenished = 0;

            // Print end delivery message
            prt.print(Printer::Truck, 'D', i, cargo[0] + cargo[1] + cargo[2] + cargo[3]);

            // Probably should stop if all out of cargo
            if (cargo[0] + cargo[1] + cargo[2] + cargo[3] == 0) {
                break STOCKING;
            }
        }
    }

    prt.print(Printer::Truck, 'F');
}
