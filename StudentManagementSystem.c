/*
    Student Management System that implements
    linked list data structure along with
    file manipulation
    ------------------------
    Author: Yassine A.
    Date of creation: Spring 2024 (February 26 2024)
    Discord: jwh9
    ------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char s_name[30];
    double s_gpa;
    int s_age;
    struct node *next;
} node;

void menu(void);
node *createfill(void);
void addnode(node **phead, node *to_add);
void displayelements(node *head);
node *deletenode(node *head, char *ToDelete, int *status);
void updategpa(node *head, char *ToUpdate, double *pngpa, int *pstatus);
void updateage(node *head, int *nage, char *ToUpdate, int *pstatus);
void load(node **phead);

int main(void)
{
    node *head = NULL;
    node *n_node;
    char ToDelete[30];
    char ToUpdate[30];
    int choice;
    int status;
    double ngpa;
    int nage;

    do
    {
        menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            n_node = createfill();
            if (n_node != NULL)
            {
                addnode(&head, n_node);
            }
            break;

        case 2:
            displayelements(head);
            break;

        case 3:
            while (getchar() != '\n' && !feof(stdin))
                ;
            printf("Enter the name of the student you want to delete:\n");
            if (fgets(ToDelete, sizeof(ToDelete), stdin) != NULL)
            {
                ToDelete[strcspn(ToDelete, "\n")] = '\0';
            }
            head = deletenode(head, ToDelete, &status);
            if (status == 0)
            {
                printf("The node you want to delete doesn't exist in the linked list.\n");
            }
            else
            {
                printf("The node was successfully deleted.\n");
            }
            break;

        case 4:
            while (getchar() != '\n' && !feof(stdin))
                ;
            printf("Enter the name of the student you want to update their GPA:\n");
            if (fgets(ToUpdate, sizeof(ToUpdate), stdin) != NULL)
            {
                ToUpdate[strcspn(ToUpdate, "\n")] = '\0';
            }
            updategpa(head, ToUpdate, &ngpa, &status);
            if (status == 0)
            {
                printf("The student you want to edit doesn't exist in the linked list.\n");
            }
            else
            {
                printf("The GPA was successfully updated.\n");
            }
            break;

        case 5:
            while (getchar() != '\n' && !feof(stdin))
                ;
            printf("Enter the name of the student you want to update their age:\n");
            if (fgets(ToUpdate, sizeof(ToUpdate), stdin) != NULL)
            {
                ToUpdate[strcspn(ToUpdate, "\n")] = '\0';
            }
            updateage(head, &nage, ToUpdate, &status);
            if (status == 0)
            {
                printf("The student you want to edit doesn't exist in the linked list.\n");
            }
            else
            {
                printf("The age was successfully updated.\n");
            }
            break;

        case 6:
            load(&head);
            printf("Please check 'loadedfile.txt' for the data.\n");
            break;

        case 0:
            printf("Exiting program...\n");
            break;

        default:
            printf("Please enter a valid choice.\n");
            break;
        }
    } while (choice != 0);

    return 0;
}

void menu(void)
{
    printf("------------------\n");
    printf("1 : Create and add element to linked list\n");
    printf("2 : Display all elements in the linked list\n");
    printf("3 : Delete a node from the linked list\n");
    printf("4 : Update a student's GPA\n");
    printf("5 : Update a student's age\n");
    printf("6 : Load elements of the linked list to a text file\n");
    printf("0 : Exit the program\n");
    printf("------------------\n");
    printf("Enter your choice: ");
}

node *createfill(void)
{
    node *n_node = (node *)malloc(sizeof(node));
    if (!n_node)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    while (getchar() != '\n' && !feof(stdin))
        ;

    printf("Enter the name of the student:\n");
    if (fgets(n_node->s_name, sizeof(n_node->s_name), stdin) != NULL)
    {
        n_node->s_name[strcspn(n_node->s_name, "\n")] = '\0';
    }
    else
    {
        printf("Error reading name.\n");
        free(n_node);
        return NULL;
    }

    printf("Enter the student's GPA:\n");
    scanf("%lf", &n_node->s_gpa);

    printf("Enter the student's age:\n");
    scanf("%d", &n_node->s_age);

    n_node->next = NULL;
    return n_node;
}

void addnode(node **phead, node *to_add)
{
    node *current = *phead;
    node *previous = NULL;

    while (current != NULL && current->s_gpa > to_add->s_gpa)
    {
        previous = current;
        current = current->next;
    }

    if (previous == NULL)
    {
        to_add->next = *phead;
        *phead = to_add;
    }
    else
    {
        to_add->next = current;
        previous->next = to_add;
    }
}

void displayelements(node *head)
{
    if (head == NULL)
    {
        printf("There are no elements in the linked list.\n");
        return;
    }

    node *walker = head;
    while (walker != NULL)
    {
        printf("------------------------\n");
        printf("Student name: %s\n", walker->s_name);
        printf("Student GPA: %.2lf\n", walker->s_gpa);
        printf("Student age: %d\n", walker->s_age);
        walker = walker->next;
    }
    printf("------------------------\n");
}

node *deletenode(node *head, char *ToDelete, int *pstatus)
{
    *pstatus = 0;
    if (head == NULL)
    {
        return NULL;
    }

    if (strcmp(ToDelete, head->s_name) == 0)
    {
        node *temp = head;
        head = head->next;
        free(temp);
        *pstatus = 1;
        return head;
    }

    node *walker = head;
    while (walker->next != NULL)
    {
        if (strcmp(ToDelete, walker->next->s_name) == 0)
        {
            node *temp = walker->next;
            walker->next = temp->next;
            free(temp);
            *pstatus = 1;
            return head;
        }
        walker = walker->next;
    }
    return head;
}

void updategpa(node *head, char *ToUpdate, double *pngpa, int *pstatus)
{
    node *walker = head;
    *pstatus = 0;

    while (walker != NULL)
    {
        if (strcmp(ToUpdate, walker->s_name) == 0)
        {
            printf("Enter the new GPA of the student:\n");
            scanf("%lf", pngpa);
            walker->s_gpa = *pngpa;
            *pstatus = 1;
            break;
        }
        walker = walker->next;
    }
}

void updateage(node *head, int *pnage, char *ToUpdate, int *pstatus)
{
    node *walker = head;
    *pstatus = 0;

    while (walker != NULL)
    {
        if (strcmp(ToUpdate, walker->s_name) == 0)
        {
            printf("Enter the new age of the student:\n");
            scanf("%d", pnage);
            walker->s_age = *pnage;
            *pstatus = 1;
            break;
        }
        walker = walker->next;
    }
}

void load(node **phead)
{
    FILE *infp;
    node *walker = *phead;

    infp = fopen("loadedfile.txt", "w");
    if (infp == NULL)
    {
        perror("Could not open loadedfile.txt");
        return;
    }

    while (walker != NULL)
    {
        fprintf(infp, "------------------\n");
        fprintf(infp, "%s\n", walker->s_name);
        fprintf(infp, "%lf\n", walker->s_gpa);
        fprintf(infp, "%d\n", walker->s_age);
        walker = walker->next;
    }
    fprintf(infp, "------------------\n");

    fclose(infp);
}
