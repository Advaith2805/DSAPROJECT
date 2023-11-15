#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a contact
typedef struct Contact_info {
    char firstname[30];
    char number[50];
    char email[40];
} Content;

// Define a structure to represent a contact node
typedef struct ContactNode {
    Content reach;
    struct ContactNode* left;
    struct ContactNode* right;
} ContNode;

// Define a structure to represent a contact tree
typedef struct ContactTree {
    ContNode* root;
} ContTree;

// Function to create a new contact node
ContNode* createCont(Content reach) {
    ContNode* newNode = (ContNode*)malloc(sizeof(ContNode));
    if (newNode == NULL) {
        printf("The memory allocation failed.\n");
        return NULL;
    }
    newNode->reach = reach;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a contact into the contact tree
ContNode* insertCont(ContNode* root, Content reach) {
    if (root == NULL) {
        return createCont(reach);
    }
    int comp = strcmp(reach.firstname, root->reach.firstname);
    if (comp < 0) {
        root->left = insertCont(root->left, reach);
    } else if (comp > 0) {
        root->right = insertCont(root->right, reach);
    }

    return root;
}

// Function to display contacts in an in-order traversal
void dispCont(ContNode* root) {
    if (root != NULL) {
        dispCont(root->left);
        printf("Name: %s\n", root->reach.firstname);
        printf("Number: %s\n", root->reach.number);
        printf("Email: %s\n\n", root->reach.email);
        dispCont(root->right);
    }
}

// Function to search for a contact by name
ContNode* searchCont(ContNode* root, const char* firstname) {
    if (root == NULL || strcmp(firstname, root->reach.firstname) == 0) {
        return root;
    }

    if (strcmp(firstname, root->reach.firstname) < 0) {
        return searchCont(root->left, firstname);
    }

    return searchCont(root->right, firstname);
}
void updateCont(ContNode* root, const char* firstname, const char* newnum, const char* newEmail) {
    ContNode* reach = searchCont(root, firstname);
    if (reach != NULL) {
        strcpy(reach->reach.number, newnum);
        strcpy(reach->reach.email, newEmail);
        printf("Contact updated successfully.\n");
    } else {
        printf("Contact not found. Update failed.\n");
    }
}

// Function to delete a contact by name
ContNode* delete_Contact(ContNode* root, const char* firstname) {
    if (root == NULL) {
        return root;
    }

    int comp = strcmp(firstname, root->reach.firstname);
    if (comp < 0) {
        root->left = delete_Contact(root->left, firstname);
    } else if (comp > 0) {
        root->right = delete_Contact(root->right, firstname);
    } else {
        if (root->left == NULL) {
            ContNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            ContNode* temp = root->left;
            free(root);
            return temp;
        }

        ContNode* temp = root;
        while (temp->left != NULL) {
            temp = temp->left;
        }
strcpy(root->reach.firstname, temp->reach.firstname);
        root->right = delete_Contact(root->right, temp->reach.firstname);
    }

    return root;
}

int main() {
    ContTree contTree;
    contTree.root = NULL;

    char firstname[30];
    char number[50];
    char email[40];
    int choice;

    printf("************** PHONE BOOK **************\n\n");
    do {
        printf("\nMenu:\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact by Name\n");
        printf("4. Update Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the Name: ");
                scanf("%s", firstname);
                printf("Enter the phone number: ");
                scanf("%s", number);
                printf("Enter the E-mail id: ");
                scanf("%s", email);
                Content latest ;
                strcpy(latest.firstname, firstname);
                strcpy(latest.number, number);
                strcpy(latest.email, email);
                contTree.root = insertCont(contTree.root, latest);
                break;
            case 2:
                printf("Contacts in the Phone Book:\n");
                dispCont(contTree.root);
                break;
            case 3:
                printf("Enter the name to search: ");
                scanf("%s", firstname);
                ContNode* find = searchCont(contTree.root, firstname);
                if (find != NULL) {
                    printf("The contact exists in the phonebook:\n");
                    printf("Name: %s\n", find->reach.firstname);
                    printf("Number: %s\n", find->reach.number);
                    printf("E-mail: %s\n\n", find->reach.email);
                } else {
                    printf("Contact not found.\n");
                }
                break;
            case 4:
                printf("Enter the name to update: ");
                scanf("%s", firstname);
                printf("Enter the new phone number: ");
                scanf("%s", number);
                
                printf("Enter the new E-mail-id : ");
                scanf("%s", email);
                updateCont(contTree.root, firstname, number, email);
                break;
            case 5:
                printf("Please enter the name to delete: ");
                scanf("%s", firstname);
                contTree.root = delete_Contact(contTree.root, firstname);
                break;
            case 6:
                printf("Exiting the Phone Book.\n");
                break;
            default:
                printf("Your choice is invalid. Please try again.\n");
                break;
        }
    } while (choice != 6);

return 0;
}