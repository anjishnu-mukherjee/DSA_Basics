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


node* mergeSortedLists(node* l1, node* l2) 
{
    node dummy;  // Dummy node to simplify merging logic
    node* tail = &dummy; 
    dummy.link = NULL;

    while (l1 != NULL && l2 != NULL) 
    {
        if (l1->data <= l2->data) 
        {
            tail->link = l1;
            l1 = l1->link;
        } else 
        {
            tail->link = l2;
            l2 = l2->link;
        }
        tail = tail->link;
    }

    // Attach the remaining part of the list
    if (l1 != NULL) 
    {
        tail->link = l1;
    } else 
    {
        tail->link = l2;
    }

    return dummy.link;  
}


void printList(node* head) 
{
    while (head != NULL) 
    {
        printf("%d -> ", head->data);
        head = head->link;
    }
    printf("NULL\n");
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

int main() 
{
    node* list1 = NULL;
    node* list2 = NULL;

    // Creating first sorted linked list: 1 -> 3 -> 5
    list1 = insertEnd(list1, 1);
    list1 = insertEnd(list1, 3);
    list1 = insertEnd(list1, 5);

    // Creating second sorted linked list: 2 -> 4 -> 6
    list2 = insertEnd(list2, 2);
    list2 = insertEnd(list2, 4);
    list2 = insertEnd(list2, 6);

    printf("List 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);

    node* mergedList = mergeSortedLists(list1, list2);
    printf("Merged Sorted List: ");
    printList(mergedList);

    return 0;
}
