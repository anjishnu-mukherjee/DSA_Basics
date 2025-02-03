/*
Suggest a pseudo code / C function to find the middle element of a single linked list in a single
pass. (Please note that if the list has even number of elements (n) then middle element will be the
first middle element (⌊n/2⌋).
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    int data;
    struct node* link;
} node;


node* createNode(int data) 
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

node* insertEnd(node* head, int data) 
{
    node* newNode = createNode(data);
    if (head == NULL) 
    {
        return newNode;
    }
    node* temp = head;
    while (temp->link != NULL) 
    {
        temp = temp->link;
    }
    temp->link = newNode;
    return head;
}

node* find_middle(node* h)
{
    if (h == NULL)
    {
        return NULL;
    }

    node* step1 = h;
    node* step2 = h;

    while(step2 != NULL && step2->link != NULL)
    {
        step1 = step1->link;
        step2 = step2->link->link;
    }
    return step1;
}

void printList(node* head) 
{
    printf("List: ");
    while (head != NULL) 
    {
        printf("%d -> ", head->data);
        head = head->link;
    }
    printf("NULL\n");
}

int main()
{
    node* list1 = NULL;
    node* list2 = NULL;

    
    list1 = insertEnd(list1, 1);
    list1 = insertEnd(list1, 3);
    list1 = insertEnd(list1, 5);

    list2 = insertEnd(list2, 2);
    list2 = insertEnd(list2, 4);
    list2 = insertEnd(list2, 6);

    node* middle_list1 = find_middle(list1);
    node* middle_list2 = find_middle(list2);

    printList(list1);
    if (middle_list1 != NULL)
        printf("Middle Element : %d\n",middle_list1->data);
    else
        printf("Empty List!\n");
    printList(list2);
    if (middle_list2 != NULL)
        printf("Middle Element : %d\n",middle_list2->data);
    else
        printf("Empty List!\n");
    return 0;
}