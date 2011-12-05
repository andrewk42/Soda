/*
 * CS343 A6 Truck Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 * The truck moves soda from the bottling plant to the vending machines. The truck is passed the number of
 * vending machines, numVendingMachines, and the maximum number of bottles of each flavour in a vending
 * machine maxStockPerFlavour. The truck begins by obtaining the location of each vending machine from the
 * name server. Before each shipment from the bottling plant, the truck yields a random number of times [1, 10]
 * to get a coffee from Tom Hortons. The truck then calls BottlingPlant::getShipment to obtain a new shipment of
 * soda; any soda still on the truck is thrown away as it is past its due date. If the bottling plant is closing down,
 * the truck terminates. The vending machines are restocked in the order given by the name server, until there
 * is no more soda on the truck or the truck has made a complete cycle of all the vending machines; so there is
 * no guarantee each vending machine is completely restocked or the entire complement of vending machines is
 * restocked or all the soda on the truck is used. The truck can only restock up to MaxStockPerFlavour for each
 * flavour in each vending machine (see VendingMachine task).
 *
 * The truck prints the following information:
 * State    Meaning                                 Additional Information
 * -----    -------                                 ----------------------
 * S        starting
 * P        picked up shipment                      total amount of all sodas in the shipment
 * d        begin delivery to vending machine       vending machine id, total amount remaining in the shipment
 * U        unsuccessfully filled vending machine   vending machine id, total number of bottles not replenished
 * D        end delivery to vending machine         vending machine id, total amount remaining in the shipment
 * F        finished
 *
 * States d and D are printed for each vending machine visited during restocking.
 */

#ifndef TRUCK_H
#define TRUCK_H

#include "printer.h"
#include "nameserver.h"
#include "plant.h"

_Task BottlingPlant;

_Task Truck {
    Printer &prt;
    NameServer &ns;
    BottlingPlant &plt;
    VendingMachine **machine_list;
    unsigned int num_machines, max_stock, cargo[4];

    //bool driveOverCampus(int gasRemaining, int tireSize, int targetDeathCount);
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
