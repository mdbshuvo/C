#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "struct.h"
#include "title.h"

void new()
{
    FILE *fptr;
    account *ptr;
    history *hptr;
    int id_chooser,j;
    char choice,*current_time;
    system("cls");
    display(NEW ACCOUNT WINDOW);

    hptr=(history *)malloc(sizeof(history));                 //use of malloc function

    fptr=fopen("history","r");
    if(fptr==NULL)
    {
        fptr=fopen("history","w");
        fclose(fptr);
        id_chooser=200010;
    }
    else
    {
        for(j=0;!feof(fptr);j++)
            fread(hptr,sizeof(history),1,fptr);
        fclose(fptr);
        id_chooser=hptr->account_id+1;
        j--;
    }
    hptr=(history *)realloc(hptr,sizeof(history));          //use of realloc
    ptr=(account *)calloc(1,sizeof(account));

    ptr->account_id=id_chooser;
    hptr->account_id=id_chooser;
    printf("The account id for this account is : %d\n\
           [ This is given by the server and unchangable! ]\n",ptr->account_id);

    printf("Enter the new customer name: ");
    gets(ptr->name);
    //puts(ptr->name);
    strcpy(hptr->name,ptr->name);
    printf("Enter the age of \"%s\": ",ptr->name);
    scanf("%d",&ptr->age);
    getchar();      //to avoid the problem of newline character left by scanf function.

    printf("Enter the present address of \"%s\": ",ptr->name);
    gets(ptr->address.present);
    printf("Enter the permanent address of \"%s\": ",ptr->name);
    gets(ptr->address.permanent);
    printf("Enter the account type(\"K\" for keep / \"B\" for borrow) \n\
    [N.B: You will be able to only KEEP or BORROW using a single account] \
    : ");
    ptr->account_type=getchar();
    printf("Enter the amount of first transaction: ");
    scanf("%f",&ptr->account_balance);
    getchar();
    printf("Enter the email address of the customer (if not any then enter a blank space) : ");
    gets(ptr->email);
    printf("Enter the phone number of this account: ");
    gets(ptr->contact_no);

    //Getting the creation real time.

    strcpy(ptr->created,current_time);

    strcpy(hptr->account_creation,current_time);
    strcat(hptr->account_creation,": The account was created.");
    strcpy(hptr->account_deletion,"This account is still active.");

    hptr->account_log_quantity=0;

    printf("\n\t Confirm to add this account? [ some data are not rechangable ] [Y/N]\n");
    printf("INPUT:");
    choice=getchar();
    getchar();
    if(choice=='N') return;

    fptr=fopen("data","a");
    fwrite(ptr,sizeof(account),1,fptr);
    fclose(fptr);
    free(ptr);

    fptr=fopen("history","a");
    fwrite(hptr,sizeof(history),1,fptr);
    fclose(fptr);
    free(hptr);

    printf("\n\t\tProcess ended successfully.\n");
}
