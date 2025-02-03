/*
Write a function which will take any number n as its argument. The function will break this
number into its individual digits and then store every single digit in a separate node thereby
forming a linked list. The function must return the head node address of the created linked list at
the end. (For example, if the number is 13579, then there will be 5 nodes in the list containing
nodes with values 1, 3, 5, 7, 9).
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node * link;
}node;

node* createnode(int data)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

node* convert(node* h, int num)
{
    if (num == 0)
    {
        return createnode(0);
    }
    for(int i = num;i>0;i= i/10)
    {
        node* newnode = createnode(i%10);
        newnode->link = h; // always insert at beginning
        h = newnode;
    }
    return h;
}

void print_list(node* head)
{
    printf("The List: ");
    node* temp = head;
    while (temp != NULL)
    {
        printf("%d->",temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}

int main()
{
    int n;
    printf("Enter the number: ");
    scanf("%d",&n);

    node* head = NULL;

    head = convert(head,n);
    printf("The Original Number: %d\n",n);
    print_list(head);
}