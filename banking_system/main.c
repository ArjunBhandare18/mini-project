
#include <stdio.h>
#include <stdlib.h>

struct Account
{
    int accNo;
    char name[50];
    float balance;
};

// Function to create a new account
void createAccount()
{
    struct Account a, temp;
    FILE *fp;

    fp = fopen("accounts.dat", "ab+");

    if (fp == NULL)
    {
        printf("File error!");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &a.accNo);

    rewind(fp);

    while (fread(&temp, sizeof(temp), 1, fp))
    {
        if (temp.accNo == a.accNo)
        {
            printf("Account already exists!\n");
            fclose(fp);
            return;
        }
    }

    printf("Enter Account Holder Name: ");
    scanf(" %49[^\n]", a.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    if (a.balance < 0)
    {
        printf("Invalid balance!\n");
        fclose(fp);
        return;
    }

    fwrite(&a, sizeof(a), 1, fp);

    printf("\nAccount Created Successfully!\n");

    fclose(fp);
}

// Function to deposit money
void depositMoney()
{
    struct Account a;
    FILE *fp;
    int accNo, found = 0;
    float amount;

    fp = fopen("accounts.dat", "rb+");

    if (fp == NULL)
    {
        printf("No account records found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&a, sizeof(a), 1, fp))
    {
        if (a.accNo == accNo)
        {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid amount!\n");
                fclose(fp);
                return;
            }

            a.balance += amount;

            fseek(fp, -(long)sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);

            printf("Deposit Successful!\n");
            printf("New Balance: %.2f\n", a.balance);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found!\n");

    fclose(fp);
}

// Function to withdraw money
void withdrawMoney()
{
    struct Account a;
    FILE *fp;
    int accNo, found = 0;
    float amount;

    fp = fopen("accounts.dat", "rb+");

    if (fp == NULL)
    {
        printf("No account records found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&a, sizeof(a), 1, fp))
    {
        if (a.accNo == accNo)
        {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid amount!\n");
                fclose(fp);
                return;
            }

            if (amount > a.balance)
            {
                printf("Insufficient Balance!\n");
                fclose(fp);
                return;
            }

            a.balance -= amount;

            fseek(fp, -(long)sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);

            printf("Withdrawal Successful!\n");
            printf("Remaining Balance: %.2f\n", a.balance);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found!\n");

    fclose(fp);
}

// Function to check balance
void checkBalance()
{
    struct Account a;
    FILE *fp;
    int accNo, found = 0;

    fp = fopen("accounts.dat", "rb");

    if (fp == NULL)
    {
        printf("No account records found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&a, sizeof(a), 1, fp))
    {
        if (a.accNo == accNo)
        {
            printf("\nAccount Holder: %s\n", a.name);
            printf("Account Number: %d\n", a.accNo);
            printf("Available Balance: %.2f\n", a.balance);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Account Not Found!\n");

    fclose(fp);
}

// Function to display all accounts
void displayAccounts()
{
    struct Account a;
    FILE *fp;

    fp = fopen("accounts.dat", "rb");

    if (fp == NULL)
    {
        printf("No account records found!\n");
        return;
    }

    printf("\n------ ALL BANK ACCOUNTS ------\n");

    while (fread(&a, sizeof(a), 1, fp))
    {
        printf("\nAccount Number: %d\n", a.accNo);
        printf("Account Holder: %s\n", a.name);
        printf("Balance: %.2f\n", a.balance);
    }

    fclose(fp);
}

// Main function
int main()
{
    int choice;

    do
    {
        printf("\n================================");
        printf("\n     BANKING MANAGEMENT SYSTEM");
        printf("\n================================");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. Display All Accounts");
        printf("\n6. Exit");

        printf("\n\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                displayAccounts();
                break;

            case 6:
                printf("\nThank You for Using Our Banking System!\n");
                break;

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }

    } while (choice != 6);

    return 0;
}
