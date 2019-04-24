#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "struct.h"
#include "search.h"
#include "title.h"

enum verification{NO,YES};

void delete(int indicator)
{
    FILE *fptr;
    account *ptr;
    history *hptr;
    int i,j;
    char choice,*current_time;

    system("cls");
    display(DELETE WINDOW);
    ptr=(account *)calloc(100,sizeof(account));

    //read section.
    fptr=fopen("data","r");
    if(fptr==NULL)
    {
        printf("There is nothing on this server please input a new account first.\n");
        return;
    }
    else
    {
        for(j=0;!feof(fptr);j++)
            fread((ptr+j),sizeof(account),1,fptr);
        fclose(fptr);
        j--;
    }
    if(indicator==-1)       //if no indicator value passed from search
    {
        printf("You need to find the account first.\n\
                press enter to go to SEARCH WINDOW.\n");
        getchar();
        indicator=search('D');
    }
    if(indicator==-1)       //if search was not finished properly.
    {
        printf("Couldnot find the item to delete!\n");
        return;
    }

    system("cls");
    display(DELETE WINDOW);
    //starting the deleting.

    if((ptr+indicator)->account_balance!=0)
    {
        printf("Cannot delete the account . Please finish your transaction with our bank first!\n");
        return;
    }

    printf("Are you sure you want to delete the account \"%s\" ?(warning! this process cannot be undone.)[Y/N]\n\
    \nINPUT:\t",(ptr+indicator)->name);
    while(YES)
    {
        choice=getchar();
        getchar();
        if(choice=='Y'||choice=='y') break;
        else if(choice=='N'||choice=='n')
        {
            printf("Account deletion aborted.\n");
            return;
        }
        else printf("Please enter correct command!\n");
    }

    //Taking the deletion history
    fptr=fopen("history","r+");
    hptr=(history *)malloc(sizeof(history));
    for(;;)
    {
        fread(hptr,sizeof(history),1,fptr);
        if(hptr->account_id==(ptr+indicator)->account_id)
        {
            fseek(fptr,-sizeof(history),SEEK_CUR);
            strcpy(hptr->account_deletion,current_time);
            strcat(hptr->account_deletion,": The account was deleted.");
            fwrite(hptr,sizeof(history),1,fptr);
            fclose(fptr);
            free(hptr);
            break;
        }
    }

    for(i=indicator;i<j;i++)
    {
        *(ptr+i)=*(ptr+i+1);
    }
    j--;

    //write section
    fptr=fopen("data","w");
    if(fptr==NULL)
    {
        printf("ERROR- The data couldnot be accessed!\n");
        exit(0);
    }
    else
    {
        for(i=0;i<j;i++)
            fwrite((ptr+i),sizeof(account),1,fptr);
        fclose(fptr);
    }
    free(ptr);
    printf("Process ended successfully.\n");
}
