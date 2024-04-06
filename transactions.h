#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "identifier.h"
#include "bank.h"

struct Transaktionsstruct {
    int id;
    int value;
    Ident sentby;
    Ident receiver;
};

typedef struct Transaktionsstruct *Transaction;

Transaction newTrans(Bank myBank,int value, Ident sentby, Ident receiver);


#endif  // TRANSACTION_H
