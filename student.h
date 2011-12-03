/*
 * CS343 A6 Student Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 *   A Student’s function is to periodically buy some of their favourite soda from a vending machine (a bottle costs
 * whatever the vending machine is charging). Each student is passed an id in the range [0, NumStudents) for
 * identification.
 *   A student begins by selecting a random number of bottles to purchase [1, MaxPurchases], a
 * random favourite flavour [0, 3], creates a WATCard via the WATCardOffice with a $5 balance, and obtains the
 * location of a vending machine from the name server. A student terminates after purchasing all the soda initially
 * selected. Before each attempt to buy a soda, a student yields a random number of times in the range [1, 10]. A
 * student then attempts to buy a bottle of soda from the vending machine. Since the vending machine only takes
 * “real” money, the student may have to block until the amount transfered from the WATCardOffice appears on
 * their WATCard.
 *   If a courier has lost a student’s WATCard during a transfer (see WATCardOffice::Courier), the
 * exception WATCardOffice::Lost is raised when the future value is accessed. In this case, the student must delete
 * the old WATCard and create a new WATCard via the WATCardOffice with a $5 balance. Note, a courier can lose
 * a student’s WATCard during the transfer for the new create so this issue can occur repeatedly.
 *   If the vending machine delivers a bottle of soda, the student drinks it and attempts another purchase.
 * If the vending machine indicates there is insufficient funds, a student transfers the current vending-machine
 * soda-cost plus $5 to their WATCard via the WATCard office. If the vending machine is out of the student’s
 * favourite flavour, the student must obtain a new vending machine from the name server. (Hence, a student may
 * busy wait among vending machines until its specific soda appears from the bottling plant.)
 *
 * A student prints the following information:
 * State    Meaning                         Additional Information
 * -----    -------                         ----------------------
 * S        starting                        favourite soda, number of bottles to purchase
 * V        selecting vending machine       identifier of selected vending machine
 * B        bought a soda                   WATCard balance
 * L        WATCard lost
 * F        finished
 */

#ifndef STUDENT_H
#define STUDENT_H

_Task Student {
    Printer &prt;
    NameServer &nameServer;
    WATCardOffice &office;
    unsigned int id, maxPurchases;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif
