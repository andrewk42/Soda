/*
 * CS343 A6 Machine Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 *   A vending machine’s function is to sell soda to students at some cost. Each vending machine is passed an id
 * in the range [0, NumVendingMachines) for identification, MSRP price for a bottle of soda, and the maximum
 * number of bottles of each flavour in a vending machine. A new vending machine is empty (no stock) and begins
 * by registering with the name server. A student calls buy to obtain one of their favourite sodas. If the specified
 * soda is unavailable or the student has insufficient funds to purchase the soda, buy returns STOCK or FUNDS,
 * respectively; otherwise, the student’s WATCard is debited by the cost of a soda and buy returns BUY.
 *
 *   Periodically, the truck comes by to restock the vending machines with new soda from the bottling plant. Re-
 * stocking is performed in two steps. The truck calls inventory to return a pointer to an array containing the amount
 * of each kind of soda currently in the vending machine. The truck uses this information to transfer into each ma-
 * chine as much of its stock of new soda as fits; for each kind of soda, no more than MaxStockPerFlavour per
 * flavour can be added to a machine. If the truck cannot top-up a particular flavour, it transfers as many bottles as
 * it has (which could be 0). After transferring new soda into the machine by directly modifying the array passed
 * from inventory, the truck calls restocked to indicate the operation is complete. The vending machine cannot
 * accept buy calls during restocking. The cost member returns the cost of purchasing a soda for this machine. The
 * getId member returns the identification number of the vending machine. You define the public type Flavours to
 * represent the different flavours of soda.
 *
 * A vending machine prints the following information:
 * State    Meaning                         Additional Information
 * -----    -------                         ----------------------
 * S        starting                        cost per bottle
 * r        start reloading by truck
 * R        complete reloading by truck
 * B        student bought a soda           flavour of soda purchased, amount remaining of this flavour
 * F        finished
 */

#ifndef MACHINE_H
#define MACHINE_H

#include "nameserver.h"
#include "card.h"
#include "printer.h"

_Task NameServer;

_Task VendingMachine {
    Printer &prt;
    NameServer &nameserver;
    unsigned int id, sodaCost, maxStock;
    int stockCount[4];
    void main();
  public:
    enum Flavours { PINK, ORGANGE, GREEN, BLUE }; 			// flavours of soda
    enum Status { BUY, STOCK, FUNDS };		// purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};


#endif
