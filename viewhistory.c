#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include "struct.h"
#include "title.h"
#include "search.h"

void viewhistory(int account_id)
{
    FILE *fptr;
    history *hptr;
    char choice,*current_time;
    int checker_duality=0,i;

    hptr=(history *)calloc(1,sizeof(history));

    system("cls");
    display(HISTORY WINDOW);

    fptr=fopen("history","r");
    if(fptr==NULL) //if the file opening is unsuccessfull.
    {
        printf("There is nothing on this server please input a new account first.\n");
        return;
    }

    if(account_id!=-1)
    {
        if(account_id<101)              //if came with an account index
        {
            FILE *f2ptr;
            account *ptr;
            f2ptr=fopen("data","r");
            ptr=(account *)malloc(sizeof(account));
            for(++account_id;account_id;account_id--)
                fread(ptr,sizeof(account),1,f2ptr);
            account_id=ptr->account_id;
        }
        goto B;
    }

    printf("\t1. Press \"A\" or \"a\" to view all the account history of this bank .\n\
        2. Press \"S\" or\"s\" to view a single account history .\n\
        3. Press zero (0) to cancel .\n\
    INPUT : \n");
    choice=getchar();
    getchar();

    switch (choice)
    {
    case 'A':
    case 'a':
        for(i=1;;i++)
        {
            fread(hptr,sizeof(history),1,fptr);
            if(checker_duality==hptr->account_id) break;
            printf("\n%d. Name : %s\n\
   Account id : %d\n\n\
            %s\n\
            %s\n",i,hptr->name,hptr->account_id,hptr->account_creation,hptr->account_deletion);
            checker_duality=hptr->account_id;
        }
        printf("\n\t Finished reading all the history .\n");
        fclose(fptr);
        free(hptr);
        return;
    case 'S':
    case 's':
        printf("\t1. Press \"E\" or \"e\" to view the history of an existing account .\n\
        2. Press \"D\" or \"d\" to view history of a deleted account .\n\
            [ warning you must know the account id of the deleted account to access it .\n\
    INPUT : ");
        A:
        choice=getchar();
        getchar();
        if(choice=='E'||choice=='e')
        {
            printf("You need to find the account first.\n\
                press enter to go to SEARCH WINDOW.\n");
            getchar();
            account_id=search('H');
            if(account_id==-1)
            {
                printf("\n\t History search interepted. \n");
                return;
            }


            system("cls");
            display(HISTORY WINDOW);
        }
        else if(choice=='D'||choice=='d')
        {
            printf("Enter the deleted account id : ");
            scanf("%d",&account_id);
            getchar();
            fptr=fopen("history","r");
            for(;;)
            {
                fread(hptr,sizeof(history),1,fptr);
                if(hptr->account_id==account_id)
                {
                    printf("\n\tHere is the requested deleted account history :\n\n");
                    printf("Name : %s\n",hptr->name);
                    printf("Account Id : %d\n\n",hptr->account_id);
                    puts(hptr->account_creation);
                    for(i=0;i<hptr->account_log_quantity;i++) puts(hptr->account_log[i]);
                    puts(hptr->account_deletion);
                    fclose(fptr);
                    free(hptr);
                    return;
                }
                if(feof(fptr))
                {
                    printf("Invalid User id.Process failed.\n");
                    free(hptr);
                    fclose(fptr);
                    return;
                }
            }
        }
        else
        {
            printf("Invalid selection.\n\
            INPUT : ");
            goto A;
        }
        break;
    }
    B:
        fptr=fopen("history","r");
        for(;;)
        {
            fread(hptr,sizeof(history),1,fptr);
            if(hptr->account_id==account_id)
            {
                printf("\n\tHere is the requested account log :\n\n");
                printf("Name : %s\n",hptr->name);
                printf("Account Id : %d\n\n",hptr->account_id);
                puts(hptr->account_creation);
                for(i=0;i<hptr->account_log_quantity;i++) puts(hptr->account_log[i]);
                puts(hptr->account_deletion);
                fclose(fptr);
                free(hptr);
                return;
            }
        }
}
