#include "main.h"

void gotoxy(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main()
{
    char choice,password[20],*current_time;
    int indicator=0,i;
    for(;;)
    {
        system("cls");
        printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
               \n\t-\t\t\t\t\t\t\t\t\t\t\t-\
               \n\t-\t\t\t\t\t\t\t\t\t\t\t-\
               \n\t-\t\t\t\t\t\t\t\t\t\t\t-\
               \n\t-\t\t\t\t\t\t\t\t\t\t\t-\
               \n\t-\t\t");
        printf("Enter the authentication password to access the data base  \t\t-\
               \n\t-\t\t\t\t\t\t\t\t\t\t\t-\
               \n\t-\t\t\t\tPASSWORD:  \t\t\t\t\t\t-\
               \n\t-\t\t\t\t\t\t\t\t\t\t\t-\
               \n\t-\t\t\t\t\t\t\t\t\t\t\t-\
               \n\t-\t\t\t\t\t\t\t\t\t\t\t-\
               \n\t-\t\t\t\t\t\t\t\t\t\t\t-\
               \n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        gotoxy(51,8);

        for(i=0;i<20;i++)
        {
            char temp=getch();
            if(temp==10||temp==13)
            {
                password[i]='\0';
                break;
            }
            else if(temp==8)
            {
                if(i==0)
                {
                    i--;
                    continue;
                }
                gotoxy(51+i-1,8);
                printf(" ");
                gotoxy(51+i-1,8);
                i-=2;
                continue;
            }
            password[i]=temp;
            printf("*");
        }

        if(strcmp(password,"iamadmin")!=0)
        {
            int indicator=0;
            indicator=MessageBoxA(NULL,"Wrong password.","NOTE",5|MB_ICONEXCLAMATION);
            if(indicator!=4) return 0;
        }
        else
        {
            MessageBoxA(NULL,"Welcome,Press enter to continue.","NOTE",MB_DEFAULT_DESKTOP_ONLY);
            break;
        }
    }
    gotoxy(0,14);
    printf("\n\n\t\t\t\t\t\tLOADING\n");
    int printer;
    for(printer=0;printer<105;printer++) printf("_");

    CONSOLE_SCREEN_BUFFER_INFO cursor;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
    gotoxy(0,cursor.dwCursorPosition.Y);

    for(printer=0;printer<105;printer++)
    {
        printf("%c",-37);
        Sleep(5);
    }
    Sleep(300);
    while(TRUE)
    {
        system("cls");
        display(MAIN MENU);

        printf("Please choose a option below:-\n\
    1. To find an account press \"F\" or \"f\" .\n\
    2. To add a new account press \"N\" or \"n\" .\n\
    3. To update an account information press \"U\" or \"u\" . \n\
    4. To delete an account press \"D\" or \"d\" .\n\
    5. To view the data files press \"V\" or \"v\" .\n\
    6. To view the history or log of an account press \"H\" or \"h\" .\n\
    7. To exit press \"e\" .\n\
    \nINPUT:\t");
        choice=getchar();
        getchar();
        if(choice=='F'||choice=='f')
        {
            indicator=search('M');
            if(indicator!=-1)
            {
                printf("What do you want to do with this account?\n\
                    1. Press \"D\" or \"d\" to delete it .\n\
                    2. Press \"U\" or \"u\" to update account information .\n\
                    3. Press \"I\" or\"i\" to view detailed information .\n\
                    4. Press \"H\" or\"h\" to view history .\n\
                    4. Press \"a\" to abort. \n");
                while(1)
                {
                    printf("\nINPUT:\t");
                    choice=getchar();
                    getchar();
                    if(choice=='D'||choice=='d')
                    {
                        delete(indicator);
                        break;
                    }
                    else if(choice=='U'||choice=='u')
                    {
                        update(indicator);
                        break;
                    }
                    else if(choice=='I'||choice=='i')
                    {
                        view(indicator);
                        break;
                    }
                    else if(choice=='H'||choice=='h')
                    {
                        viewhistory(indicator);
                        break;
                    }
                    else if(choice=='a') break;
                    else printf("Invalid selection . Select again .\n");
                }
            }
        }
        else if(choice=='N'||choice=='n') new();
        else if(choice=='U'||choice=='u') update(-1);
        else if(choice=='D'||choice=='d') delete(-1);
        else if(choice=='V'||choice=='v') view(-1);
        else if(choice=='H'||choice=='h') viewhistory(-1);
        else if(choice=='e') break;
        printf("\n\
               --Press \"Enter\" key to go to main menu.\n");
        char a[100];
        gets(a);
    }

    return 0;
}
