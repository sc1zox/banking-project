// bank.h

#ifndef BANK_H
#define BANK_H

#include "identifier.h"

// Forward declaration of Invest to avoid circular dependency
struct Investmentsstruct;
typedef struct Investmentsstruct *Invest;

struct Bankstruct {
    char *name;
    Ident last;
    Ident first;
    Invest Investment;
    int costumercount;
    int accountcount;
    int Kundennummer;
    int countsaved;
    int lastAssignedTransnumber;
};

typedef struct Bankstruct *Bank;

Bank newBank(char *name);

#endif  // BANK_H
