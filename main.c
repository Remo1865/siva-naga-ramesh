#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_EMAIL 80
#define MAX_ADDRESS 150
#define MAX_NUMBERS 5
#define MAX_NUMBER 15

typedef struct Contact
{
    char name[MAX_NAME];

    char numbers[MAX_NUMBERS][MAX_NUMBER];
    int number_count;

    char email[MAX_EMAIL];
    char address[MAX_ADDRESS];

    struct Contact *next;

} Contact;


/* Function declarations */
Contact *create_contact(Contact *head);
void print_contacts(Contact *head);
void find_contact(Contact *head);
Contact *delete_contact(Contact *head);
Contact *edit_contact(Contact *head);
void save_contacts(Contact *head);
Contact *load_contacts(void);


/* CREATE CONTACT */
Contact *create_contact(Contact *head)
{
    Contact *new_contact;
    Contact *temp;
    char choice;

    new_contact = malloc(sizeof(Contact));

    if (new_contact == NULL)
    {
        printf("Memory allocation failed.\n");
        return head;
    }

    printf("\nEnter contact name: ");
    scanf(" %49[^\n]", new_contact->name);

    /* Check duplicate */
    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->name, new_contact->name) == 0)
        {
            printf("Contact already exists.\n");
            free(new_contact);
            return head;
        }

        temp = temp->next;
    }

    new_contact->number_count = 0;

    /* First phone number */
    printf("Enter phone number: ");
    scanf(" %14s", new_contact->numbers[0]);

    new_contact->number_count = 1;

    /* Additional numbers */
    while (new_contact->number_count < MAX_NUMBERS)
    {
        printf("Do you want to add another number? (Y/N): ");
        scanf(" %c", &choice);

        if (choice == 'N' || choice == 'n')
        {
            break;
        }

        if (choice == 'Y' || choice == 'y')
        {
            printf("Enter phone number: ");

            scanf(" %14s",
                  new_contact->numbers[new_contact->number_count]);

            new_contact->number_count++;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    /* Email */
    printf("Do you want to add email? (Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        printf("Enter email: ");
        scanf(" %79s", new_contact->email);
    }
    else
    {
        strcpy(new_contact->email, "Not Available");
    }

    /* Address */
    printf("Do you want to add address? (Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y')
    {
        printf("Enter address: ");
        scanf(" %149[^\n]", new_contact->address);
    }
    else
    {
        strcpy(new_contact->address, "Not Available");
    }

    new_contact->next = NULL;


    /* Add node */
    if (head == NULL)
    {
        head = new_contact;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = new_contact;
    }

    printf("\nContact created successfully.\n");

    return head;
}


/* PRINT CONTACTS */
void print_contacts(Contact *head)
{
    Contact *temp;
    int i;

    if (head == NULL)
    {
        printf("\nPhone book is empty.\n");
        return;
    }

    temp = head;

    printf("\n========================================\n");
    printf("           PHONE BOOK\n");
    printf("========================================\n");

    while (temp != NULL)
    {
        printf("\nName    : %s\n", temp->name);

        printf("Phone   : ");

        for (i = 0; i < temp->number_count; i++)
        {
            printf("%s", temp->numbers[i]);

            if (i < temp->number_count - 1)
            {
                printf(", ");
            }
        }

        printf("\n");

        printf("Email   : %s\n", temp->email);

        printf("Address : %s\n", temp->address);

        printf("----------------------------------------\n");

        temp = temp->next;
    }
}


/* FIND CONTACT */
void find_contact(Contact *head)
{
    Contact *temp;
    char name[MAX_NAME];
    int i;

    if (head == NULL)
    {
        printf("\nPhone book is empty.\n");
        return;
    }

    printf("\nEnter name to find: ");
    scanf(" %49[^\n]", name);

    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            printf("\nContact found!\n");

            printf("Name    : %s\n", temp->name);

            printf("Phone   : ");

            for (i = 0; i < temp->number_count; i++)
            {
                printf("%s", temp->numbers[i]);

                if (i < temp->number_count - 1)
                {
                    printf(", ");
                }
            }

            printf("\n");

            printf("Email   : %s\n", temp->email);

            printf("Address : %s\n", temp->address);

            return;
        }

        temp = temp->next;
    }

    printf("\nContact not found.\n");
}


/* DELETE CONTACT */
Contact *delete_contact(Contact *head)
{
    Contact *temp;
    Contact *prev;
    char name[MAX_NAME];

    if (head == NULL)
    {
        printf("\nPhone book is empty.\n");
        return head;
    }

    printf("\nEnter name to delete: ");
    scanf(" %49[^\n]", name);

    temp = head;
    prev = NULL;

    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            /* Delete first node */
            if (prev == NULL)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }

            free(temp);

            printf("\nContact deleted successfully.\n");

            return head;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nContact not found.\n");

    return head;
}


/* EDIT CONTACT */
Contact *edit_contact(Contact *head)
{
    Contact *temp;
    char name[MAX_NAME];
    int choice;
    int number_choice;

    if (head == NULL)
    {
        printf("\nPhone book is empty.\n");
        return head;
    }

    printf("\nEnter name to edit: ");
    scanf(" %49[^\n]", name);

    temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            printf("\nContact found.\n");

            printf("\n1. Edit name\n");
            printf("2. Edit phone number\n");
            printf("3. Add phone number\n");
            printf("4. Edit email\n");
            printf("5. Edit address\n");

            printf("\nEnter choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
                case 1:

                    printf("Enter new name: ");
                    scanf(" %49[^\n]", temp->name);

                    printf("Name updated.\n");

                    break;


                case 2:

                    printf("\nCurrent phone numbers:\n");

                    for (int i = 0; i < temp->number_count; i++)
                    {
                        printf("%d. %s\n",
                               i + 1,
                               temp->numbers[i]);
                    }

                    printf("Select number: ");
                    scanf("%d", &number_choice);

                    if (number_choice >= 1 &&
                        number_choice <= temp->number_count)
                    {
                        printf("Enter new number: ");

                        scanf(" %14s",
                              temp->numbers[number_choice - 1]);

                        printf("Number updated.\n");
                    }
                    else
                    {
                        printf("Invalid selection.\n");
                    }

                    break;


                case 3:

                    if (temp->number_count < MAX_NUMBERS)
                    {
                        printf("Enter new phone number: ");

                        scanf(" %14s",
                              temp->numbers[temp->number_count]);

                        temp->number_count++;

                        printf("Phone number added.\n");
                    }
                    else
                    {
                        printf("Maximum phone numbers reached.\n");
                    }

                    break;


                case 4:

                    printf("Enter new email: ");
                    scanf(" %79s", temp->email);

                    printf("Email updated.\n");

                    break;


                case 5:

                    printf("Enter new address: ");
                    scanf(" %149[^\n]", temp->address);

                    printf("Address updated.\n");

                    break;


                default:

                    printf("Invalid choice.\n");
            }

            return head;
        }

        temp = temp->next;
    }

    printf("\nContact not found.\n");

    return head;
}


/* SAVE CONTACTS */
void save_contacts(Contact *head)
{
    FILE *fp;
    Contact *temp;

    fp = fopen("phonebook.dat", "wb");

    if (fp == NULL)
    {
        printf("\nUnable to open file.\n");
        return;
    }

    temp = head;

    while (temp != NULL)
    {
        fwrite(temp, sizeof(Contact), 1, fp);

        temp = temp->next;
    }

    fclose(fp);

    printf("\nContacts saved successfully.\n");
}


/* LOAD CONTACTS */
Contact *load_contacts(void)
{
    FILE *fp;
    Contact *head = NULL;
    Contact *new_contact;
    Contact *temp;

    fp = fopen("phonebook.dat", "rb");

    if (fp == NULL)
    {
        return NULL;
    }

    while (1)
    {
        new_contact = malloc(sizeof(Contact));

        if (new_contact == NULL)
        {
            fclose(fp);
            return head;
        }

        if (fread(new_contact,
                  sizeof(Contact),
                  1,
                  fp) != 1)
        {
            free(new_contact);
            break;
        }

        new_contact->next = NULL;

        if (head == NULL)
        {
            head = new_contact;
        }
        else
        {
            temp = head;

            while (temp->next != NULL)
            {
                temp = temp->next;
            }

            temp->next = new_contact;
        }
    }

    fclose(fp);

    return head;
}


/* MAIN */
int main(void)
{
    Contact *head;
    char choice;

    head = load_contacts();

    while (1)
    {
        printf("\n\n");
        printf("============================================\n");
        printf("              PHONE BOOK APP\n");
        printf("============================================\n");

        printf("c/C : Create contact\n");
        printf("p/P : Print contacts\n");
        printf("d/D : Delete contact\n");
        printf("f/F : Find contact\n");
        printf("e/E : Edit contact\n");
        printf("s/S : Save contacts\n");
        printf("q/Q : Quit\n");

        printf("============================================\n");

        printf("Enter your choice: ");
        scanf(" %c", &choice);


        switch (choice)
        {
            case 'c':
            case 'C':

                head = create_contact(head);

                break;


            case 'p':
            case 'P':

                print_contacts(head);

                break;


            case 'd':
            case 'D':

                head = delete_contact(head);

                break;


            case 'f':
            case 'F':

                find_contact(head);

                break;


            case 'e':
            case 'E':

                head = edit_contact(head);

                break;


            case 's':
            case 'S':

                save_contacts(head);

                break;


            case 'q':
            case 'Q':

                printf("\nExiting Phone Book...\n");

                return 0;


            default:

                printf("\nInvalid choice.\n");
        }
    }

    return 0;
}
