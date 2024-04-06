#include <stdio.h>
#include <stdlib.h>

#include "identifier.h"
#include "account.h"
#include "transactions.h"
#include "investments.h"

static int lastAssignedKontonummer = 10;


Account newAccount(Ident person) {
    if (person == NULL) {
        printf("error");
        exit(-1);
    }

    Account newAcc = malloc(sizeof(struct Accountstruct));
    newAcc->trans = malloc(sizeof(struct Transaktionsstruct));
    newAcc->Kontostand = 0;
    newAcc->Kontonummer = ++lastAssignedKontonummer;
    newAcc->Investment=initialize();
    newAcc->owner = person;
    newAcc->transcount = 0;
    newAcc->next = NULL; 

    return newAcc;
}
