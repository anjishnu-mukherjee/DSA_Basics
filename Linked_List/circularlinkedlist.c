#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct cll
{
   int data;
   struct cll* link;
} cnode;


void cll_insert_at_beg(cnode **tptr, int val);
void cll_insert_at_end(cnode **tptr, int val);
int cll_insert_at_pos(cnode **tptr, int pos, int val);
int cll_delete_at_beg(cnode **tptr);
int cll_delete_at_end(cnode **tptr);
int cll_delete_at_pos(cnode **tptr, int pos);
int cll_delete_by_val(cnode **tptr, int val);
void cll_print(cnode **tptr);


int main()
{
   cnode *tail = NULL;
   int ch, pos, val, result;


   while (1)
   {
       printf("\nCircular Linked List Operations:\n");
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


       switch (ch)
       {
           case 1:
               printf("Enter value to insert at beginning: ");
               scanf("%d", &val);
               cll_insert_at_beg(&tail, val);
               cll_print(&tail);
               break;


           case 2:
               printf("Enter value to insert at end: ");
               scanf("%d", &val);
               cll_insert_at_end(&tail, val);
               cll_print(&tail);
               break;


           case 3:
               printf("Enter position to insert: ");
               scanf("%d", &pos);
               printf("Enter value to insert at position %d: ", pos);
               scanf("%d", &val);
               cll_insert_at_pos(&tail, pos, val);
               cll_print(&tail);
               break;


           case 4:
               result = cll_delete_at_beg(&tail);
               if (result != INT_MIN)
                   printf("Deleted value from beginning: %d\n", result);
               cll_print(&tail);
               break;


           case 5:
               result = cll_delete_at_end(&tail);
               if (result != INT_MIN)
                   printf("Deleted value from end: %d\n", result);
               cll_print(&tail);
               break;


           case 6:
               printf("Enter position to delete: ");
               scanf("%d", &pos);
               result = cll_delete_at_pos(&tail, pos);
               if (result != INT_MIN)
                   printf("Deleted value from position %d: %d\n", pos, result);
               cll_print(&tail);
               break;


           case 7:
               printf("Enter value to delete: ");
               scanf("%d", &val);
               result = cll_delete_by_val(&tail, val);
               if (result != INT_MIN)
                   printf("Deleted value: %d\n", val);
               cll_print(&tail);
               break;


           case 8:
               cll_print(&tail);
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


void cll_insert_at_beg(cnode **tptr, int val)
{
   cnode *new_node = (cnode *)malloc(sizeof(cnode));
   new_node->data = val;
   if (*tptr == NULL)
   {
       *tptr = new_node;
       new_node->link = new_node;
   }
   else
   {
       new_node->link = (*tptr)->link;
       (*tptr)->link = new_node;
   }
}


void cll_insert_at_end(cnode **tptr, int val)
{
   cnode *new_node = (cnode *)malloc(sizeof(cnode));
   new_node->data = val;
   if (*tptr == NULL)
   {
       *tptr = new_node;
       new_node->link = new_node;
   }
   else
   {
       new_node->link = (*tptr)->link;
       (*tptr)->link = new_node;
       *tptr = new_node;
   }
}


int cll_delete_at_beg(cnode **tptr)
{
   if (*tptr == NULL)
   {
       printf("List is Empty\n");
       return INT_MIN;
   }
   cnode *curr = (*tptr)->link;
   int del_data = curr->data;


   if (*tptr == curr)
   {
       *tptr = NULL;
   }
   else
   {
       (*tptr)->link = curr->link;
   }


   free(curr);
   return del_data;
}


int cll_delete_at_end(cnode **tptr)
{
   if (*tptr == NULL)
   {
       printf("List is Empty\n");
       return INT_MIN;
   }
   cnode *curr = (*tptr)->link;
   int del_data;


   if (*tptr == curr)
   {
       del_data = curr->data;
       *tptr = NULL;
       free(curr);
       return del_data;
   }


   while (curr->link != *tptr)
   {
       curr = curr->link;
   }


   del_data = (*tptr)->data;
   curr->link = (*tptr)->link;
   free(*tptr);
   *tptr = curr;
   return del_data;
}


int cll_insert_at_pos(cnode **tptr, int pos, int val)
{
    if (pos < 1)
    {
        printf("Invalid Position!\n");
        return INT_MIN;
    }


    if (pos == 1)
    {
        cll_insert_at_beg(tptr, val);
        return 0;
    }


    cnode *new_node = (cnode *)malloc(sizeof(cnode));
    new_node->data = val;


    cnode *curr = (*tptr)->link;
    int c = 1;


    while (curr != *tptr && c < pos - 1)
    {
        curr = curr->link;
        c++;
    }


    if (c == pos - 1)
    {
        new_node->link = curr->link;
        curr->link = new_node;


        if (curr == *tptr)
        {
            *tptr = new_node;
        }
        return 0;
    }
    else
    {
        printf("Position out of bounds!\n");
        free(new_node);
        return INT_MIN;
    }
}




int cll_delete_at_pos(cnode **tptr, int pos)
{
   if (*tptr == NULL)
   {
       printf("List is empty!\n");
       return INT_MIN;
   }
   
   if (pos < 1)
   {
       printf("Invalid Position!\n");
       return INT_MIN;
   }


   cnode *curr = (*tptr)->link;
   cnode *prev = NULL;
   int c = 1;
   if (pos == 1)
   {
       return cll_delete_at_beg(tptr);
   }


   while (curr != *tptr && c < pos)
   {
       prev = curr;
       curr = curr->link;
       c++;
   }


   if (c == pos)
   {
       prev->link = curr->link;


       if (curr == *tptr)
       {
           *tptr = prev;  
       }


       int del_data = curr->data;
       free(curr);
       return del_data;
   }
   else
   {
       printf("Position out of bounds!\n");
       return INT_MIN;
   }
}




int cll_delete_by_val(cnode **tptr, int val)
{
   if (*tptr == NULL)
   {
       printf("List is Empty\n");
       return INT_MIN;
   }


   cnode *curr = (*tptr)->link;


   if (curr->data == val)
   {
       return cll_delete_at_beg(tptr);
   }


   while (curr->link != *tptr && curr->link->data != val)
   {
       curr = curr->link;
   }


   if (curr->link->data == val)
   {
       if (curr->link == *tptr)
       {
           return cll_delete_at_end(tptr);
       }
       else
       {
           cnode *del_node = curr->link;
           int del_data = del_node->data;
           curr->link = del_node->link;
           free(del_node);
           return del_data;
       }
   }


   printf("Value not found\n");
   return INT_MIN;
}


void cll_print(cnode **tptr)
{
   if (*tptr == NULL)
   {
       printf("NULL\n");
   }
   else
   {
       cnode *curr = (*tptr)->link;
       do
       {
           printf("%d -> ", curr->data);
           curr = curr->link;
       } while (curr != (*tptr)->link);


       printf("NULL\n");
   }
}