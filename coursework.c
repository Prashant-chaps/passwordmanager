#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORDS 86
#define MAX_PASSWORD_LENGTH 200

typedef struct {
    char website[MAX_PASSWORD_LENGTH];
    char username[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} PasswordEntry;

void savePasswords(const PasswordEntry* passwords, int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s\n", passwords[i].website, passwords[i].username, passwords[i].password);
    }

    fclose(file);
    printf("Passwords saved successfully.\n");
}

void readPasswords(PasswordEntry* passwords, int* count, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("No passwords found.\n");
        return;
    }

    *count = 0;
    while (fscanf(file, "%[^,],%[^,],%s\n", passwords[*count].website, passwords[*count].username, passwords[*count].password) == 3) {
        (*count)++;
    }

    fclose(file);
}

void addPassword(PasswordEntry* passwords, int* count) {
    if (*count >= MAX_PASSWORDS) {
        printf("Maximum number of passwords reached.\n");
        return;
    }

    printf("Enter website: ");
    scanf("%s", passwords[*count].website);
    printf("Enter username: ");
    scanf("%s", passwords[*count].username);
    printf("Enter password: ");
    scanf("%s", passwords[*count].password);

    (*count)++;
    printf("Password added successfully.\n");
}

void listPasswords(const PasswordEntry* passwords, int count) {
    if (count == 0) {
        printf("No passwords found.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Website: %s\n", passwords[i].website);
        printf("Username: %s\n", passwords[i].username);
        printf("Password: %s\n", passwords[i].password);
        printf("-----------------\n");
    }
}

int main() {
    PasswordEntry passwords[MAX_PASSWORDS];
    int count = 0;
    char filename[] = "passwords.txt";

    int choice;
    while (1) {
        printf("Password Manager Menu:\n");
        printf("1. Add a password\n");
        printf("2. List all passwords\n");
        printf("3. Save passwords\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPassword(passwords, &count);
                break;

            case 2:
                listPasswords(passwords, count);
                break;

            case 3:
                savePasswords(passwords, count, filename);
                break;

            case 4:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

        printf("\n");
    }

    return 0;
}
