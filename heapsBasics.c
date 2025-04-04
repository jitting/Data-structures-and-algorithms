/*
NOTE: To test the code, go to the main function and
edit functions parameters
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct node
{
    int key;
    int value;
    struct node *next;
} node;

node *hashTable[MAX];

int hash(int key)
{
    return key % MAX;
}

void insert(int key, int value)
{
    int index = hash(key);
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode)
    {
        printf("Memory allocation error!\n");
        return;
    }

    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    if (hashTable[index] == NULL)
    {
        hashTable[index] = newNode;
    }
    else
    {
        node *temp = hashTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

node *search(int key)
{
    int index = hash(key);
    node *temp = hashTable[index];

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteKey(int key)
{
    int index = hash(key);
    node *temp = hashTable[index];
    node *prev = NULL;

    while (temp != NULL && temp->key != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return;
    }

    if (prev == NULL)
    {
        hashTable[index] = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }
    free(temp);
}

int main(void)
{
    for (int i = 0; i < MAX; i++)
    {
        hashTable[i] = NULL;
    }

    insert(10, 100);
    insert(30, 300);
    insert(50, 500);
    insert(21, 2100);
    insert(41, 4100);

    node *found = search(30);
    if (found)
    {
        printf("Found key %d with value %d\n", found->key, found->value);
    }
    else
    {
        printf("Key 30 not found.\n");
    }

    deleteKey(30);

    found = search(30);
    if (found)
    {
        printf("Found key %d with value %d\n", found->key, found->value);
    }
    else
    {
        printf("Key 30 not found after deletion.\n");
    }

    return 0;
}
