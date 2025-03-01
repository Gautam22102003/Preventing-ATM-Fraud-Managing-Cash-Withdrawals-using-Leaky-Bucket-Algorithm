#include <stdio.h>
#include <time.h>
#include <unistd.h>  // For sleep()
#include <string.h>

#define MAX_USERS 5   // Maximum number of users
#define BUCKET_SIZE 3 // Max withdrawals allowed within time window
#define LEAK_RATE 10  // Time in seconds after which a withdrawal is removed

typedef struct {
    char user_id[10];   // User's ATM ID
    int transactions;   // Number of withdrawals
    time_t last_time;   // Last withdrawal time
} ATM_User;

// Initialize user database
ATM_User users[MAX_USERS] = {
    {"1001", 0, 0},
    {"1002", 0, 0},
    {"1003", 0, 0},
    {"1004", 0, 0},
    {"1005", 0, 0}
};

// Find user by ID
ATM_User* find_user(char *id) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].user_id, id) == 0) {
            return &users[i];
        }
    }
    return NULL; // User not found
}

void withdraw_cash(ATM_User *user) {
    time_t current_time = time(NULL);

    // Leak withdrawals if time exceeded
    if (user->transactions > 0 && (current_time - user->last_time >= LEAK_RATE)) {
        user->transactions--;  // Reduce transaction count
        user->last_time = current_time;
    }

    // Check if withdrawal is allowed
    if (user->transactions < BUCKET_SIZE) {
        user->transactions++;  // Add new transaction
        user->last_time = current_time;
        printf("✅ Withdrawal successful! User %s - Remaining limit: %d\n", 
               user->user_id, BUCKET_SIZE - user->transactions);
    } else {
        printf("❌ Too many withdrawals for user %s! Try again later.\n", user->user_id);
    }
}

int main() {
    char user_id[10];
    int choice;

    while (1) {
        printf("\nEnter ATM User ID: ");
        scanf("%s", user_id);

        ATM_User *user = find_user(user_id);
        if (!user) {
            printf("❌ Invalid User ID! Try again.\n");
            continue;
        }

        printf("\nATM Withdrawal System\n1. Withdraw Cash\n2. Exit\nChoose: ");
        scanf("%d", &choice);

        if (choice == 1) {
            withdraw_cash(user);
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
