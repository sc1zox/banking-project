#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bank.h"
#include "identifier.h"
#include "account.h"
#include "transactions.h"
#include "functions.h"
#include "investments.h"

void safebank(Bank myBank) {
    FILE* file = fopen("bank.txt", "w");
    if (file != NULL) {
        // Write bank name
        fprintf(file, "%s\n", myBank->name);

        // Write Kundennummer and countsaved
        fprintf(file, "%d %d %d\n", myBank->Kundennummer, myBank->countsaved,myBank->lastAssignedTransnumber);

        // Write Bitcoin investment
        fprintf(file, "%d %.2f\n", myBank->Investment->bitcoin->amount, myBank->Investment->bitcoin->bitcoinValue);

        // Write Ethereum investment
        fprintf(file, "%d %.2f\n", myBank->Investment->ethereum->amount, myBank->Investment->ethereum->ethereumValue);

        // Write Babitzka investment
        fprintf(file, "%d %.2f\n", myBank->Investment->babitzka->amount, myBank->Investment->babitzka->babitzkaValue);

        printf("Successfully saved bank %s with %d customers.\n", myBank->name, myBank->countsaved);
        fclose(file);
    } else {
        printf("Error: Unable to open file for writing.\n");
    }
}

Bank readBank() {
    FILE* file = fopen("bank.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return NULL;
    }

    // Read bank name
    char* name = malloc(20 * sizeof(char)); 
    if (name == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }
    fscanf(file, "%s", name);

     // Allocate memory for new bank
    Bank newBanktmp = newBank(name);

    // Read Kundennummer and countsaved
    fscanf(file, "%d",&(newBanktmp->Kundennummer));
    fscanf(file, "%d",&(newBanktmp->countsaved));
    fscanf(file, "%d",&(newBanktmp->lastAssignedTransnumber));

    // Read Bitcoin investment
    fscanf(file, "%d %f", &(newBanktmp->Investment->bitcoin->amount), &(newBanktmp->Investment->bitcoin->bitcoinValue));

    // Read Ethereum investment
    fscanf(file, "%d %f", &(newBanktmp->Investment->ethereum->amount), &(newBanktmp->Investment->ethereum->ethereumValue));

    // Read Babitzka investment
    fscanf(file, "%d %f", &(newBanktmp->Investment->babitzka->amount), &(newBanktmp->Investment->babitzka->babitzkaValue));

    fclose(file);
    return newBanktmp;
}

//splitting up the data in different files for readability
void safeperson(Ident p) {
    FILE *file = fopen("person.txt", "a");
    if (file != NULL) {
        // Write Kundenummer
        fprintf(file, "%d\n", p->Kundenummer);
        
        // Write name
        fprintf(file, "%s\n", p->name);

        // Write Wohnort
        fprintf(file, "%s\n", p->Wohnort);

        // Write PLZ and alter
        fprintf(file, "%d\n", p->PLZ);

        fprintf(file, "%d\n", p->alter);

        fclose(file);
    } else {
        printf("Error: Unable to open file for writing.\n");
    }
}

void safeaccount(Ident p){

        FILE* file = fopen("account.txt", "a");

        if (file != NULL) {

        // Write Account details
        fprintf(file, "%d\n", p->Account->Kontonummer);
        fprintf(file, "%d\n", p->Account->Kontostand);
        fprintf(file, "%d\n", p->Account->transcount);

        } else {
        printf("Error: Unable to open file for writing.\n");
    }
}
void safetrans(Ident p, char* data){

        char filename[200];
        sprintf(filename,"%s.txt",data);

        FILE* file = fopen(filename, "a");

        if (file != NULL) {

        // Write trans array elements -> Kundennummer von absender und dann empfänger -> muss gelesen und mit funktion gesucht werden
        for (int i = 0; i < p->Account->transcount; i++) {
            fprintf(file, "%d %d %d %d\n",p->Account->trans[i]->sentby->Kundenummer,p->Account->trans[i]->receiver->Kundenummer,p->Account->trans[i]->id,p->Account->trans[i]->value);
        }

        } else {
        printf("Error: Unable to open file for writing.\n");
    }
}
void safeinvest(Ident p){

        FILE* file = fopen("invest.txt", "a");

        if (file != NULL) {
        // Write Investments
        fprintf(file, "%d %.2f\n", p->Account->Investment->bitcoin->amount, p->Account->Investment->bitcoin->bitcoinValue);
        fprintf(file, "%d %.2f\n", p->Account->Investment->ethereum->amount, p->Account->Investment->ethereum->ethereumValue);
        fprintf(file, "%d %.2f\n", p->Account->Investment->babitzka->amount, p->Account->Investment->babitzka->babitzkaValue);

        } else {
        printf("Error: Unable to open file for writing.\n");
    }
}  

Ident* readperson(int count) {
    FILE *file = fopen("person.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return NULL;
    }

    Ident *users = malloc(count * sizeof(Ident));
    if (users == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        int kundennummer, plz, age;
        char wohnort[20];
        char* vorname=malloc(20*sizeof(char));
        char* nachname=malloc(20*sizeof(char));

        fscanf(file,"%d",&kundennummer);
        fscanf(file,"%s",vorname);
        fscanf(file,"%s",nachname);
        fscanf(file,"%s",wohnort);
        fscanf(file,"%d",&plz);
        fscanf(file,"%d",&age);


    char* whitespace=" ";
    char* name = malloc((strlen(vorname) + strlen(nachname) + strlen(whitespace)+ 1) * sizeof(char));
    strcpy(name, vorname);
    strcat(name, whitespace);
    strcat(name, nachname);

        users[i] = mkid(name, wohnort, age, plz);
        if (users[i] == NULL) {
            printf("Error: Failed to create Ident struct for user %d.\n", i);
            fclose(file);
            for (int j = 0; j < i; j++) {
                free(users[j]); // Free memory allocated for previous users
            }
            free(users);
            return NULL;
        }
        users[i]->Kundenummer = kundennummer;
    }
    fclose(file);
    return users;
}



void readaccount(Ident* user,int count){
    FILE *file = fopen("account.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }
    for(int i=0;i<count;i++){
    giveAccount(user[i]);
    fscanf(file,"%d",&user[i]->Account->Kontonummer);
    fscanf(file,"%d",&user[i]->Account->Kontostand);
    fscanf(file,"%d",&user[i]->Account->transcount);

    }
    fclose(file);

}

void readinvest(Ident* user,int count){
    FILE *file = fopen("invest.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }
    for(int o=0;o<count;o++){
    Invest i=user[o]->Account->Investment;
    fscanf(file,"%d",&i->bitcoin->amount);
    fscanf(file,"%f",&i->bitcoin->bitcoinValue);
    fscanf(file,"%d",&i->ethereum->amount);
    fscanf(file,"%f",&i->ethereum->ethereumValue);
    fscanf(file,"%d",&i->babitzka->amount);
    fscanf(file,"%f",&i->babitzka->babitzkaValue);
    }

    fclose(file);
}

void readtrans(Bank mybank, Ident user, int fileindex) {
    char filename[50];
    sprintf(filename, "accounttrans%d.txt", fileindex);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    printf("Reading transactions...\n");

    int Absender, Empfaenger, id, value;

    // Loop until the end of file or a read error occurs
    while (fscanf(file, "%d %d %d %d", &Absender, &Empfaenger, &id, &value) == 4) {
        
        Ident sender = getPerson(mybank, Absender);
        Ident receiver = getPerson(mybank, Empfaenger);

        if (sender == NULL || receiver == NULL) {
            printf("Error: Sender or receiver not found.\n");
            continue; // Skip this transaction or handle the error as appropriate
            }

        Transaction transaction = newTrans(mybank,value, sender, receiver);
        transaction->id = id;
                Transactionmemory(mybank, user->Kundenummer);
                printf("%d\n",user->Account->transcount);
                user->Account->trans[user->Account->transcount++] = transaction;
    }

    if (feof(file)) {
        
    } else {
        printf("Error reading file.\n");
    }

    fclose(file);
}

void loaddata(Bank myBank) {
    if (myBank == NULL) {
        printf("Error: Invalid bank.\n");
        return;
    }
    int count=myBank->countsaved;
    printf("Number of customers: %d\n", count);

    Ident* arrayofperson = readperson(count);
    if (arrayofperson == NULL) {
        printf("Error: Failed to read person data.\n");
        return;
    }
    for(int i=0;i<count;i++){
    LegeKundean(myBank,arrayofperson[i]);
    }

    for(int i=0;i<count;i++){

    readaccount(arrayofperson,count);
    readinvest(arrayofperson,count);
        
    if(arrayofperson[i]->Account->transcount>0){
            arrayofperson[i]->Account->transcount=0;
            readtrans(myBank,arrayofperson[i],i+1);
        }
    }
    free(arrayofperson);
}
