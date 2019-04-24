typedef struct
{
    char present[40];
    char permanent[40];
}addresses;
typedef struct
{
    char name[20];
    int age;
    int account_id;
    char created[30];
    addresses address;
    float account_balance;
    char account_type;
    char email[30];
    char contact_no[15];
}account;

typedef struct
{
    char name[20];
    int account_id;
    char account_creation[60];
    char account_log[50][60];
    int account_log_quantity;
    char account_deletion[60];
}history;
