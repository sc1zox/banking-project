#ifndef ACCOUNTCREATION_H
#define ACCOUNTCREATION_H

#include <stdio.h>
#include <stdlib.h>

#include "bank.h"
#include "identifier.h"
#include "account.h"
#include "transactions.h"
#include "functions.h"


void accountcreation(Bank myBank);
void deleteaccount(Bank myBank,int Kundennummer);

#endif  
