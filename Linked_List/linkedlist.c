#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Node 
{
    int data;
    struct Node* link;
}node;


node* createNode(int data) 
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}


node* insert_at_begin(node* h, int data) 
{
    node* newNode = createNode(data);
    newNode->link = h;
    return newNode;
}


node* insert_at_end(node* h, int data) 
{
    node* newNode = createNode(data);
    if (h == NULL) 
    {
        return newNode;
    }
    node* temp = h;
    while (temp->link != NULL) 
    {
        temp = temp->link;
    }
    temp->link = newNode;
    return h;
}


node* insert_at_position(node* h, int data, int pos) 
{
    node* newNode = createNode(data);
    if (pos == 0) {
        newNode->link = h;
        return newNode;
    }
    node* temp = h;
    for (int i = 0; i < pos - 1; i++) 
    {
        if (temp == NULL) 
        {
            printf("Position out of bounds\n");
            return h;
        }
        temp = temp->link;
    }
    if (temp == NULL) 
    {
        printf("Position out of bounds\n");
        return h;
    }
    newNode->link = temp->link;
    temp->link = newNode;
    return h;
}


int delete_at_begin(node** hptr) {
    if (*hptr == NULL) {
        printf("List is empty\n");
        return INT_MIN;
    }
    node* temp = *hptr;
    int data = temp->data;
    *hptr = temp->link;
    free(temp);
    return data;
}


int delete_at_end(node** hptr) 
{
    if (*hptr == NULL) 
    {
        printf("List is empty\n");
        return INT_MIN;
    }
    node* temp = *hptr;
    if (temp->link == NULL) 
    {
        int data = temp->data;
        free(temp);
        *hptr = NULL;
        return data;
    }
    while (temp->link->link != NULL) 
    {
        temp = temp->link;
    }
    int data = temp->link->data;
    free(temp->link);
    temp->link = NULL;
    return data;
}


int delete_at_position(node** hptr, int pos) 
{
    if (*hptr == NULL) 
    {
        printf("List is empty\n");
        return INT_MIN;
    }
    node* temp = *hptr;
    if (pos == 0) 
    {
        int data = temp->data;
        *hptr = temp->link;
        free(temp);
        return data;
    }
    for (int i = 0; i < pos - 1; i++) 
    {
        if (temp == NULL || temp->link == NULL) 
        {
            printf("Position out of bounds\n");
            return INT_MIN;
        }
        temp = temp->link;
    }
    node* nodeToDelete = temp->link;
    if (nodeToDelete == NULL) 
    {
        printf("Position out of bounds\n");
        return INT_MIN;
    }
    int data = nodeToDelete->data;
    temp->link = nodeToDelete->link;
    free(nodeToDelete);
    return data;
}


node* delete_value_from_list(node* h, int del_val) 
{
    node* temp = h;
    node* prev = NULL;
    int c=0;
    while (temp != NULL)
    {
        while (temp != NULL && temp->data != del_val) 
        {
            prev = temp;
            temp = temp->link;
        }
        if (temp == NULL) 
        {
            break;
        }
        if (prev == NULL) 
        {
            h = temp->link;
            c++;
        } 
        else 
        {
            prev->link = temp->link;
            c++;
        }
        temp = temp->link;
    }
    if (temp == NULL && c == 0) 
    {
        printf("Value not found\n");
    }
    free(temp);
    return h;
}


node* reverse_linked_list(node* h) 
{
    node* prev = NULL;
    node* current = h;
    node* next = NULL;
    while (current != NULL) 
    {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }
    h = prev;
    return h;
}


void print_linked_list(node* h) 
{
    while (h != NULL) 
    {
        printf("%d -> ", h->data);
        h = h->link;
    }
    printf("NULL\n");
}


int main() 
{
    node* head = NULL;
    int choice, data, pos, result;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at position\n");
        printf("4. Delete at beginning\n");
        printf("5. Delete at end\n");
        printf("6. Delete at position\n");
        printf("7. Delete value from list\n");
        printf("8. Reverse linked list\n");
        printf("9. Print linked list\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                head = insert_at_begin(head, data);
                print_linked_list(head);
                break;
            case 2:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                head = insert_at_end(head, data);
                print_linked_list(head);
                break;
            case 3:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &pos);
                if (pos < 0)
                {
                    printf("Position doesn't Exist!");
                    print_linked_list(head);
                    break;
                }
                head = insert_at_position(head, data, pos);
                print_linked_list(head);
                break;
            case 4:
                result = delete_at_begin(&head);
                print_linked_list(head);
                if (result != INT_MIN) 
                {
                    printf("Deleted data: %d\n", result);
                }
                break;
            case 5:
                result = delete_at_end(&head);
                print_linked_list(head);
                if (result != INT_MIN) 
                {
                    printf("Deleted data: %d\n", result);
                }
                break;
            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                if (pos < 0)
                {
                    printf("Position doesn't Exist!");
                    print_linked_list(head);
                    break;
                }
                result = delete_at_position(&head, pos);
                print_linked_list(head);
                if (result != INT_MIN) 
                {
                    printf("Deleted data: %d\n", result);
                }
                break;
            case 7:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                head = delete_value_from_list(head, data);
                print_linked_list(head);
                break;
            case 8:
                head = reverse_linked_list(head);
                print_linked_list(head);
                break;
            case 9:
                print_linked_list(head);
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}