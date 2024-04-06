#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "identifier.h"

// Forward declaration of Invest to avoid circular dependency
struct Investmentsstruct;
typedef struct Investmentsstruct *Invest;

struct Transaktionsstruct;
typedef struct Transaktionsstruct *Transaction;

struct Identifierstruct;
typedef struct Identifierstruct *Ident;

#include "identifier.h"


struct Accountstruct {
    Transaction *trans;
    int transcount;
    int Kontostand;
    int Kontonummer;
    Invest Investment;
    Ident owner;
    struct Accountstruct *next;
};


typedef struct Accountstruct *Account;

Account newAccount(Ident person);


#endif  // ACCOUNT_H
