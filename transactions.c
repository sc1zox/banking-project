#include <stdio.h>
#include <stdlib.h>

#include "identifier.h"
#include "transactions.h"
#include "bank.h"

Transaction newTrans(Bank myBank,int value, Ident sentby, Ident receiver) {
    if (value == 0 || sentby == NULL || receiver == NULL) {
        printf("error");
        exit(-1);
    }

    Transaction newTrans = malloc(sizeof(struct Transaktionsstruct));
    newTrans->value = value;
    newTrans->sentby = sentby;
    newTrans->receiver = receiver;
    newTrans->id = ++(myBank->lastAssignedTransnumber);

    return newTrans;
}