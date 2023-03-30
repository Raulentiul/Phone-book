#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_ENTRIES 100

typedef struct {
    char name[50];
    char phone[20];
    char email[20];
} person;

int num_entries = 0;
person phonebook[MAX_ENTRIES];

void add_person() {
    if (num_entries >= MAX_ENTRIES) {
        printf("Phonebook is full.\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", phonebook[num_entries].name);

    printf("Enter e-mail: ");
    scanf("%s", phonebook[num_entries].email);

    printf("Enter phone number: ");
    scanf("%s", phonebook[num_entries].phone);

    num_entries++;

    printf("Person added to phonebook.\n");
}

void delete_person() {
    int i;
    char name[50];

    if (num_entries == 0) {
        printf("Phonebook is empty.\n");
        return;
    }

    printf("Enter name of person to delete: ");
    scanf("%s", name);

    for (i = 0; i < num_entries; i++) {
        if (strcmp(phonebook[i].name, name) == 0) {
            break;
        }
    }

    if (i == num_entries) {
        printf("Person not found.\n");
        return;
    }

    num_entries--;

    for (; i < num_entries; i++) {
        phonebook[i] = phonebook[i + 1];
    }

    printf("Person deleted from phonebook.\n");
}

void update_person() {
    char name[50];
    int i;

    if (num_entries == 0) {
        printf("Phonebook is empty.\n");
        return;
    }

    printf("Enter name of person to update: ");
    scanf("%s", name);

    for (i = 0; i < num_entries; i++) {
        if (strcmp(phonebook[i].name, name) == 0) {
            printf("Enter new name: ");
            scanf("%s", phonebook[i].name);
            printf("Enter new phone number: ");
            scanf("%s", phonebook[i].phone);
            printf("Enter E-mail: ");
            scanf("%s", phonebook[i].email);
            printf("Person updated.\n");
            return;
        }
    }

    printf("Person not found.\n");
}

void view_phonebook() {
    int i;

    if (num_entries == 0) {
        printf("Phonebook is empty.\n");
        return;
    }
    printf("6");
    for (i = 0; i < num_entries; i++) {
        printf("Name: %s\tEmail: %s\tPhone Number: %s\n", phonebook[i].name,phonebook[i].email, phonebook[i].phone);
    }
}

void load_phonebook() {
    FILE *fp;
    int i;

    fp = fopen("phonebook.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(fp, "%s %s %s", phonebook[num_entries].name, phonebook[num_entries].phone, phonebook[num_entries].email)!= EOF) {
        num_entries++;
    }

    fclose(fp);

    printf("Phonebook loaded from file.\n");
}

void save_phonebook() {
    FILE *fp;
    int i;

    fp = fopen("phonebook.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (i = 0; i < num_entries; i++) {
        fprintf(fp, "%s %s %s\n", phonebook[i].name, phonebook[i].phone,phonebook[i].email);
    }

    fclose(fp);

    printf("Phonebook saved to file.\n");
}


void search_person() {
    char query[50];
    int found = 0;

    printf("Enter name or phone number to search for: ");
    scanf("%s", query);

    for (int i = 0; i < num_entries; i++) {
        if (strcmp(phonebook[i].name, query) == 0 || strcmp(phonebook[i].phone, query) == 0) {
            printf("%s: %s, %s\n", phonebook[i].name, phonebook[i].phone,phonebook[i].email);
            found = 1;
        }
    }

    if (!found) {
        printf("No results found.\n");
    }
}


int main() {
    int choice;
    load_phonebook();

    while (1) {
        printf("\n                PHONEBOOK\n");
        printf("1. Add person\n");
        printf("2. Delete person\n");
        printf("3. Update person\n");
        printf("4. Search person\n");
        printf("5. View Phonebook\n");
        printf("6. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_person();
                save_phonebook();
                system("cls");
                break;
            case 2:
                delete_person();
                save_phonebook();
                break;
            case 3:
                update_person();
                save_phonebook();
                break;
            case 4:
                search_person();
                break;
            case 5:
                view_phonebook();
                break;
            case 6:
                save_phonebook();
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

}
