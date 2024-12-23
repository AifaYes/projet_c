#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client {
    int id;
    char name[50];
    char destination[50];
    float budget;
    struct Client* next; 
} Client;

Client* addClient(Client* head, int id, char* name, char* destination, float budget);
void displayClients(Client* head);
Client* searchClient(Client* head, int id);
Client* deleteClient(Client* head, int id);
void freeList(Client* head);
int main() {    
    Client* head = NULL; 
    int choice, id;
    char name[50], destination[50];
    float budget;
    while (1) {
        printf("\n--- Travel Agency Database ---\n");
        printf("NB: Spaces are not allowed when you write your choice in any input\n");
        printf("1. Add Client\n");
        printf("2. Display Clients\n");
        printf("3. Search for a Client\n");
        printf("4. Delete a Client\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf(" %[^\n]", name); 
                printf("Enter Destination: ");
                scanf(" %[^\n]", destination);
                printf("Enter Budget: ");
                scanf("%f", &budget);
                head = addClient(head, id, name, destination, budget);
                break;
            case 2:
                displayClients(head);
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                Client* found = searchClient(head, id);
                if (found) {
                    printf("Client Found - ID: %d, Name: %s, Destination: %s, Budget: %.2f\n",
                           found->id, found->name, found->destination, found->budget);
                } else {
                    printf("Client with ID %d not found.\n", id);
                }
                break;
            case 4:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                head = deleteClient(head, id);
                break;
            case 5:
                freeList(head);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
Client* addClient(Client* head, int id, char* name, char* destination, float budget) { //
    Client* newClient = (Client*)malloc(sizeof(Client));
    newClient->id = id;
    strcpy(newClient->name, name);
    strcpy(newClient->destination, destination);
    newClient->budget = budget;
    newClient->next = head; 
    return newClient;
}

void displayClients(Client* head) { 
    if (!head) {
        printf("No clients in the database.\n");
        return;
    }
    printf("\n--- Client List ---\n");
    Client* temp = head;
    while (temp) {
        printf("ID: %d, Name: %s, Destination: %s, Budget: %.2f\n",
               temp->id, temp->name, temp->destination, temp->budget);
        temp = temp->next;
    }
}

Client* searchClient(Client* head, int id) {
    Client* temp = head;
    while (temp) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
Client* deleteClient(Client* head, int id) { 
    Client* temp = head;
    Client* prev = NULL;


    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Client with ID %d not found.\n", id);
        return head; 
    }

    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp); 
    printf("Client with ID %d deleted.\n", id);
    return head;
}

void freeList(Client* head) {
    Client* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}





