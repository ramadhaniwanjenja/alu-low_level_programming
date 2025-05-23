#include <stdio.h>

void check_balance(float balance);
void deposit(float *balance);
void withdraw(float *balance);

int main() {
    float balance = 1000.0; 
    int choice;

    while (1) {
        printf("\n=== ATM Menu ===\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                check_balance(balance);
                break;
            case 2:
                deposit(&balance);
                break;
            case 3:
                withdraw(&balance);
                break;
            case 4:
                printf("Thank you for using the ATM. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please enter 1-4.\n");
        }
    }
    return 0;
}

void check_balance(float balance) {
    printf("Current balance: $%.2f\n", balance);
}

void deposit(float *balance) {
    float amount;
    printf("Enter amount to deposit: $");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Error: Deposit amount must be positive!\n");
    } else {
        *balance += amount;
        printf("Deposited $%.2f. New balance: $%.2f\n", amount, *balance);
    }
}

void withdraw(float *balance) {
    float amount;
    printf("Enter amount to withdraw: $");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Error: Withdrawal amount must be positive!\n");
    } else if (amount > *balance) {
        printf("Error: Insufficient funds! Balance: $%.2f\n", *balance);
    } else {
        *balance -= amount;
        printf("Withdrew $%.2f. New balance: $%.2f\n", amount, *balance);
    }
}
