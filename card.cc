/*
 * CS343 A6 Card Implementation
 * Written by Marina 2 Samuel (m2samuel)
 * and Andrew J Klamut (ajklamut)
 *
 * November 2011
 */

#include "card.h"

WATCard::WATCard() {
    balance = 0;
}

void WATCard::deposit(unsigned int amount) {
    balance += amount;
}

void WATCard::withdraw(unsigned int amount) {
    balance -= amount;
}

unsigned int WATCard::getBalance() {
    return balance;
}
