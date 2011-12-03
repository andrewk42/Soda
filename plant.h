/*
 * CS343 A6 Plant Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 * The bottling plant periodically produces random new quantities of each flavour of soda,
 * [0, MaxShippedPerFlavour] per flavour. The bottling plant is passed the number of vending machines,
 * NumVendingMachines, the maximum number of bottles of each flavour generated during a production run
 * and subsequently shipped, MaxShippedPerFlavour, the maximum number of bottles of each flavour in a
 * vending machine MaxStockPerFlavour, and the length of time between shipment pickups by the truck,
 * TimeBetweenShipments. It begins by creating a truck, performing a production run, and distributing these
 * bottles to initialize the registered vending machines using the truck. To simulate a production run of soda, the
 * bottling plant yields for TimeBetweenShipments times (not random). The truck calls getShipment to obtain a
 * shipment from the plant (i.e., the production run), and the shipment is copied into the cargo array passed by
 * the truck. getShipment returns true if the bottling plant is closing down and cargo is not changed, and false
 * otherwise with the shipment copied into the cargo array passed by the truck. The bottling plant does not start
 * another production run until the truck has picked up the current run.
 *
 * The bottling plant prints the following information:
 * State    Meaning                         Additional Information
 * -----    -------                         ----------------------
 * S        starting
 * G        generating soda                 bottles generated in production run
 * P        shipment picked up by truck
 * F        finished
 */

#ifndef PLANT_H
#define PLANT_H

_Task BottlingPlant {
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif
