#include <stdio.h>
#include <stdlib.h>

#include "bank.h"
#include "identifier.h"
#include "account.h"
#include "accountcreation.h"
   
   
   
    int login;
    int token;
    int loginform(Bank myBank){
    do{
    printf("To Login into Accounting System please input your Accountnumber\n");
    scanf("%d",&login);
    Ident actualID=getPerson(myBank,login);
    if(actualID!=NULL && login==actualID->Kundenummer){
        printf("Willkommen %s\n\n",actualID->name);
        token=1;
    }
    else{
        int yesno;

        do{
        printf("Account Number incorrect\n");
        printf("Please choose one of the following options \n");
        printf("1. Account creation\n");
        printf("2. Back to login\n");
        scanf("%d",&yesno);

        switch (yesno)
        {
        case 1:
        accountcreation(myBank);
            break;
        
        case 2:
        printf("Back to login\n");
            printf("-----------\n");
            token=0;
            yesno=1;
            break;
        default:
            printf("Invalid Input please chose a given option\n");
            token=0;
            break;
        }
        }while(yesno!=1);
    }
    }while(token!=1);
    return login;
    }
    