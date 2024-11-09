#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct dcll 
{
    int data;
    struct dcll* next;
    struct dcll* prev;
} dcnode;

void dcll_insert_at_beg(dcnode** hptr, dcnode** tptr, int val);
void dcll_insert_at_end(dcnode** hptr, dcnode** tptr, int val);
int dcll_insert_at_pos(dcnode** hptr, dcnode** tptr, int pos, int val);
int dcll_delete_at_beg(dcnode** hptr, dcnode** tptr);
int dcll_delete_at_end(dcnode** hptr, dcnode** tptr);
int dcll_delete_at_pos(dcnode** hptr, dcnode** tptr, int pos);
int dcll_delete_by_val(dcnode** hptr, dcnode** tptr, int val);
void dcll_print(dcnode** hptr);

int main() 
{
    dcnode* tail = NULL;
    dcnode* head = NULL;
    int ch, pos, val, result;

    while (1) 
    {
        printf("\nDoubly Circular Linked List Operations:\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete from Position\n");
        printf("7. Delete by Value\n");
        printf("8. Print List\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter value to insert at beginning: ");
                scanf("%d", &val);
                dcll_insert_at_beg(&head, &tail, val);
                dcll_print(&head);
                break;

            case 2:
                printf("Enter value to insert at end: ");
                scanf("%d", &val);
                dcll_insert_at_end(&head, &tail, val);
                dcll_print(&head);
                break;

            case 3:
                printf("Enter position to insert: ");
                scanf("%d", &pos);
                printf("Enter value to insert at position %d: ", pos);
                scanf("%d", &val);
                result = dcll_insert_at_pos(&head, &tail, pos, val);
                if (result == INT_MIN) 
                {
                    printf("Invalid Position\n");
                }
                dcll_print(&head);
                break;

            case 4:
                result = dcll_delete_at_beg(&head, &tail);
                if (result != INT_MIN)
                    printf("Deleted value from beginning: %d\n", result);
                dcll_print(&head);
                break;

            case 5:
                result = dcll_delete_at_end(&head, &tail);
                if (result != INT_MIN)
                    printf("Deleted value from end: %d\n", result);
                dcll_print(&head);
                break;

            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                result = dcll_delete_at_pos(&head, &tail, pos);
                if (result != INT_MIN)
                    printf("Deleted value from position %d: %d\n", pos, result);
                dcll_print(&head);
                break;

            case 7:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                result = dcll_delete_by_val(&head, &tail, val);
                if (result != INT_MIN)
                    printf("Deleted value: %d\n", val);
                dcll_print(&head);
                break;

            case 8:
                dcll_print(&head);
                break;

            case 9:
                exit(0);
                break;

            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
    return 0;
}

void dcll_insert_at_beg(dcnode** hptr, dcnode** tptr, int val) 
{
    dcnode* new = (dcnode*)malloc(sizeof(dcnode));
    new->data = val;
    if (*hptr == NULL) 
    {
        *hptr = new;
        *tptr = new;
        new->next = new;
        new->prev = new;
    } 
    else 
    {
        new->next = *hptr;
        new->prev = *tptr;
        (*hptr)->prev = new;
        (*tptr)->next = new;
        *hptr = new;
    }
}

void dcll_insert_at_end(dcnode** hptr, dcnode** tptr, int val) 
{
    dcnode* new = (dcnode*)malloc(sizeof(dcnode));
    new->data = val;
    if (*hptr == NULL) 
    {
        *hptr = new;
        *tptr = new;
        new->next = new;
        new->prev = new;
    } 
    else 
    {
        new->next = *hptr;
        new->prev = *tptr;
        (*hptr)->prev = new;
        (*tptr)->next = new;
        *tptr = new;
    }
}

int dcll_insert_at_pos(dcnode** hptr, dcnode** tptr, int pos, int val) 
{
    if (pos <= 0)
        return INT_MIN;

    if (pos == 1) 
    {
        dcll_insert_at_beg(hptr, tptr, val);
        return 0;
    }

    dcnode* current = *hptr;
    int count = 1;

    
    while (current != *tptr && count < pos - 1) 
    {
        current = current->next;
        count++;
    }

    if (count == pos - 1) 
    {
        dcnode* new = (dcnode*)malloc(sizeof(dcnode));
        new->data = val;
        new->next = current->next;
        new->prev = current;
        current->next->prev = new;
        current->next = new;
        return 0;
    }

    return INT_MIN; 
}

int dcll_delete_at_beg(dcnode** hptr, dcnode** tptr) 
{
    if (*hptr == NULL) 
    {
        printf("List Empty!\n");
        return INT_MIN;
    }
    int del_val = (*hptr)->data;
    dcnode* temp = *hptr;


    if (*hptr == *tptr) 
    {
        *hptr = NULL;
        *tptr = NULL;
    }
    else 
    {
        *hptr = (*hptr)->next;
        (*hptr)->prev = *tptr;
        (*tptr)->next = *hptr;
    }
    free(temp);
    return del_val;
}

int dcll_delete_at_end(dcnode** hptr, dcnode** tptr) 
{
    if (*hptr == NULL) 
    {
        printf("List Empty!\n");
        return INT_MIN;
    }
    int del_val = (*tptr)->data;
    dcnode* temp = *tptr;

    
    if (*hptr == *tptr) 
    {
        *hptr = NULL;
        *tptr = NULL;
    } else 
    {
        *tptr = (*tptr)->prev;
        (*tptr)->next = *hptr;
        (*hptr)->prev = *tptr;
    }
    free(temp);
    return del_val;
}

int dcll_delete_at_pos(dcnode** hptr, dcnode** tptr, int pos) 
{
    if (*hptr == NULL) 
    {
        printf("Empty List!\n");
        return INT_MIN;
    }

    if (pos <= 0)
        return INT_MIN;

    if (pos == 1) 
    {
        return dcll_delete_at_beg(hptr, tptr);
    }

    dcnode* current = *hptr;
    int count = 1;

    
    while (current != *tptr && count < pos) 
    {
        current = current->next;
        count++;
    }

    if (count == pos) 
    {
        if (current == *tptr) 
        {
            return dcll_delete_at_end(hptr, tptr);
        }

        int del_val = current->data;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
        return del_val;
    }

    return INT_MIN; 
}

int dcll_delete_by_val(dcnode** hptr, dcnode** tptr, int val) 
{
    if (*hptr == NULL) 
    {
        printf("Empty List!\n");
        return INT_MIN;
    }

    dcnode* current = *hptr;

    do 
    {
        if (current->data == val) 
        {
            if (current == *hptr) 
            {
                return dcll_delete_at_beg(hptr, tptr);
            }
            if (current == *tptr) 
            {
                return dcll_delete_at_end(hptr, tptr);
            }

            int del_val = current->data;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            return del_val;
        }
        current = current->next;
    } while (current != *hptr);

    printf("Value Not Found!\n");
    return INT_MIN;
}

void dcll_print(dcnode** hptr) 
{
    if (*hptr == NULL) 
    {
        printf("List is empty!\n");
        return;
    }

    dcnode* current = *hptr;
    printf("List: ");
    do 
    {
        printf("%d ", current->data);
        current = current->next;
    } while (current != *hptr);

    printf("\n");
}