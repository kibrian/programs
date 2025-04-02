#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

struct BankAccount {
    char accountNumber[20]; // Changed from int to char to allow alphanumeric account numbers
    char accountHolderName[100];
    float balance;
};

struct BankAccount accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Function to find an account by number
struct BankAccount* findAccount(char accNum[]) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].accountNumber, accNum) == 0)
            return &accounts[i];
    }
    return NULL;
}

// Deposit money
void depositMoney() {
    char accNum[20];
    float amount;
    printf("Enter account number to deposit into: ");
    scanf("%s", accNum);
    struct BankAccount *acc = findAccount(accNum);
    if (acc) {
        printf("Enter amount to deposit: ");
        scanf("%f", &amount);
        if (amount > 0) {
            acc->balance += amount;
            printf("Deposit successful! New balance: %.2f\n", acc->balance);
        } else {
            printf("Invalid deposit amount!\n");
        }
    } else {
        printf("Account not found!\n");
    }
}

// Send money
void sendMoney() {
    char senderAccNum[20], receiverAccNum[20];
    float amount;
    printf("Enter your account number: ");
    scanf("%s", senderAccNum);
    printf("Enter recipient account number: ");
    scanf("%s", receiverAccNum);
    struct BankAccount *sender = findAccount(senderAccNum);
    struct BankAccount *receiver = findAccount(receiverAccNum);
    if (sender && receiver) {
        printf("Enter amount to send: ");
        scanf("%f", &amount);
        if (amount > 0 && sender->balance >= amount) {
            sender->balance -= amount;
            receiver->balance += amount;
            printf("Transfer successful! Your new balance: %.2f\n", sender->balance);
        } else {
            printf("Invalid amount or insufficient funds!\n");
        }
    } else {
        printf("One or both accounts not found!\n");
    }
}

// Withdraw money
void withdrawMoney() {
    char accNum[20];
    float amount;
    printf("Enter account number to withdraw from: ");
    scanf("%s", accNum);
    struct BankAccount *acc = findAccount(accNum);
    if (acc) {
        printf("Enter amount to withdraw: ");
        scanf("%f", &amount);
        if (amount > 0 && amount <= acc->balance) {
            acc->balance -= amount;
            printf("Withdrawal successful! New balance: %.2f\n", acc->balance);
        } else {
            printf("Invalid amount or insufficient balance!\n");
        }
    } else {
        printf("Account not found!\n");
    }
}

// Check balance
void checkBalance() {
    char accNum[20];
    printf("Enter account number to check balance: ");
    scanf("%s", accNum);
    struct BankAccount *acc = findAccount(accNum);
    if (acc) {
        printf("Account Number: %s, Name: %s, Balance: %.2f\n", acc->accountNumber, acc->accountHolderName, acc->balance);
    } else {
        printf("Account not found!\n");
    }
}

// Create new account
void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot create more accounts.\n");
        return;
    }
    struct BankAccount *newAccount = &accounts[accountCount];
    printf("Enter account number: ");
    scanf("%s", newAccount->accountNumber);
    printf("Enter account holder's name: ");
    scanf(" %[^]", newAccount->accountHolderName);
    printf("Enter initial deposit: ");
    scanf("%f", &newAccount->balance);
    if (newAccount->balance < 0) {
        printf("Invalid initial deposit amount!\n");
        return;
    }
    accountCount++;
    printf("Account created successfully!\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Create Account\n2. Deposit Money\n3. Send Money\n4. Withdraw Money\n5. Check Balance\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: sendMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: checkBalance(); break;
            case 6: printf("Exiting program.\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
