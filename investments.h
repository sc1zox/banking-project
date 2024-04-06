#ifndef INVESTMENTS_H
#define INVESTMENTS_H

#include "bank.h"
#include "identifier.h"
#include "functions.h"
#include "account.h"

struct Transaktionsstruct;
typedef struct Transaktionsstruct *Transaction;

typedef struct Bitcoinstruct{
    int amount;
    float bitcoinValue;
}*BTC;

typedef struct Ethereumstruct{
    int amount;
    float ethereumValue;
}*ETH;

typedef struct Babitzkastruct{
    int amount;
    float babitzkaValue;
}*BZK;

typedef struct Investmentsstruct{

    int* Stocks;
    BTC bitcoin;
    ETH ethereum;
    BZK babitzka;

}*Invest;


Invest createInvest(int amount);
BZK mkBabitzka();
ETH mkEthereum();
BTC mkBitcoin();
void mkinvestStock(Bank mybank, int accountnumber, int stockOption, int amount,int maxstocks,Ident person);
void updateCryptoValues(Invest investment);
void mkInvestCrypto(Bank myBank,int kundennumber,int amount,int option);
Invest initialize(void);
Invest getFinanceInfoAndShowCopy(Bank myBank,Invest investment);
void sellInvestCrypto(Bank myBank,int kundennumber,int amount,int option);
void updateBalance(Bank myBank,Ident person);

#endif
