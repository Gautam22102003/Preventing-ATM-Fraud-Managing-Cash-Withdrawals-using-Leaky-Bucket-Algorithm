#include <stdio.h>
#include <time.h>
#include <unistd.h>  // For sleep()

#define BUCKET_SIZE 3  // Max withdrawals allowed within time window
#define LEAK_RATE 10   // Time in seconds after which a withdrawal is removed

typedef struct {
    int transactions;   // Number of withdrawals in the bucket
    time_t last_time;   // Last withdrawal time
} ATM_User;

void withdraw_cash(ATM_User *user) {
    time_t current_time = time(NULL);

    // Leak withdrawals that are older than LEAK_RATE seconds
    if (user->transactions > 0 && (current_time - user->last_time >= LEAK_RATE)) {
        user->transactions--;  // Remove old transaction
        user->last_time = current_time; // Update last withdrawal time
    }

    // Check if withdrawal is allowed
    if (user->transactions < BUCKET_SIZE) {
        user->transactions++;  // Add a new transaction
        user->last_time = current_time;
        printf("✅ Withdrawal successful! Remaining limit: %d\n", BUCKET_SIZE - user->transactions);
    } else {
        printf("❌ Too many withdrawals! Try again later.\n");
    }
}

int main() {
    ATM_User user = {0, time(NULL)};

    int choice;
    while (1) {
        printf("\nATM Withdrawal System\n1. Withdraw Cash\n2. Exit\nChoose: ");
        scanf("%d", &choice);

        if (choice == 1) {
            withdraw_cash(&user);
        } else if (choice == 2) {
            printf("Thank you for using the ATM!\n");
            break;
        } else {
            printf("Invalid choice! Try again.\n");
        }

        sleep(3); // Simulate time passing
    }
    return 0;
}
