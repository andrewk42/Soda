/*
 * CS343 A6 Driver file
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include <uC++.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include "mprng.h"
#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "office.h"
#include "nameserver.h"
#include "machine.h"

using namespace std;

// Forward declarations
_Monitor Printer;
_Monitor Bank;
_Task Parent;
_Task WATCardOffice;
_Task NameServer;
_Task VendingMachine;


/* The random-number generator is the only permitted global variable.
 * All 1 in N chance rolls are generated using (mprng(N-1) == 0) */
MPRNG mprng;

/*****************************************************************************
 * helper functions...
 ****************************************************************************/

void usage(char *argv[]) {
    cerr << "Usage: "
         << argv[0]
         << " [ config-file [ random-seed (> 0) ] ]"
         << endl;

    exit(EXIT_FAILURE);
}

// Stolen from Peter Buhr
bool convert(int &val, char *buffer) {      // convert C string to integer
    std::stringstream ss(buffer);           // connect stream and buffer
    ss >> dec >> val;                       // convert integer from buffer
    return ! ss.fail() &&                   // conversion successful ?
    // characters after conversion all blank ?
    string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert


/*****************************************************************************
 * uMain
 ****************************************************************************/

void uMain::main() {
    int seed = getpid();
    const char *default_file = "soda.config";
    ConfigParms cfg;

    // Handle bad input.
    if (argc == 1) processConfigFile(default_file, cfg);
    if (argc > 3) {
        usage(argv);
    }

    for (int i = 1; i < argc; i++) {
        if (i == 1) processConfigFile(argv[i], cfg);
        else if ((i == 2 && !convert(seed, argv[i]))) {
            usage(argv);
        }
    }

    if (seed <= 0) {
        usage(argv);
    }

    // Ready to begin
    mprng.seed(seed);

    /* Config test
    cout << "SodaCost: " << cfg.sodaCost << endl
         << "NumStudents: " << cfg.numStudents << endl
         << "MaxPurchases: " << cfg.maxPurchases << endl
         << "NumVendingMachines: " << cfg.numVendingMachines << endl
         << "MaxStockPerFlavour: " << cfg.maxStockPerFlavour << endl
         << "MaxShippedPerFlavour: " << cfg.maxShippedPerFlavour << endl
         << "TimeBetweenShipments: " << cfg.timeBetweenShipments << endl
         << "ParentalDelay: " << cfg.parentalDelay << endl
         << "NumCouriers: " << cfg.numCouriers << endl;*/

    /* MPRNG test
    int N = 10;
    for (int i = 0; i < 20; i++) {
        cout << mprng(1, 3) << endl;
    }*/

    // Create the Printer
    Printer *prt = new Printer(cfg.numStudents, cfg.numVendingMachines, cfg.numCouriers);

    // Create the Bank
    Bank *b = new Bank(cfg.numStudents);

    // Create the Parent
    Parent *par = new Parent(*prt, *b, cfg.numStudents, cfg.parentalDelay);

    // Create the Office (the office creates the Couriers)
    WATCardOffice *office = new WATCardOffice(*prt, *b, cfg.numCouriers);

    // Create the Name Server
    NameServer *nameServer = new NameServer(*prt, cfg.numVendingMachines, cfg.numStudents);

    // Create the Machines
    vector<VendingMachine*> machines;

    for (unsigned int id = 0; id < cfg.numVendingMachines; id++) {
        machines.push_back(new VendingMachine(*prt, *nameServer, id, cfg.sodaCost, cfg.maxStockPerFlavour));
    }

    // Create the Plant (the plant creates the Truck)


    // Create the Students
    //for (int i = 0; i < cfg.numStudents; i++) {
    //  Student *student = new Student(*prt, &nameServer, WATCardOffice &cardOffice, unsigned int id,
    //         unsigned int maxPurchases)
    //}

    // Terminate once all students are finished


    // Delete the Plant


    // Delete the Machines
    for (unsigned int i = 0; i < machines.size(); i++) {
        delete machines[i];
    }

    // Delete the Name Server
    delete nameServer;

    // Delete the Office
    delete office;

    // Delete the Parent
    delete par;

    // Delete the Bank
    delete b;

    // Delete the Printer
    delete prt;

    cout << "end of main" << endl;
}
