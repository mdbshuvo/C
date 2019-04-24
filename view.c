#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "struct.h"
#include "search.h"
#include "title.h"

void view(int indicator)
{
    FILE *fptr;
    account *ptr;
    char choice,*current_time;
    int i,j;
    system("cls");
    display(VIEW WINDOW);

    ptr=(account *)calloc(100,sizeof(account));
    fptr=fopen("data","r");
    if(fptr==NULL) //if the file opening is unsuccessfull.
    {
        printf("There is nothing on this server please input a new account first.\n");
        return;
    }
    else
    {
        for(j=0;!feof(fptr);j++)
        {
            fread((ptr+j),sizeof(account),1,fptr);
        }
        fclose(fptr);
        j--;
    }
    if(indicator==-1)
    {
        printf("What do you want to be done?\n\
                1. To view the whole data stored in the server press \"A\" or \"a\" .\n\
                2. To view a single account data press \"S\" or \"s\" .\n\
                3. Enter zero (0) to cancel.\n\
                \nINPUT:\t");
        choice=getchar();
        getchar();
        if(choice=='S'||choice=='s')
        {
            printf("You need to find the account first.\n\
                   press enter to go to SEARCH WINDOW.\n");
            getchar();
            indicator=search('V');
        }
        else if(choice=='A'||choice=='a')
        {
            printf("Here is all the data stored in the server.\n");
            for(i=0;i<j;i++)
            {
                printf("%d.\n",i+1);
                printf("Name: %s\n",(ptr+i)->name);
                printf("Age: %d\n",(ptr+i)->age);
                printf("Account id: %d\n",(ptr+i)->account_id);
                printf("Account creation date : %s\n",(ptr+i)->created);
                printf("Present Address: %s\n",(ptr+i)->address.present);
                printf("Permanent Address: %s\n",(ptr+i)->address.permanent);
                printf("Account type (KEEP or BORROW) : %c\n",(ptr+i)->account_type);
                if((ptr+i)->account_type=='K') printf("Account balance: %.2f tk.\n",(ptr+i)->account_balance);
                else printf("Borrowed money: %.2f tk.\n",(ptr+i)->account_balance);
                printf("E-mail: %s\n",(ptr+i)->email);
                printf("Contact Number : %s",(ptr+i)->contact_no);
            }
            return;
        }
        else
        {
            printf("Process canceled.\n");
            return;
        }

    }
    if(indicator==-1)
    {
        printf("Requested account couldnot be viewed!\n");
    }
    else
    {

        system("cls");
        display(VIEW WINDOW);

        printf("-- Here is the requested account information. --\n");
        printf("Name: %s\n",(ptr+indicator)->name);
        printf("Age: %d\n",(ptr+indicator)->age);
        printf("Account id: %d\n",(ptr+indicator)->account_id);
        printf("Account creation date : %s\n",(ptr+indicator)->created);
        printf("Present Address: %s\n",(ptr+indicator)->address.present);
        printf("Permanent Address: %s\n",(ptr+indicator)->address.permanent);
        printf("Account type (KEEP or BORROW) : %c\n",(ptr+indicator)->account_type);
        if((ptr+indicator)->account_type=='K') printf("Account balance: %.2f tk.\n",(ptr+indicator)->account_balance);
        else printf("Borrowed money: %.2f tk.\n",(ptr+indicator)->account_balance);
        printf("E-mail: %s\n",(ptr+indicator)->email);
        printf("Contact Number : %s",(ptr+indicator)->contact_no);
    }
    free(ptr);
}
