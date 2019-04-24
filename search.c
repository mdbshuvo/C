#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "struct.h"
#include "title.h"

int match_checker(char first[],char second[]);
void make_lower_case(char target[]);

int search(char caller)
{
    FILE *fptr;
    account *ptr;
    int check_list[100],check_list_count=0,i,j,ifinder,account_id;
    char finder[10],choice,*current_time;
    system("cls");
    display(SEARCH WINDOW);

    ptr=(account *)calloc(100,sizeof(account));

    //read section.
    fptr=fopen("data","r");
    if(fptr==NULL) //if the file opening is unsuccessfull.
    {
        printf("There is nothing on this server please input a new account first.\n");
        return -1;
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
    printf("Using what you want to search?\n\
           1. By name (enter \"N\"or \"n\") .\n\
           2. By id (enter \"I\" or \"i\") [This part is sensitive . Choose it if you only know the id].\n\
           3. Enter zero (0) to cancel.\n\
           \nINPUT:\t");
    choice=getchar();
    getchar();
    if(choice=='N'||choice=='n')
    {
        printf("Enter the name or partial name you want to find : ");
        gets(finder);
        for(i=0;i<j;i++)
        {
            if(match_checker((ptr+i)->name,finder)==1)
            {
                check_list[check_list_count]=i;
                check_list_count++;
            }
        }
        printf("->Found %d results.\n",check_list_count);
        if(check_list_count==0)
        {
            printf("\nNo account found.\n");
            free(ptr);
            return -1;
        }
        for(i=0;i<check_list_count;i++)
        {
            printf("%d. %s .\n",i+1,(ptr+check_list[i])->name);
        }
        printf("Enter the index you want to select -- ");
        scanf("%d",&i);
        getchar();
        printf("                name        id  \n\
selected     \"%s\"        %d.\n",(ptr+check_list[i-1])->name,(ptr+check_list[i-1])->account_id);
        printf("Press Enter to go back.\n");
        getchar();
        account_id=(ptr+check_list[i-1])->account_id;
        free(ptr);
        if(caller=='H') return account_id;
        else return check_list[i-1];
    }
    else if(choice=='I'||choice=='i')
    {
        printf("Enter the id you want to find : ");
        scanf("%d",&ifinder);
        getchar();
        for(i=0;i<j;i++)
            if((ptr+i)->account_id==ifinder)
            {
                printf("selected \"%s\" .\n",(ptr+i)->name);
                printf("Press Enter to go back.\n");
                getchar();
                account_id=(ptr+i)->account_id;
                free(ptr);
                if(caller=='H') return account_id;
                else return i;
            }
        printf("Id not found!\n");
        free(ptr);
        return -1;
    }
    else
    {
        printf("Process canceled.\n");
        free(ptr);
        return -1;
    }
}


int match_checker(char first[],char second[])
{
    char first_l[20];
    strcpy(first_l,first);
    make_lower_case(first_l);
    make_lower_case(second);
    int flen=strlen(first),slen=strlen(second),i,j;
    if(flen<slen) return 0;
    if(flen==slen)
    {
        if(strcmp(first_l,second)==0) return 1;
        else return 0;
    }
    for(i=0;i<flen-slen+1;i++)
    {
        for(j=0;j<slen;j++)
        {
            if(first_l[i+j]!=second[j]) break;
        }
        if(j==slen) return 1;
    }
    return 0;
}

void make_lower_case(char target[])
{
    int i;
    for(i=0;target[i]!='\0';i++)
    {
        if(target[i]>='A'&&target[i]<='Z') target[i]+=32;
    }
}
