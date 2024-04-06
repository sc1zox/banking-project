#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include "bank.h"
#include "identifier.h"
#include "account.h"
#include "transactions.h"


void giveAccount(Ident person);
Ident getPerson(Bank b,int Kundenummer);
void makeTrans(Bank b,int Absender,int Empfänger,int value);
void printtransactions(Ident person);
void LegeKundean(Bank myB,Ident person);
void PrintCostumerData(Bank b);
Account getAccount(Bank b,int Kundennummer);
Transaction* Transactionmemory(Bank b,int K);
void depositMoney(Bank b,int K, int value);
void withdrawMoney(Bank b,int K,int value);
int GetCostumerCount(Bank b);
void accountcreation(Bank myBank);
#endif  
