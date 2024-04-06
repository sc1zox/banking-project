#include <stdio.h>
#include <stdlib.h>

#include "bank.h"
#include "identifier.h"
#include "account.h"
#include "transactions.h"


void giveAccount(Ident person){

    Account new=newAccount(person);
    person->Account=new;
}
int GetCostumerCount(Bank b){
    int costumer;
    if(b == NULL){
        printf("error_name\n");
        exit (-1);
    }
    Ident current=b->first;

    while(current!=NULL){
        costumer++;
        current=current->next;
    }
    return costumer;
}
void PrintCostumerData(Bank b){

    if(b == NULL){
        printf("error_name\n");
        exit (-1);
    }
    Ident current=b->first;

    while(current!=NULL){
        printf("----------------\n");
        printf("Account Owner: %s\n",current->Account->owner->name);
        printf("Account Number: %d\n",current->Kundenummer);
        printf("Account balance: %d\n",current->Account->Kontostand);
        printf("Investments Assets: \n");
        printf("----------------\n");
        current=current->next;
    }
}

Account getAccount(Bank b,int Kundennummer){

        if(Kundennummer==0 || b == NULL){
        printf("error_name\n");
        exit (-1);
    }
    Ident current=b->first;

    while(current!=NULL){
        if(current->Kundenummer==Kundennummer){
            return current->Account;
        }
        current=current->next;
    }
    printf("Costumer not found\n");
    return NULL;
}

Ident getPerson(Bank b,int Kundennummer){

    if(Kundennummer==0 || b == NULL){
        printf("error_name\n");
        exit (-1);
    }
    Ident current=b->first;

    while(current!=NULL){
        if(current->Kundenummer==Kundennummer){
            return current;
        }
        current=current->next;
    }
    return NULL;
}


Transaction* Transactionmemory(Bank b,int K){

        Ident p1=getPerson(b,K);
        Transaction *newt1 = realloc(p1->Account->trans, ((p1->Account->transcount)+1) * sizeof(Transaction));
    if (newt1 != NULL) {
        p1->Account->trans = newt1;
        return newt1;
    } else {
        // Handle realloc failure
        printf("Error: Memory reallocation for p1 failed\n");
        exit(-1);
    }
}

void makeTrans(Bank b,int Absender,int Empfaenger,int value){

    Ident p1=getPerson(b,Absender);
    Ident p2=getPerson(b,Empfaenger);

    if(p1 == NULL || p2 == NULL){
        printf("Couldn't find reciever\n");
        return;
    }

       if(p1->Account->Kontostand<value){
        printf("Insufficient Funds\n");
        return;
    }
    
    Transaction t1=newTrans(b,value,p1,p2);

    if(p1==NULL || p2==NULL || t1==NULL){
    printf("error trans");
    EXIT_FAILURE;
    }

    if (p1->Account == NULL || p2->Account == NULL) {
    printf("Error: Invalid Account pointers in makeTrans\n");
    return;
}
 
    p1->Account->Kontostand-=t1->value;
    p2->Account->Kontostand+=t1->value;

        Transactionmemory(b,p1->Kundenummer);
        p1->Account->trans[p1->Account->transcount++] = t1;
    
        Transactionmemory(b,p2->Kundenummer);
        p2->Account->trans[p2->Account->transcount++] = t1;   
}
    
void printtransactions(Ident person){

    printf("Die Transaktionen von %s: \n\n",person->name);
    for(int i=0;i<person->Account->transcount;i++){
        if(person->Account->trans[i]==NULL){
            printf("error in printing trans\n");
        }
        if(person->Account->trans[i]->sentby==person->Account->trans[i]->receiver){
        printf("------------------------------------\n");
        printf("The transaction number is: %d\n\n",person->Account->trans[i]->id);
        printf("The amount which was deposited or withdrawed: %d \n\n",person->Account->trans[i]->value);
        printf("Name of the person: %s \n\n",person->Account->trans[i]->sentby->name);
        printf("Account number of the person: %d \n\n",person->Account->trans[i]->sentby->Kundenummer);
        printf("------------------------------------\n");  
        }
        else{
        printf("------------------------------------\n");
        printf("The transaction number is: %d\n\n",person->Account->trans[i]->id);
        printf("The amount which was sent/received: %d\n\n",person->Account->trans[i]->value);
        printf("The money was sent by %s with account number %d\n\n",person->Account->trans[i]->sentby->name,person->Account->trans[i]->sentby->Kundenummer);
        printf("The money was received by: %s with account number %d\n\n",person->Account->trans[i]->receiver->name,person->Account->trans[i]->receiver->Kundenummer);
        printf("------------------------------------\n");
    }
    printf("No further transactions\n");
    printf("------------------------------------\n");
    }
    if(person->Account->transcount==0){
    printf("No transactions available\n");
    printf("------------------------------------\n"); 
    }
}

void LegeKundean(Bank myB, Ident person) {
    if (myB == NULL || person == NULL) {
        printf("Error: Invalid bank or person.\n");
        exit(EXIT_FAILURE);
    }

    // Add the person to the bank
    if (myB->costumercount == 0) {
        myB->first = person;
        myB->last = person;
        myB->first->previous = NULL;  
        myB->first->next = NULL;
    } else {
        myB->last->next = person;
        person->previous = myB->last;
        person->next = NULL;
        myB->last = person;
    }

    myB->costumercount++;
    myB->accountcount++;
}


void depositMoney(Bank b,int K, int value){

    if(K<0 || value<1){
        printf("falsche eingabe\n");
        return;
    }
    else{
        Ident p=getPerson(b,K);
        p->Account->Kontostand+=value;
        Transactionmemory(b,K);
        Transaction t1=newTrans(b,value,p,p);
        p->Account->trans[p->Account->transcount++]=t1;     
    }
}

void withdrawMoney(Bank b,int K,int value){

    if(K<0 || value<1){
        printf("falsche eingabe\n");
        return;
    }
    else{
        Ident p=getPerson(b,K);
        if(p->Account->Kontostand<value){
            printf("Insufficient Funds\n");
            return;
        }
        else{
        p->Account->Kontostand-=value;
        Transactionmemory(b,K);
        Transaction t1=newTrans(b,value,p,p);
        p->Account->trans[p->Account->transcount++]=t1;    
        }    
    }
}
