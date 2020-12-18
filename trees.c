#include<stdio.h>
#include<stdbool.h>
struct node {
    int key;
    struct node *left, *right;
};
struct node *root=NULL;
struct node* newNode(int item)
{
    struct node* temp
        = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
void inorder(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}
struct node* insert(struct node* node, int key)
{
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return node;
}
struct node* minnode(struct node* node)
{
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}
struct node* maxnode(struct node* node)
{
    struct node* current = node;
    while (current && current->right != NULL)
        current = current->right;
    return current;
}
int depth(struct node *root)
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
bool treeisbalanced(struct node *root)
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
bool nodeisbalanced(struct node *root)
{
    int leftHeight, rightHeight;
    if(root == NULL)
        return true;
    leftHeight = depth(root->left);
    rightHeight = depth(root->right);
    if(abs(leftHeight - rightHeight) <= 1)
        return true;
    else
        return false;
}
struct node* delete(struct node* root, int key)
{
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = delete(root->left,key) ;
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        if(depth(root->right) >=depth(root->right))
        {
            struct node* temp = minnode(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
        else
        {
            struct node* temp = maxnode(root->left);
            root->key = temp->key;
            root->right = delete(root->left, temp->key);
        }
    }
    return root;
}
void balance(struct node *root_)
{
    if (root_==NULL) 
        return NULL;
    balance(root_->left) ;
    balance(root_->right) ;
    if(!(nodeisbalanced(root_)))
    {
        int k=root->key;
        root=delete(root,k) ;
        printf("%d is deleted\n",k);
        root=insert(root, k) ;
        printf("%d is inserted\n",k);
    }
}
int main()
{
    int i;
    while(1)
    {
        printf("enter the value that you want to insert\n") ;
        scanf("%d",&i);
        if(i==-1) 
        break;
        else
        {
        root=insert(root,i);
        balance(root) ;
        if(treeisbalanced(root)) 
        printf("tree is balanced\n") ;
        else
        printf("tree is unbalanced\n") ;
        }
    }
    inorder(root) ;
    
}
