#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bank.h"
#include "investments.h"

Bank newBank(char *name) {
    if (name == NULL) {
        printf("error");
        exit(-1);
    }
    Invest newInvest=createInvest(10);
    Bank new = malloc(sizeof(struct Bankstruct));
    new->name = name;
    new->costumercount = 0;
    new->accountcount = 0;
    new->countsaved = 0;
    new->Investment=newInvest;
    new->Kundennummer=1001;
    new->lastAssignedTransnumber=0;
    
    return new;
}

