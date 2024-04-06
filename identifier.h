#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "account.h"
struct Bankstruct;
typedef struct Bankstruct *Bank;

struct Identifierstruct {
    int Kundenummer;
    char *name;
    char *Wohnort;
    int PLZ;
    short alter;
    Account Account;
    struct Identifierstruct *next;
    struct Identifierstruct *previous;
};

typedef struct Identifierstruct *Ident;

Ident mkid(char *name, char *Wohnort, short alter,int plz);
void givePersonKundennummer(Bank mybank,Ident person);


#endif  // IDENTIFIER_H
