#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct doubly_linked_list
{
    int data;
    struct doubly_linked_list* right;
    struct doubly_linked_list* left;
}dnode;

void dll_insert_at_beg(dnode** hptr, dnode** tptr,int val);
void dll_insert_at_end(dnode** hptr, dnode** tptr,int val);
int dll_insert_at_pos(dnode** hptr, dnode** tptr,int val,int pos);
int dll_delete_at_beg(dnode** hptr, dnode** tptr);
int dll_delete_at_end(dnode** hptr, dnode** tptr);
int dll_delete_at_pos(dnode** hptr, dnode** tptr,int pos);
void dll_delete_odd(dnode** hptr, dnode** tptr);
void dll_print(dnode** hptr);

void print_menu() 
{ 
    printf("\nDoubly Linked List Operations:\n");
    printf("1. Insert at Beginning\n");
    printf("2. Insert at End\n");
    printf("3. Insert at Position\n");
    printf("4. Delete at Beginning\n");
    printf("5. Delete at End\n");
    printf("6. Delete at Position\n");
    printf("7. Delete odd Positional values\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main() 
{
    dnode* head = NULL;
    dnode* tail = NULL;
    int choice, val, pos, result;

    while (1) 
    {
        print_menu();
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1: 
                printf("Enter value to insert at beginning: ");
                scanf("%d", &val);
                dll_insert_at_beg(&head, &tail, val);
                dll_print(&head);
                break;
            case 2: 
                printf("Enter value to insert at end: ");
                scanf("%d", &val);
                dll_insert_at_end(&head, &tail, val);
                dll_print(&head);
                break;
            case 3: 
                printf("Enter position:");
                scanf("%d", &pos);
                printf("Enter Value:");
                scanf("%d", &val);
                result = dll_insert_at_pos(&head, &tail, pos, val);
                if (result == INT_MIN)
                    printf("Position doesnt Exist\n");
                dll_print(&head);
                break;
            case 4: 
                result = dll_delete_at_beg(&head, &tail);
                if (result != INT_MIN) 
                    printf("Deleted value at beginning: %d\n", result);
                else 
                    printf("List is empty\n");
                dll_print(&head);
                break;
            case 5: 
                result = dll_delete_at_end(&head, &tail);
                if (result != INT_MIN) 
                    printf("Deleted value at end: %d\n", result);
                else 
                    printf("List is empty\n");
                dll_print(&head);
                break;
            case 6: 
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                result = dll_delete_at_pos(&head, &tail, pos);
                if (result != INT_MIN) 
                    printf("Deleted value at position %d: %d\n", pos, result);
                dll_print(&head);
                break;
            case 7:
                printf("Deleting odd positioned elements\n");
                dll_delete_odd(&head, &tail);
                dll_print(&head);
                break;
            case 0: 
                exit(0);
            default: 
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void dll_print(dnode** hptr) 
{
    dnode* temp = *hptr;
    printf("Current List: ");
    while (temp != NULL) 
    {
        printf("%d->", temp->data);
        temp = temp->right;
    }
    printf("NULL");
    printf("\n");
}


void dll_insert_at_beg(dnode** hptr, dnode** tptr, int val)
{
    dnode * new = (dnode*)malloc(sizeof(dnode));
    new->data = val;
    if (*hptr == NULL)
    {
        *hptr = new;
        *tptr = new;
        new->left = NULL;
        new->right = NULL;
    }
    else
    {
        new->right = *hptr;
        new->left = NULL;
        (*hptr)->left = new; 
        *hptr = new;
    }
}


void dll_insert_at_end(dnode** hptr, dnode** tptr, int val)
{
    dnode * new = (dnode*)malloc(sizeof(dnode));
    new->data = val;
    if (*hptr == NULL)
    {
        *hptr = new;
        *tptr = new;
        new->left = NULL;
        new->right = NULL;
    }
    else 
    {
        new->left = *tptr;
        new->right = NULL;
        (*tptr)->right = new;
        *tptr = new;
    }
}


int dll_insert_at_pos(dnode** hptr, dnode** tptr,int pos,int val)
{
    if (pos == 1)
    {
        dll_insert_at_beg(hptr,tptr,val);
        return 1;
    }
    if (pos < 1)
    {
        return INT_MIN;
    }
    int c=1;
    dnode* curr = *hptr;
    while ( c < pos-1 && curr != NULL)
    {
        curr = curr->right;
        c++;
    }
    if ( curr != NULL)
    {
        dnode* next = curr->right;
        if (next == NULL)
        {
            dll_insert_at_end(hptr,tptr,val);
            return 1;
        }
        else 
        {
            dnode* new = (dnode*)malloc(sizeof(dnode));
            new->data = val;
            new->right = next;
            new->left = curr;
            curr->right = new;
            next->left = new;
            return 1;
        }
    }
    else
    {
        return INT_MIN;
    }
}


int dll_delete_at_beg(dnode** hptr, dnode** tptr)
{
    if (*hptr == NULL)
    {
        return INT_MIN;
    }
    int del_data = (*hptr)->data;
    if (*hptr == *tptr)
    {
        free(*hptr);
        *hptr = NULL;
        *tptr = NULL;
    }
    else
    {
        dnode* temp = *hptr;
        *hptr = (*hptr)->right;
        (*hptr)->left = NULL;
        free(temp);
    }
    return del_data;
}


int dll_delete_at_end(dnode** hptr, dnode** tptr)
{
    if (*hptr == NULL)
    {
        return INT_MIN;
    }
    int del_data = (*tptr)->data;
    if (*hptr == *tptr)
    {
        free(*hptr);
        *hptr = NULL;
        *tptr = NULL;
    }
    else
    {
        dnode* temp = *tptr;
        *tptr = (*tptr)->left;
        (*tptr)->right = NULL;
        free(temp);
    }
    return del_data;
}


int dll_delete_at_pos(dnode** hptr, dnode** tptr,int pos)
{
    if (*hptr == NULL || *tptr == NULL)
    {
        printf("List is Empty\n");
        return INT_MIN;
    }
    if (pos <1)
    {
        printf("Position doesnt exist");
        return INT_MIN;
    }
    int c=1;
    dnode* curr = *hptr;
    while(curr!= NULL && c < pos)
    {
        curr = curr->right;
        c++;
    }
    int del_data;
    if (curr!=NULL)
    {
        dnode * prev = curr->left;
        dnode * next = curr->right;
        if (next == NULL)
        {
            del_data= dll_delete_at_end(hptr,tptr);
            return del_data;
        }
        else if (prev == NULL)
        {
            del_data = dll_delete_at_beg(hptr,tptr);
            return del_data;
        }
        else
        {
            del_data = curr->data;
            prev->right= curr->right;
            next->left = curr->left;
            return del_data;
        }
    }
    else
    {
        printf("\nPosition doesnt exist");
        return INT_MIN;
    }
}

// function to delete odd positioned elements
void dll_delete_odd(dnode** hptr, dnode** tptr)
{
    if (*hptr == NULL)
    {
        printf("Empty List\n");
        return;
    }
    int pos = 1;
    int del_val;
    int curr_pos = 1;
    dnode* curr = *hptr;
    while (curr != NULL)
    {
        dnode* next = curr->right;
        if (curr_pos%2 != 0)
        {
            del_val = dll_delete_at_pos(hptr,tptr,pos);
            printf("Deleted Value: %d\n",del_val);
            pos --;
        }
        curr = next;
        pos++;
        curr_pos ++;
    }
}

