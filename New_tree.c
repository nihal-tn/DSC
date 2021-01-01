#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<stdbool.h>
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
int max(int a, int b)
{
    return (a > b) ? a : b;
}
int depth(struct Node *root)
{
    if (root == NULL)
        return 0;
    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);
    if (leftDepth > rightDepth)
        return leftDepth + 1;
    else
        return rightDepth + 1;
}
bool treeisbalanced(struct Node *root)
{
    int leftHeight, rightHeight;
    if(root == NULL)
        return true;
    leftHeight = depth(root->left);
    rightHeight = depth(root->right);
    if(abs(leftHeight - rightHeight) <= 1 &&
            treeisbalanced(root->right) &&
            treeisbalanced(root->left))
        return true;
    else
        return false;
}
struct Node *newNode(int key)
{
    struct Node *node = (struct Node *)
                        malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
struct Node* minnode(struct Node* node)
{
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}
struct Node* maxnode(struct Node* node)
{
    struct Node* current = node;
    while (current && current->right != NULL)
        current = current->right;
    return current;
}
struct Node *insert(struct Node *node, int key);
struct Node* delete(struct Node* root, int key)
{
    if(root==NULL)
        return NULL;
    else if(key>root->key)
        root->right=delete(root->right, key) ;
    else if(key<root->key)
        root->left=delete(root->left, key) ;
    else
    {    
        if (root->left == NULL)
        {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        if(root->right->height >=root->left->height)
        {
            struct Node* temp = minnode(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
        else
        {
            struct Node* temp = maxnode(root->left);
            root->key = temp->key;
            root->left = delete(root->left, temp->key);
        }
    }
    root->height = 1 + max(height(root->left),
                           height(root->right));
    int balance=getBalance(root) ;
    if(abs(balance)>1)
    {
        int k=root->key;
        //printf("%d deleting\n",k);
        root=delete(root, k);
        root=insert(root, k);
    }
    return root;
}
struct Node *insert(struct Node *node, int key)
{
    struct Node *parent;
    if (node == NULL)
    {
        printf("%d is inserted\n",key);
        return (newNode(key));
    }
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    node->height = 1 + max(height(node->left),
                           height(node->right));
    int balance=getBalance(node) ;
    if(abs(balance)>1)
    {
        int k=node->key;
        printf("%d deleting\n",k);
        node=delete(node, k);
        node=insert(node, k);
    }
    return node;
}
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d(height=%d)(balance factor=%d)\n",root->key,root->height,getBalance(root));
        inorder(root->right);
    }
}
int main()
{
    struct Node *root = NULL;
    clock_t begin=clock() ;
    for (int i=0; i<1000; i++)
    {
        root=insert(root, i) ;
    }
    clock_t end=clock() ;
    inorder(root);
    printf ("%d\n",(double)(end-begin) / CLOCKS_PER_SEC) ;
    if(treeisbalanced(root))
        printf("balanced\n") ;
    else
        printf("unbalanced\n") ;
}
