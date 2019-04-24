#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "struct.h"
#include "search.h"
#include "title.h"

void update(int indicator)
{
    FILE *fptr;
    account *ptr;
    history *hptr;
    int i,j,ichoice;
    float amount;
    char choice,*current_time;

    system("cls");
    display(UPDATE WINDOW);

    printf("    [N.B: This window is sensitive of invalid selection.]\n");
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
        j--;
        fclose(fptr);
    }
    if(indicator==-1)       //if no indicator value passed from search
    {
        printf("You need to find the account first.\n\
                press enter to go to SEARCH WINDOW.\n");
        getchar();
        indicator=search('U');
    }
    if(indicator==-1)       //if search was not finished properly.
    {
        printf("Could not find the account!\n");
        return;
    }

    system("cls");
    display(UPDATE WINDOW);
    //history creation
    //Taking the deletion history
    fptr=fopen("history","r+");
    hptr=(history *)malloc(sizeof(history));
    for(;;)
    {
        fread(hptr,sizeof(history),1,fptr);
        if(hptr->account_id==(ptr+indicator)->account_id)
        {
            fseek(fptr,-sizeof(history),SEEK_CUR);
            break;
        }
    }


    //Starting updating.
    printf("    #Press \"B\" or \"b\" to update balance information.\n\
    #Press \"O\" or \"o\" to update other informations.\n\
    #Enter zero (0) to cancel.\n\
    \nINPUT:\t");
    choice=getchar();
    getchar();
    if(choice=='B'||choice=='b')
    {
        if((ptr+indicator)->account_type=='K')
        {
            printf("    Current account balance is %.2f tk.\n\
    Account type: K .\n\n",(ptr+indicator)->account_balance);
            printf("\n\
        1.If you want to withdraw money press \"W\" or \"w\" .\n\
        2.If you want to keep money press \"K\" or \"k\" .\n\
        \nINPUT:\t");
            choice=getchar();
            printf("Enter the amountf tk [0-10000]: ");
            scanf("%f",&amount);
            getchar();
            if(choice=='W'||choice=='w')
            {
                if(amount>(ptr+indicator)->account_balance)
                {
                    printf("Withdrwal amount exceeded the current balance. withdrwal failed!\n");
                    return;
                }
                else if(amount>10000||amount<=0)
                {
                    printf("Withdrwal amount exceeded the maximum withdrwal limit. withdrwal failed!\n");
                    return;
                }
                ((ptr+indicator)->account_balance)-=amount;

                strcpy(hptr->account_log[hptr->account_log_quantity],current_time);
                char temp[30];
                sprintf(temp," : Withdrawed %.2f Taka.",amount);
                strcat(hptr->account_log[hptr->account_log_quantity],temp);
                hptr->account_log_quantity++;
            }
            else if(choice=='K'||choice=='k')
            {
                if(amount>10000||amount<=0)
                {
                    printf("Deposal amount exceeded the maximum deposal limit. deposing failed!\n");
                    return;
                }
                ((ptr+indicator)->account_balance)+=amount;
                strcpy(hptr->account_log[hptr->account_log_quantity],current_time);
                char temp[30];
                sprintf(temp," : Kept %.2f Taka.",amount);
                strcat(hptr->account_log[hptr->account_log_quantity],temp);
                hptr->account_log_quantity++;
            }
            else
            {
                printf("Invalid selection\n");
                return;
            }
            printf("New balance is %.2f tk.\n",(ptr+indicator)->account_balance);
        }
        else if((ptr+indicator)->account_type=='B')
        {
            printf("    Current loan amount is %.2f tk.\n\
    Account type: B .\n\n",(ptr+indicator)->account_balance);
            printf("\n\
        1.If you want to borrow more press \"B\" or \"b\" .\n\
        2.If you want to pay press \"P\" or \"p\" .\n\
        \nINPUT:\t");
            choice=getchar();
            printf("Enter the amountf tk [0-10000]: ");
            scanf("%f",&amount);
            getchar();
            if(choice=='B'||choice=='b')
            {
                if(amount>10000||amount<=0)
                {
                    printf("Borrowing amount exceeded the maximum borrow limit. cannot be borrowed!\n");
                    return;
                }
                ((ptr+indicator)->account_balance)+=amount;
                strcpy(hptr->account_log[hptr->account_log_quantity],current_time);
                char temp[30];
                sprintf(temp," : Borrowed %.2f Taka.",amount);
                strcat(hptr->account_log[hptr->account_log_quantity],temp);
                hptr->account_log_quantity++;
            }
            else if(choice=='P'||choice=='p')
            {
                if(((ptr+indicator)->account_balance)<amount)
                {
                    printf("Payment amount exceeded the current loan. Payment failed!\n");
                    return;
                }
                else if(amount>10000||amount<=0)
                {
                    printf("Payment amount exceeded the maximum Payment limit. payment failed!\n");
                    return;
                }
                ((ptr+indicator)->account_balance)-=amount;
                strcpy(hptr->account_log[hptr->account_log_quantity],current_time);
                char temp[30];
                sprintf(temp," : Paid %.2f Taka.",amount);
                strcat(hptr->account_log[hptr->account_log_quantity],temp);
                hptr->account_log_quantity++;
            }
            else
            {
                printf("Invalid selection\n");
                return;
            }
            printf("New loan amount is %.2f tk.\n",(ptr+indicator)->account_balance);
        }
        else
        {
            printf("Invalid selection . failed to update .\n");
            return;
        }
    }
    else if(choice=='O'||choice=='o')
    {
        printf("Select the index from the following list to upgrade information--\n\
        1.Present address.\n\
        2.Permanent address. \n\
        3.Email address. \n\
        4.Contact Number. \n\
        5.Enter zero (0) to cancel\n\
        [N.B: Some informations like name,age etc are not changable]\n");
        scanf("%d",&ichoice);
        getchar();
        switch (ichoice){
        case 1:
            printf("Your current present address: %s\n",(ptr+indicator)->address.present);
            printf("Enter the new present address: ");
            gets((ptr+indicator)->address.present);
            strcpy(hptr->account_log[hptr->account_log_quantity],current_time);
            strcat(hptr->account_log[hptr->account_log_quantity],": Present address updated.");
            hptr->account_log_quantity++;
            break;
        case 2:
            printf("Your current permanent address: %s\n",(ptr+indicator)->address.permanent);
            printf("Enter the new permanent address: ");
            gets((ptr+indicator)->address.permanent);
            strcpy(hptr->account_log[hptr->account_log_quantity],current_time);
            strcat(hptr->account_log[hptr->account_log_quantity],": Permanent address updated.");
            hptr->account_log_quantity++;
            break;
        case 3:
            printf("Your current E-mail address: %s\n",(ptr+indicator)->email);
            printf("Enter the new E-mail address: ");
            gets((ptr+indicator)->email);
            strcpy(hptr->account_log[hptr->account_log_quantity],current_time);
            strcat(hptr->account_log[hptr->account_log_quantity],": Email address updated.");
            hptr->account_log_quantity++;
            break;
        case 4:
            printf("Your current Contact Number: %s\n",(ptr+indicator)->contact_no);
            printf("Enter the new Contact Number: ");
            gets((ptr+indicator)->contact_no);
            strcpy(hptr->account_log[hptr->account_log_quantity],current_time);
            strcat(hptr->account_log[hptr->account_log_quantity],": Contact Number updated.");
            hptr->account_log_quantity++;
            break;
        default:
            printf("Process canceled.\n");
            return;
        }
        printf("Information updated successfully.\n");
    }
    else
    {
        printf("Process canceled.\n");
        return;
    }

    //history write section
    fwrite(hptr,sizeof(history),1,fptr);
    fclose(fptr);
    free(hptr);


    //write section.
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
}
