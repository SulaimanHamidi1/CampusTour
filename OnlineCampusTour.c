#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TourStop{
    char name[25];
    char description [100];
    int minutes;
} TourStop;

typedef struct Node{
    TourStop stop;
    struct Node* next;
} Node;

char menu (){
    char choice = ' ';

    do {
        printf("\n=========================================\n");
        printf("    Welcome to the GMUTT Campus Tour\n");
        printf("=========================================\n");
        printf("Please choose from the following options:\n");
        printf("    p. Print the current tour\n");
        printf("    a. Add a stop to the tour\n");
        printf("    d. Delete a stop from the tour\n");
        printf("    l. Load a tour from a file\n");
        printf("    s. Save the current tour to a file\n");
        printf("    e. Exit the program\n");
        printf("========================================\n");
        printf("Enter your choice: ");

        choice = getchar();
        getchar();

        if (choice != 'a' && choice != 'A' &&
            choice != 'p' && choice != 'P' &&
            choice != 'l' && choice != 'L' &&
            choice != 'd' && choice != 'D' &&
            choice != 'e' && choice != 'E' &&
            choice != 's' && choice != 'S') {

            printf("\n--Invalid input, try again--\n");
        }

    } while (choice != 'a' && choice != 'A' &&
             choice != 'p' && choice != 'P' &&
             choice != 'l' && choice != 'L' &&
             choice != 'd' && choice != 'D' &&
             choice != 'e' && choice != 'E' &&
             choice != 's' && choice != 'S' );

    return choice;
}

Node* createNode (){
    Node* newNode = calloc(1, sizeof(Node));
    if (newNode == NULL){
        printf("\n--Memory allocation failed--\n");
        return NULL;
    }

    printf("Tour stops's name: ");
    fgets(newNode->stop.name, 25, stdin);
    newNode->stop.name[strcspn(newNode->stop.name, "\n")] = '\0';

    printf("Tour stops's description: ");
    fgets(newNode->stop.description, 100, stdin);
    newNode->stop.description[strcspn(newNode->stop.description, "\n")] = '\0';

    printf("Tour stops's time in minutes: ");
    scanf("%d", &newNode->stop.minutes);
    getchar();

    newNode->next = NULL;

    return newNode;
}

Node* insertAlphabetical (Node* head){
    Node* newNode = createNode();

    if (head == NULL || strcasecmp(newNode->stop.name, head->stop.name) < 0) {
        newNode->next = head;
        printf("\n--Stop '%s' was added successfully!--\n", newNode->stop.name);
        return newNode;
    }
    
    if (strcasecmp(newNode->stop.name, head->stop.name) == 0){
        printf("\n--Stop '%s' already exists--\n", newNode->stop.name);
        free(newNode);
        return head;
    }
    Node* temp = head;

    while (temp->next != NULL){
        int match = strcasecmp(temp->next->stop.name, newNode->stop.name);

        if (match == 0){
            printf("\n--Stop '%s' already exists--\n", newNode->stop.name);
            free(newNode);
            return head;
        }
        else if (match > 0){
            break;
        }
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    printf("\n--Stop '%s' was added successfully!--\n", newNode->stop.name);
    return head;
}

Node* insertCustom(Node* head){
    Node* newNode = createNode();
    
    if (head == NULL){
        return newNode;
    }
    Node* check = head;

    while (check != NULL){
        int match = strcasecmp(check->stop.name, newNode->stop.name);

        if (match == 0){
            printf("\n--Stop %s already exists!--\n", newNode->stop.name);
            free(newNode);
            return head;
        }
        check = check->next;
    }
    
    int choice = 0;
    do {
        printf("\nPlease choose one of the following:\n");
        printf("1. Insert the stop at the beginning\n");
        printf("2. Insert the stop at the end\n");
        printf("3. Insert the stop somewhere else\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();

        if (choice != 1 && choice != 2 && choice != 3){
            printf("Invalid input, please try again!\n");
        }
    } while (choice != 1 && choice != 2 && choice != 3);    

        if (choice == 1){
            newNode->next = head;
            printf("\n--Stop '%s' was inserted successfully!--\n", newNode->stop.name);
            return newNode;
        }
        else if (choice == 2){
            Node* current = head;
            while(current->next != NULL){
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            printf("\n--Stop '%s' was inserted successfully\n", newNode->stop.name);
            return head;
        }
        else if (choice == 3){
            char stopName[25];
            printf("\nEnter the name of the stop you would like to insert after: ");
            fgets(stopName, 25, stdin);
            stopName[strcspn(stopName, "\n")] = '\0';

            Node* current = head;
            while (current != NULL){
                if (strcasecmp(stopName, current->stop.name) == 0){
                    newNode->next = current->next;
                    current->next = newNode;
                    printf("\n--Stop '%s' was inserted successfully!--\n", newNode->stop.name);
                    return head;
                }
                current = current->next;
            }
            printf("\n--Stop %s was not found!--\n", stopName);
            free(newNode);
            return head;
        }
    return head;
}

void printList (Node* head){
    Node* current = head;
    if (head == NULL){
        printf("\n--Cannot print empty list!--\n");
        return;
    }
    int i = 1;
    printf("\n********************************\n");
    printf("    Your Current Tour\n");
    printf("********************************\n");
    while (current != NULL){
        printf("Stop %d:\n", i);
        printf("Stop's name: %s\nDescription: %s\nTime: %d\n",
               current->stop.name, current->stop.description, current->stop.minutes);

        current = current->next;
        i++;
        
        if (current != NULL){
            printf("\n");
        }
    }
    printf("********************************\n");
}

Node* deleteStop (Node* head){
    if (head == NULL){
        printf("\n--List is empty!--\n");
        return head;
    }

    int choice = 0;
    do {
        printf("\nPlease choose from the following options:\n");
        printf("1. Remove the first Stop\n");
        printf("2. Remove the last Stop\n");
        printf("3. Remove some other Stop\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();

        if (choice != 1 && choice != 2 && choice != 3){
            printf("Invalid input, try again\n");
        }
    } while (choice != 1 && choice != 2 && choice != 3);

    if (choice == 1){
        Node* temp = head;
        head = head->next;
        free(temp);
        printf("\n--First stop was removed!--\n");
        return head;
    }
    else if (choice == 2){
        if (head->next == NULL){
            free(head);
            printf("\n--Only stop has been removed--\n");
            return NULL;
        }
        Node* current = head;
        while (current->next->next != NULL){
               current = current->next;
        }
        free(current->next);
        current->next = NULL;
        printf("\n--Last stop has been removed--\n");
        return head;
    }
    else if (choice == 3){
        char stopName [25];
        printf("Enter the stop's name you would like to remove: ");
        fgets(stopName, 25, stdin);
        stopName[strcspn(stopName, "\n")] = '\0';

        if (strcasecmp(stopName, head->stop.name) == 0){
            Node* temp = head;
            head = head->next;
            free(temp);
            printf("\n--Stop '%s' has been removed--\n", stopName);
            return head;
        }
        
        Node* current = head;
        while (current->next != NULL && strcasecmp(current->next->stop.name, stopName) != 0){
            current = current->next;
        }
        if (current->next != NULL && strcasecmp(stopName, current->next->stop.name) == 0){
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            printf("\n--Stop '%s' has been removed--\n", stopName);
        }
        else {
            printf("Stop '%s' was not found!\n", stopName);
        }
        return head;
    }
    return head;
}

void freeList (Node* head){
    if (head == NULL){
        printf("\n--Goodbye!--\n");
        return;
    }
    Node* current = head;
    while(current != NULL){
        Node* next = current->next;
        free(current);
        current = next;
    }
    printf("\n--Goodbye!--\n");
    head = NULL;
}

void saveList (Node* head){

    if (head == NULL){
        printf("\n--You have no tours to save!--\n");
        return;
    }
    char filename[25];
    printf("Save file as: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';

    FILE* file = fopen(filename, "wb");

    if (file == NULL){
        printf("--Error, opening file--\n");
        return;
    }
    Node* current = head;
    while(current != NULL){
        fwrite(&current->stop, sizeof(TourStop), 1, file);
        current = current->next;
    }
    fclose(file);
    printf("\n--Tour was saved as %s--\n", filename);
}

Node* loadList (Node* head){
    char choice = ' ';
    printf("\n--Warning!--\nProceeding will delete your current tour\n");

    do {
        printf("Do you wish to proceed? (y/n): ");
        choice = getchar();
        getchar();

        if (choice == 'y' || choice == 'Y'){
            char fileName [25];
            printf("\nName of the file to load: ");
            fgets(fileName, 25, stdin);
            fileName[strcspn(fileName, "\n")] = '\0';

            FILE* file = fopen(fileName, "rb");
            if (file == NULL){
                printf("\n--Cannot open file--\n");
                return head;
            }

            freeList(head);

            Node* newHead = NULL;
            Node* tail = NULL;
            TourStop current; 

            while (fread(&current, sizeof(TourStop), 1, file) == 1){
                Node* newNode = malloc(sizeof(Node));
                if (newNode == NULL){
                    printf("\n--Cannot load file--\n");
                    fclose(file);
                    return 0;
                }

                newNode->stop = current;
                newNode->next = NULL;

                if (newHead == NULL){
                    newHead = newNode;
                    tail = newNode;
                }
                else {
                    tail->next = newNode;
                    tail = newNode;
                }
            }

            fclose(file);
            printf("\n--Tour loaded successfully--\n");
            return newHead;
        }
        else if (choice == 'n' || choice == 'N'){
            printf("\n--No file was loaded--\n");
            return head;
        }
        else {
            printf("\n--Invalid input, try again!--\n");
        }
    } while (choice != 'y' && choice != 'Y' &&
             choice != 'n' && choice != 'N' );
    return head;
}

Node* alphabeticalOrCustom (Node* head){
    int option = 0;

    do {
        printf("\n1 - For Alphabetical insert\n");
        printf("2 - For custom insert\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        getchar();

        if (option != 1 && option != 2){
            printf("\n\n--Invalid input, try again!--\n\n");
            continue;
        }
        head = (option == 1) ? insertAlphabetical(head) : insertCustom(head);
    } while (option != 1 && option != 2);
    return head;
}

int main (){
    char choice = ' ';
    Node* head = NULL;

    do {
        choice = menu();

        switch (choice){
            
            case 'p':
            case 'P':
                printList(head);
                break;

            case 'a':
            case 'A':
                head = alphabeticalOrCustom(head);
                break;

            case 'd':
            case 'D':
                head = deleteStop(head);
                break;

            case 's':
            case 'S':
                saveList(head);
                break;

            case 'l':
            case 'L':
                head = loadList(head);
                break;

            case 'e':
            case 'E':
                freeList(head);
                return 0;
        }

    } while (choice != 'f' && choice != 'F');

    return 0;
}

