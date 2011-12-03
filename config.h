/*
 * CS343 A6 Configuration Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 *   Comments in the file (from # to the end-of-line), as well as blank lines, are ignored. The constants may appear in
 * any order. Any number of spaces/tabs may appear around a constant name, value or comment. You may assume each
 * constant appears in the configuration file, is syntactically correct, its value is within an appropriate range (i.e., no error
 * checking is required), and only one constant is defined per line. You may have to modify the values in the provided
 * sample file to obtain interesting results when testing.
 * Add only public destructor and private members
 */

#ifndef CONFIG_H
#define CONFIG_H

struct ConfigParms {
    unsigned int sodaCost;                      // MSRP per bottle
    unsigned int numStudents;                   // number of students to create
    unsigned int maxPurchases;                  // maximum number of bottles a student purchases
    unsigned int numVendingMachines;            // number of vending machines
    unsigned int maxStockPerFlavour;            // maximum number of bottles of each flavour stocked
    unsigned int maxShippedPerFlavour;          // number of bottles of each flavour in a shipment
    unsigned int timeBetweenShipments;          // length of time between shipment pickup
    unsigned int parentalDelay;                 // length of time between cash deposits
    unsigned int numCouriers;                   // number of couriers in the pool
};

void processConfigFile( const char *configFile, ConfigParms &cparms );

#endif
