#include <stdio.h>
#include <stdlib.h>

#include "bank.h"
#include "identifier.h"
#include "account.h"
#include "transactions.h"
#include "functions.h"
#include "accountcreation.h"
#include "login.h"
#include "investments.h"
#include "safeprogram.h"


int main() {
    

    Bank myBank;

    int choice;
    int subchoice;
    int subchoice2;

    int loginnumber;
    int token;
    int loadingchoice;


    do
    {
        printf("Loading Menu\n");
        printf("----------------\n");
        printf("1. Load Bank Data \n");
        printf("2. Load Costumer Data\n");
        printf("3. proceed to login\n");
        scanf("%d",&loadingchoice);

        switch (loadingchoice)
        {
        case 1:
            myBank=readBank();
            if(myBank->name==NULL){
                printf("Please create a Bank\n");
            }
            printf("%s\n",myBank->name);
            break;
        
        case 2:
            loaddata(myBank);
            break;

        case 3:
        if(myBank->accountcount==0){
        printf("Currently no accounts in Bank please create one to proceed\n");
        accountcreation(myBank);
        }
            loadingchoice=3;
            break;
        
        default:
            printf("Invalid Input. Please choose a valid option\n");
            loadingchoice=0;
            break;
        }
    } while (loadingchoice!=3);
    
    
    loginnumber=loginform(myBank);
    Ident actualID=getPerson(myBank,loginnumber);

    if(actualID==NULL || loginnumber==0){
        printf("error in fetching Person please enter valid Informations\n");
    }
    
 do {
        printf("Menu\n");
        printf("-----------------\n");
        printf("Choose your point \n");
        printf("-----------------\n");

        printf("1. Go into Banking Options\n");
        printf("2. Go into Account Data\n");
        printf("3. Show all Accounts\n");
        printf("4. Bank Info\n");
        printf("5. Account management\n");
        printf("6. Manage Stocks and Crypto\n");
        printf("7. Logout\n");
        printf("8. Safe Persons\n");
        printf("9. Load Persons\n");
        printf("10. Data Bankmenu\n");
        printf("11. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do{
                    printf("\n Banking Options\n");
                    printf("-------------\n");
                    printf("1. Deposit\n");
                    printf("2. Withdraw\n");
                    printf("3. Transfer\n");
                    printf("4. Go back to main menu\n");

                    scanf("%d",&subchoice);

                    switch (subchoice)
                    {
                    case 1:
                        int deposit;
                        printf("You chose to deposit\n");
                        printf("Please input the amount you want to deposit\n");
                        scanf("%d",&deposit);
                        depositMoney(myBank,loginnumber,deposit);
                        break;

                    case 2:
                        int withdraw;
                        printf("you chose to withdraw\n");
                        printf("Please input the amount you want to withdraw\n");
                        scanf("%d",&withdraw);
                        withdrawMoney(myBank,loginnumber,withdraw);
                        break;

                    case 3:
                        int value;
                        int acc;
                        printf("Please input the recieving persons account number\n");
                        scanf("%d",&acc);
                        printf("Please input the value of the transaction\n");
                        scanf("%d",&value);
                        makeTrans(myBank,actualID->Kundenummer,acc,value);
                        printf("The Money has been sent\n");
                        break;

                    case 4:
                        printf("Exiting to main menu\n");
                        break;

                    default:
                        printf("Invalid Input. Please choose a valid option\n");
                        break;
                    }
                }while(subchoice!=4);
                break;
            case 2:
            do{
                printf("\nAccount Options\n");
                printf("-------------------------\n");
                printf("1. Show account data\n");
                printf("2. Show Account Balance\n");
                printf("3. Show transactions \n");
                printf("4. Show Accountnumber \n");
                printf("5. Go back to main menu\n");

                scanf("%d",&subchoice2);
                Ident owner=getPerson(myBank,loginnumber);
                switch (subchoice2)
                {
                    
                case 1:
                    printf("\n Name: %s \n",owner->name);
                    printf("\n Home Adress: %s\n",owner->Wohnort);
                    printf("\n Age: %d\n",owner->alter);
                    printf("\nPLZ: %d\n",owner->PLZ);
                    break;
                case 2:
                    Invest i=owner->Account->Investment;
                    updateBalance(myBank,owner);
                    printf("Your Account Balance ist : \n\n    %d \n\n",owner->Account->Kontostand);
                    printf("Your CryptoBalance is: \n Bitcoin: %f \n Etherum: %f \n Babitzka: %f \n\n",i->bitcoin->bitcoinValue,i->ethereum->ethereumValue,i->babitzka->babitzkaValue);
                    printf("You have:\n %d Bitcoin \n %d Ethereum\n %d Babitzka \n",i->bitcoin->amount,i->ethereum->amount,i->babitzka->amount);
                    printf("                 \n");
                    break;
                case 3:
                    printtransactions(owner);
                    break;
                case 4:
                    printf("The Accountnumber is: %d\n",owner->Kundenummer);
                    break;
                case 5:
                    printf("Going back to the main menu\n");
                    break;
                default:
                printf("Invalid Input. Please choose a valid option\n");
                    break;
                }
            }while(subchoice2!=5);
            break;
            case 3:
                PrintCostumerData(myBank);
                break;
            case 4:
                int subchoice3;
                do{
                    printf("Bank Information\n");
                    printf("-----------------------\n");
                    printf("1. Show Bank Name\n");
                    printf("2. Show Number of Costumers\n");
                    printf("3. Show Number of accounts\n");
                    printf("4. Go back to menu\n");
                    scanf("%d",&subchoice3);

                    switch (subchoice3)
                    {
                    case 1:
                        printf("The Bank name is: %s\n",myBank->name);
                        break;
                    case 2:
                        printf("The number of costumers is: %d\n",GetCostumerCount(myBank));
                        break;
                    case 3:
                        printf("The number of accounts is: %d\n",myBank->accountcount);
                        break;
                    default:
                        printf("Invalid input please choose a valid option\n");
                        break;
                    }
                }while(subchoice3!=4);
                break;
            case 5:
            int subchoice5;
            do
            {            
                printf("Account Creation\n");
                printf("----------------\n");
                printf("1. Create an account\n");
                printf("2. Delete an existing account\n");
                printf("3. Go to main menu\n");
                scanf("%d",&subchoice5);
                switch (subchoice5)
                {
                case 1:
                accountcreation(myBank);
                loginnumber = loginform(myBank);
                    break;
                
                case 2:
                    deleteaccount(myBank,loginnumber);
                    loginnumber=loginform(myBank);
                    break;

                case 3:
                break;

                default:
                    printf("Invalid Input. Please choose a valid option\n");
                    break;
                }
            }while (subchoice5!=3);                      
                break;

    case 6:
    Ident person=getPerson(myBank,loginnumber);
    int stockCryptoChoice;
    do {
        printf("Stock and Crypto Options\n");
        printf("----------------\n");

        printf("1. Crypto\n");
        printf("2. Stocks\n");
        printf("3. Go to main menu\n");
        scanf("%d", &stockCryptoChoice);

        switch (stockCryptoChoice) {
            case 1:
                // Crypto options
                int subCryptoChoice;
                do {
                    printf("Crypto\n");
                    printf("----------------\n");
                    printf("1. Bitcoin\n");
                    printf("2. Ethereum\n");
                    printf("3. Babitzka\n");
                    printf("4. Go back \n");
                    scanf("%d", &subCryptoChoice);

                    switch (subCryptoChoice) {
                        case 1:
                        int subCryptoChoice2;
                        printf("Bitcoin Menu\n");
                        do{
                            printf("1. Show Bitcoin Value\n");
                            printf("2. Buy Bitcoin\n");
                            printf("3. Sell Bitcoin\n");
                            printf("4. return to main menu\n");
                            scanf("%d", &subCryptoChoice2);

                            switch (subCryptoChoice2)
                            {
                            case 1:
                            printf("Bitcoin Value at the moment is: %f\n and the amount of shares are: %d\n",getFinanceInfoAndShowCopy(myBank,myBank->Investment)->bitcoin->bitcoinValue,myBank->Investment->bitcoin->amount);
                            break;

                            case 2:
                            int amount;
                            int max_amount=person->Account->Kontostand/myBank->Investment->bitcoin->bitcoinValue;
                            printf("Max amount you can buy with your balance: %d\n",max_amount);
                            printf("How many options\n");
                            scanf("%d",&amount);
                            mkInvestCrypto(myBank,loginnumber,amount,subCryptoChoice);
                            break;

                            case 3:
                            int amount2;
                            printf("Max amount you can sell is: %d\n",person->Account->Investment->bitcoin->amount);
                            printf("How many do you want to sell\n");
                            scanf("%d",&amount2);
                            sellInvestCrypto(myBank,loginnumber,amount2,subCryptoChoice);
                            break;

                            case 4:
                            //fallthrough
                            break;

                            default:
                            printf("Invalid Input. Please choose a valid option\n");
                            break;
                            }
                            }while(subCryptoChoice2!=4);
                            break;

                        case 2:
                            int subCryptoChoice3;
                        printf("Ethereum Menu\n");
                        do{
                            printf("1. Show Ethereum Value\n");
                            printf("2. Buy Ethereum\n");
                            printf("3. Sell Ethereum\n");
                            printf("4. return to main menu\n");
                            scanf("%d", &subCryptoChoice3);

                            switch (subCryptoChoice3)
                            {
                            case 1:
                            printf("Ethereum Value at the moment is: %f\n and the amount of shares are: %d\n ",getFinanceInfoAndShowCopy(myBank,myBank->Investment)->ethereum->ethereumValue,myBank->Investment->ethereum->amount);
                            break;

                            case 2:
                            int amount;
                            int max_amount=person->Account->Kontostand/myBank->Investment->ethereum->ethereumValue;
                            printf("Max amount you can buy with your balance: %d\n",max_amount);
                            printf("How many options\n");
                            scanf("%d",&amount);
                            mkInvestCrypto(myBank,loginnumber,amount,subCryptoChoice);
                            break;

                            case 3:
                            int amount2;
                            printf("Max amount you can sell is: %d\n",person->Account->Investment->ethereum->amount);
                            printf("How many do you want to sell\n");
                            scanf("%d",&amount2);
                            sellInvestCrypto(myBank,loginnumber,amount2,subCryptoChoice);
                            break;

                            case 4:
                            //fallthrough
                            break;

                            default:
                            printf("Invalid Input. Please choose a valid option\n");
                            break;
                            }
                            }while(subCryptoChoice3!=4);
                            break;

                        case 3:
                        int subCryptoChoice4;
                        printf("Babitzka Menu\n");
                        printf("----------------\n");
                        printf("WARNING VOLATILE\n");
                        printf("----------------\n");
                        do{
                            printf("1. Show Babitzka Value\n");
                            printf("2. Buy Babitzka\n");
                            printf("3. Sell Babitzka\n");
                            printf("4. return to main menu\n");
                            scanf("%d", &subCryptoChoice4);

                            switch (subCryptoChoice4)
                            {
                            case 1:
                            printf("Babitzka Value at the moment is: %f\n and the amount of shares are: %d\n",getFinanceInfoAndShowCopy(myBank,myBank->Investment)->babitzka->babitzkaValue,myBank->Investment->babitzka->amount);
                            break;

                            case 2:
                            int amount;
                            int max_amount=person->Account->Kontostand/myBank->Investment->babitzka->babitzkaValue;
                            printf("Max amount you can buy with your balance: %d\n",max_amount);
                            printf("How many options\n");
                            scanf("%d",&amount);
                            mkInvestCrypto(myBank,loginnumber,amount,subCryptoChoice);
                            break;

                            case 3:
                            int amount2;
                            printf("Max amount you can sell is %d\n",person->Account->Investment->babitzka->amount);
                            printf("How many do you want to sell\n");
                            scanf("%d",&amount2);
                            sellInvestCrypto(myBank,loginnumber,amount2,subCryptoChoice);
                            break;

                            case 4:
                            //fallthrough
                            break;

                            default:
                            printf("Invalid Input. Please choose a valid option\n");
                            break;
                            }
                            }while(subCryptoChoice4!=4);
                            break;

                        case 4:
                            // No need for break here as it exits the loop
                            break;

                        default:
                            printf("Invalid Input. Please choose a valid option\n");
                            break;
                    }
                } while (subCryptoChoice != 4);
                break;

            case 2:
                // Stock options
                int stockChoice;
                do {
                    printf("10 most popular stocks\n");
                    printf("----------------\n");
                    printf("1. BASF\n");
                    printf("2. NVIDIA\n");
                    printf("3. VW\n");
                    printf("4. SIEMENS\n");
                    printf("5. INTEL\n");
                    printf("6. AMAZON\n");
                    printf("7. TESLA\n");
                    printf("8. SAP\n");
                    printf("9. GAMESTOP\n");
                    printf("10. Go back to main menu\n");
                    scanf("%d", &stockChoice);

                    switch (stockChoice) {
                        case 1:
                            // Implement stock functionality for BASF
                            break;

                        case 2:
                            // Implement stock functionality for NVIDIA
                            break;

                        case 3:
                            // Implement stock functionality for VW
                            break;

                        case 4:
                            // Implement stock functionality for SIEMENS
                            break;

                        case 5:
                            // Implement stock functionality for INTEL
                            break;

                        case 6:
                            // Implement stock functionality for AMAZON
                            break;

                        case 7:
                            // Implement stock functionality for TESLA
                            break;

                        case 8:
                            // Implement stock functionality for SAP
                            break;

                        case 9:
                            // Implement stock functionality for GAMESTOP
                            break;

                        case 10:
                            // If the user chooses to go back to the main menu, set stockChoice to exit the loop
                            break;

                        default:
                            printf("Invalid Input. Please choose a valid option\n");
                            break;
                    }
                } while (stockChoice != 10);
                break;

            case 3:
                // Exit the loop if the user chooses to go back to the main menu
                break;

            default:
                printf("Invalid Input. Please choose a valid option\n");
                break;
        }
    } while (stockCryptoChoice != 3);
    break;

    case 7:
    int logoutChoice;
    do {
        printf("Logout\n");
        printf("----------------\n");
        printf("1. Logout\n");
        printf("2. Go to main menu\n");
        scanf("%d", &logoutChoice);
        switch (logoutChoice) {
            case 1:
                printf("You have been logged out.\n");
                loginnumber=loginform(myBank);
                logoutChoice = 2;
                break;
            case 2:
                // If the user chooses to go to the main menu, set logoutChoice to exit the loop
                logoutChoice = 2;
                break;
            default:
                printf("Invalid Input. Please choose a valid option\n");
                break;
            }
        } while (logoutChoice != 2);
            break;
            
            case 8:
            Ident current=myBank->first;
            char data;
            int i=1;
            while(current!=NULL){

                safeaccount(current);
                safeperson(current);
                char filename[50];
                sprintf(filename,"accounttrans%d",i++);
                safetrans(current,filename);
                
                safeinvest(current);
                
                myBank->countsaved++;
                current=current->next;
            }
            printf("Successfully safed %d Accounts\n",myBank->countsaved);
                break;
            case 9:
               loaddata(myBank);
                    break;     
             
            case 10:
                int safechoice;
                do
                {
                printf("Data Bankmenu\n");
                printf("----------------\n");
                printf("1. Safe Bank\n");
                printf("2. Read Bank\n");
                printf("3. Go to main menu\n");
                scanf("%d", &safechoice);
                switch (safechoice)
                {
                case 1:
                    safebank(myBank);
                    break;

                case 2:
                    Bank bank =readBank();
                    printf("Bank Name: %s\n", bank->name);
                    printf("Kundennummer: %d\n", bank->Kundennummer);
                    printf("Investments:\n");
                    printf("Bitcoin - Amount: %d, Value: %.2f\n", bank->Investment->bitcoin->amount, bank->Investment->bitcoin->bitcoinValue);
                    printf("Ethereum - Amount: %d, Value: %.2f\n", bank->Investment->ethereum->amount, bank->Investment->ethereum->ethereumValue);
                    printf("Babitzka - Amount: %d, Value: %.2f\n", bank->Investment->babitzka->amount, bank->Investment->babitzka->babitzkaValue);
                    break;

                case 3:
                    safechoice = 3;
                    break;

                default:
                    printf("Invalid Input. Please choose a valid option\n");
                    break;
                }
                } while (safechoice!=3);
                
                break;
            case 11:
                printf("Exiting the program\n");
                break;
            default:
                printf("Invalid Input please choose one of the options\n");
                break;
        }
    } while (choice != 11);    

    return 0;
}
