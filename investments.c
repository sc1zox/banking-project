// investments.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "investments.h" 
#include "transactions.h"
#include "identifier.h"
#include "functions.h"
#include "account.h"

BTC mkBitcoin(){

    BTC new=malloc(sizeof(struct Bitcoinstruct));
    new->amount=0;
    new->bitcoinValue=0;
    return new;
}

ETH mkEthereum(){
    ETH new=malloc(sizeof(struct Ethereumstruct));
    new->amount=0;
    new->ethereumValue=0;
    return new;
}

BZK mkBabitzka(){

    BZK new=malloc(sizeof(struct Babitzkastruct));
    new->babitzkaValue=0;
    new->amount=0;
    return new;
}

Invest initialize(void){
    Invest newInvest = malloc(sizeof(struct Investmentsstruct));
    newInvest->bitcoin=mkBitcoin();
    newInvest->babitzka=mkBabitzka();
    newInvest->ethereum=mkEthereum();
    newInvest->babitzka->babitzkaValue=0;
    newInvest->bitcoin->bitcoinValue=0;
    newInvest->ethereum->ethereumValue=0;
    newInvest->Stocks= malloc(10*sizeof(int));

    return newInvest;
}

// Function to create an Invest object and generate random stock prices
Invest createInvest(int maxstocks) {
    Invest newInvest = malloc(sizeof(struct Investmentsstruct));
    newInvest->Stocks = malloc(maxstocks * sizeof(int));
    newInvest->bitcoin= mkBitcoin();
    newInvest->babitzka=mkBabitzka();
    newInvest->ethereum=mkEthereum();


    newInvest->bitcoin->amount=500;
    newInvest->ethereum->amount=500;
    newInvest->babitzka->amount=1000;
    newInvest->bitcoin->bitcoinValue = 1000.0;  // Initial Bitcoin value
    newInvest->ethereum->ethereumValue = 1337.0;  // Initial Ethereum value
    newInvest->babitzka->babitzkaValue = 69.0;   // Initial Babitzka value

    // Seed for random number generation
    srand(time(NULL));

    // Generate random stock prices
    for (int i = 0; i < maxstocks; i++) {
        // Adjust the range of prices according to your needs
        newInvest->Stocks[i] = rand() % 1000;  // Example: random prices between 0 and 999
    }

    return newInvest;
}
void mkinvestStock(Bank mybank, int accountnumber, int stockOption, int amount,int maxstocks,Ident person) {

    Account acc=getAccount(mybank,accountnumber);
    // Check if the stock option is within a valid range
    if (acc->Kontostand< amount*(mybank->Investment->Stocks[stockOption]))
        {
        printf("not enough money in your account please deposit more\n");
        return;
        }
    if (stockOption >= 0 && stockOption < maxstocks) {
        // Update the corresponding stock option in the investments struct
        acc->Investment->Stocks[stockOption] += amount;
        // Perform any other necessary updates or checks based on the stock option
        // For example, you might want to update the bank's balances or perform other operations
    } else {
        // Handle invalid stock option
        printf("Invalid stock option\n");
    }
}

void mkInvestCrypto(Bank myBank,int kundennumber,int amount,int option){

    
    if(amount<1){
        printf("Invalid amount\n");
        return;
    }

    Ident person=getPerson(myBank,kundennumber);

    switch (option)
    {
    case 1:
            if (person->Account->Kontostand < amount * myBank->Investment->bitcoin->bitcoinValue) {
                printf("Not enough funds, please deposit more to proceed\n");
                return;
            } else if (amount > myBank->Investment->bitcoin->amount) {
                printf("Not enough supply\n");
                return;
            } else {
                person->Account->Investment->bitcoin->bitcoinValue += amount * myBank->Investment->bitcoin->bitcoinValue;
                person->Account->Investment->bitcoin->amount += amount;
                person->Account->Kontostand -= amount * myBank->Investment->bitcoin->bitcoinValue;
                myBank->Investment->bitcoin->amount -= amount;
            }
            break;
    case 2:
    if(person->Account->Kontostand<amount*myBank->Investment->ethereum->ethereumValue){
        printf("Not enough funds, please deposit more to proceed\n");
        return;
    }else if (amount > myBank->Investment->ethereum->amount) {
                printf("Not enough supply\n");
                return;
            } 
    else{
        person->Account->Investment->ethereum->ethereumValue+=amount*myBank->Investment->ethereum->ethereumValue;
        person->Account->Investment->ethereum->amount+=amount;
        person->Account->Kontostand-=amount*myBank->Investment->ethereum->ethereumValue;
        myBank->Investment->ethereum->amount-=amount;
    }
        break;
    case 3:
    if(person->Account->Kontostand<amount*myBank->Investment->babitzka->babitzkaValue){
        printf("Not enough funds, please deposit more to proceed\n");
        return;
    }else if (amount > myBank->Investment->babitzka->amount) {
                printf("Not enough supply\n");
                return;
            } 
    else{
        person->Account->Investment->babitzka->babitzkaValue+=amount*myBank->Investment->babitzka->babitzkaValue;
        person->Account->Investment->babitzka->amount+=amount;
        person->Account->Kontostand-=amount*myBank->Investment->babitzka->babitzkaValue;
        myBank->Investment->babitzka->amount-=amount;
    }
        break;

    default:
    printf("Invalid crypto option\n");
        break;
    }
}
void updateBalance(Bank myBank,Ident person){

    person->Account->Investment->bitcoin->bitcoinValue=person->Account->Investment->bitcoin->amount*myBank->Investment->bitcoin->bitcoinValue;
    person->Account->Investment->ethereum->ethereumValue=person->Account->Investment->ethereum->amount*myBank->Investment->ethereum->ethereumValue;
    person->Account->Investment->babitzka->babitzkaValue=person->Account->Investment->babitzka->amount*myBank->Investment->babitzka->babitzkaValue;
    return;
}

void sellInvestCrypto(Bank myBank,int kundennumber,int amount,int option){
    Ident person=getPerson(myBank,kundennumber);
    updateBalance(myBank,person);

    if(amount<1){
        printf("Invalid amount\n");
        return;
    }

    switch (option)
    {
    case 1:
        if(amount>person->Account->Investment->bitcoin->amount){
            printf("Amount exceeds supply\n");
        }
        else{
        person->Account->Investment->bitcoin->bitcoinValue-=amount*myBank->Investment->bitcoin->bitcoinValue;
        person->Account->Kontostand+=amount*myBank->Investment->bitcoin->bitcoinValue;
        person->Account->Investment->bitcoin->amount-=amount;
        myBank->Investment->bitcoin->amount+=amount;
        }
        break;
    case 2:
        if(amount>person->Account->Investment->ethereum->amount){
            printf("Amount exceeds supply\n");
        }
        else{
        person->Account->Investment->ethereum->ethereumValue-=amount*myBank->Investment->ethereum->ethereumValue;
        person->Account->Kontostand+=amount*myBank->Investment->ethereum->ethereumValue;
        person->Account->Investment->ethereum->amount-=amount;
        myBank->Investment->ethereum->amount+=amount;
        }
        break;
    case 3:
        if(amount>person->Account->Investment->babitzka->amount){
            printf("Amount exceeds supply\n");
        }
        else{
        person->Account->Investment->babitzka->babitzkaValue-=amount*myBank->Investment->babitzka->babitzkaValue;
        person->Account->Kontostand+=amount*myBank->Investment->babitzka->babitzkaValue;
        person->Account->Investment->babitzka->amount-=amount;
        myBank->Investment->babitzka->amount+=amount;
        }
        break;

    default:
    printf("Invalid crypto option\n");
        break;
    }
}

Invest getFinanceInfoAndShowCopy(Bank myBank,Invest investment){

    updateCryptoValues(investment);
    Invest new=malloc(sizeof(struct Investmentsstruct));
    new=myBank->Investment;
    new->Stocks=malloc(20*sizeof(int));
    new->Stocks=NULL;
    return new;
}

#include <math.h>

void updateCryptoValues(Invest investment) {
    // Constants for the model
    float mu_bitcoin = 0.0001;  // Drift (average rate of return)
    float sigma_bitcoin = 0.01;  // Volatility (standard deviation of the rate of return)

    float mu2 = (float)rand() / RAND_MAX - 0.15;   
    float sigma2 = (float)rand() / RAND_MAX / 100.0; 
    
    float mu3 = (float)rand() / RAND_MAX - 0.2;    
    float sigma3 = (float)rand() / RAND_MAX / 50.0; 

    // Time step (you can adjust this based on your simulation frequency)
    float dt = 1.0;  

    // Generate random increments using normal distribution
    float etherumIncrement = mu2 * dt + sigma2 * sqrt(dt) * ((float)rand() / RAND_MAX);
    float babitzkaIncrement = mu3 * dt + sigma3 * sqrt(dt) * ((float)rand() / RAND_MAX);
    float bitcoinIncrement = mu_bitcoin * dt + sigma_bitcoin * sqrt(dt) * ((float)rand() / RAND_MAX);

    if (rand() % 2 == 0) {
        etherumIncrement *= -1.0;
    }
    if (rand() % 2 == 0) {
        babitzkaIncrement *= -1.0;
    }
    if (rand() % 2 == 0) {
        bitcoinIncrement *= -1.0;
    }

    // Update crypto values using geometric Brownian motion
    investment->ethereum->ethereumValue *= exp(etherumIncrement);
    investment->babitzka->babitzkaValue *= exp(babitzkaIncrement);
    investment->bitcoin->bitcoinValue *= exp(bitcoinIncrement);
}

