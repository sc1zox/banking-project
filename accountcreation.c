#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bank.h"
#include "identifier.h"
#include "account.h"
#include "transactions.h"
#include "functions.h"


void accountcreation(Bank myBank) {
    char* ort = malloc(50 * sizeof(char));  // Allocate space for the strings
    int age;
    char* vorname = malloc(20 * sizeof(char));
    char* nachname = malloc(20 * sizeof(char));
    int plz;
    

    int token1 = 0;
    int token2 = 0;
    int token3 = 0;
    int token4 = 0;
    int token5 = 0;

    printf("--------------\n");

    do {
        printf("Please enter your prename with a maximum of 20 letters\n");
        scanf("%s", vorname);
        if (vorname[0] == '\0') {
            printf("Name incorrect. Please re-enter\n");
        } else {
            token1 = 1;
        }
    } while (token1 != 1);

    do {
        printf("Please enter your family name with a maximum of 20 letters\n");
        scanf("%s", nachname);
        if (nachname[0] == '\0') {
            printf("Name incorrect. Please re-enter\n");
        } else {
            token4 = 1;
        }
    } while (token4 != 1);

    char* whitespace=" ";
    char* name = malloc((strlen(vorname) + strlen(nachname) + strlen(whitespace)+ 1) * sizeof(char));
    
    
    strcpy(name, vorname);
    strcat(name, whitespace);
    strcat(name, nachname);

    do {
        printf("Please enter your age\n");
        scanf("%d", &age);

        if(age>200){
            printf("You can't be that old please re-enter\n");
        }
        else if (age < 18) {
            printf("You have to be 18 to sign up\n");
            token2=0;
        }
        else {
            token2 = 1;
        }
    } while (token2 != 1);

    do {
        printf("Please enter your city of residence with a maximum of 20 letters\n");
        scanf("%s", ort);
        if (ort[0] == '\0') {
            printf("Address incorrect. Please re-enter city of residence\n");
        } else {
            token3 = 1;
        }
    } while (token3 != 1);

    do {
        printf("Please enter your PLZ\n");
        scanf("%d", &plz);
        if (plz == 0) {
            printf("PLZ is incorrect. Please re-enter PLZ\n");
        } else {
            token5 = 1;
        }
    } while (token5 != 1);

    Ident person = mkid(name, ort, age, plz);
    givePersonKundennummer(myBank,person);
    giveAccount(person);
    LegeKundean(myBank, person);
    printf("Account creation successful\n");
    printf("Your new account number is: %d\n", myBank->last->Kundenummer);
    printf("Please remember it for login\n");

    free(ort);  // Free allocated memory
    free(name);
}



void deleteaccount(Bank myBank, int Kundennummer) {
    Ident person = getPerson(myBank, Kundennummer);

    if (person == NULL) {
        printf("Account with Kundenummer %d not found.\n", Kundennummer);
        return;
    }

    if (person->previous != NULL) {
        person->previous->next = person->next;
    } else {
        // The person to be deleted is the first node
        myBank->first = person->next;
    }

    if (person->next != NULL) {
        person->next->previous = person->previous;
    } else {
        // The person to be deleted is the last node
        myBank->last = person->previous;
    }

    free(person);

    myBank->costumercount--;
    printf("Account with Kundenummer %d deleted.\n", Kundennummer);
}

