#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "identifier.h"
#include "bank.h"


Ident mkid(char *name, char *Wohnort, short alter,int plz) {
    if (name == NULL || Wohnort == NULL || alter == 0 ||plz == 0) {
        printf("error_mkid");
        exit(-1);
    }
    Ident newid = malloc(sizeof(struct Identifierstruct));

    newid->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newid->name, name);

   
    newid->Wohnort = malloc((strlen(Wohnort) + 1) * sizeof(char));
    strcpy(newid->Wohnort, Wohnort);

    newid->Kundenummer = 0;
    newid->alter = alter;
    newid->PLZ = plz;
    newid->next = NULL; // Initialize next to NULL
    newid->previous = NULL;
    return newid;
}

void givePersonKundennummer(Bank mybank,Ident person){

    if(mybank == NULL || person == NULL){
        printf("error Kundennummer, invalid bank or person\n");
        return;
    }
    ++mybank->Kundennummer;
    person->Kundenummer=mybank->Kundennummer;
    
}
