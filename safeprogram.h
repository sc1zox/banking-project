#ifndef SAFEPROGRAM_H
#define SAFEPROGRAM_H

#include <stdio.h>
#include <stdlib.h>

#include "bank.h"
#include "identifier.h"
#include "account.h"
#include "transactions.h"
#include "functions.h"
#include "investments.h"

void safeaccount(Ident p);
void safeperson(Ident p);
void safeinvest(Ident p);
void safetrans(Ident p, char* data);
Ident* readperson(int count);
void readinvest(Ident* user,int count);
void readaccount(Ident* user,int count);
void readtrans(Bank mybank,Ident user,int count);
void loaddata(Bank myBank);
void safebank(Bank myBank);
Bank readBank();

#endif