/*
 * CS343 A6 Card Header
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

/* Specifications:
 * The WATCard manages the money associated with a card. When a WATCard is created it has a $0 balance.
 * The courier calls deposit after a funds transfer. A vending machine calls withdraw when a soda is purchased.
 * A student and a vending machine call getBalance to determine the balance. FWATCard is a future pointer to a
 * student’s WATCard for synchronizing access to the WATCard between the student and the courier.
 */

#ifndef CARD_H
#define CARD_H

class WATCard {
    WATCard( const WATCard & );			// prevent copying
    WATCard &operator=( const WATCard & );
  public:
    WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

typedef Future_ISM<WATCard *> FWATCard;		// future WATCard pointer

#endif
