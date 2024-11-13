#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node * left;
    struct node * right;
    int h;
}tnode;


tnode* newNode(int data)
{
    tnode * new = (tnode*)malloc(sizeof(tnode));
    new->data = data;
    new->right = NULL;
    new->left = NULL;
    return new;
}


tnode* insert(tnode * root, int data)
{
    if (root == NULL)
    {
        return newNode(data);
    }
    
    if (data > root->data)
    {
        root->right = insert(root->right,data);
    }
    else if (data < root->data)
    {
        root->left = insert(root->left,data);
    }
    return root;
}


tnode* findSucc(tnode* root)
{
    tnode* curr = root;
    if (curr && curr->left != NULL)
    {
        findSucc(curr->left);
    }
    return curr;
}

tnode* delete(tnode* root, int key)
{
    if (root == NULL)
    {
        return root;
    }

    if (key > root->data)
    {
        root->right = delete(root->right,key);
    }
    else if ( key < root->data)
    {
        root->left = delete(root->left,key);
    }
    else
    {
        tnode* temp ;
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }

        temp = findSucc(root->right);
        root->data = temp->data;
        root->right = delete(root->right,temp->data);
    }
    return root;
}


tnode* search(tnode* root, int key)
{
    if (root == NULL || root->data == key)
    {
        return root;
    }

    if (root->data > key)
    {
        return search(root->left, key);
    }
    else
    {
        return search(root->right,key);
    }
}


int height(tnode* root)
{
    if (root == NULL)
    {
        return -1;
    }

    int lh = height(root->left);
    int rh = height(root->right);
    root->h = ((lh >= rh)? lh : rh) + 1;
    return root->h;
}

void inorder(tnode* root) 
{
    if (root != NULL) 
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}


void inorderprint(tnode* root) 
{
    if (root != NULL) 
    {
        inorderprint(root->left);
        int lh = height(root->left); 
        int rh = height(root->right); 
        root->h = ((lh >= rh) ? lh : rh) + 1; 
        printf("%d(%d) ", root->data, root->h); 
        inorderprint(root->right);
    }
}

int main() 
{
    tnode* root = NULL;
    int choice, value,h;

    while (1) 
    {
        printf("\nBinary Search Tree Menu:\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. In-order traversal\n");
        printf("4. Search an element\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                h = height(root);
                printf("Height: %d\n",h);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = delete(root, value);
                h = height(root);
                printf("Height: %d\n",h);
                break;
            case 3:
                printf("In-order traversal: ");
                inorder(root);
                printf("\n");
                h = height(root);
                inorderprint(root);
                printf("Height: %d",h);
                break;
            case 4:
                printf("Enter element to search: ");
                scanf("%d", &value);
                tnode * out = search(root,value);
                if ( out != NULL)
                {
                    printf("Elenemt Found!\n");
                }
                else
                {
                    printf("Element not Found\n");
                }
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}