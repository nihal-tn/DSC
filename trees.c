#include<stdio.h>
#include<stdbool.h>
#include<time.h>
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
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}
void postorder(struct node* root)
{
    if (root != NULL)
    {
        inorder(root->left);
        inorder(root->right);
        printf("%d \n", root->key);
    }
}
void preorder(struct node* root)
{
    if (root != NULL)
    {
        printf("%d \n", root->key);
        inorder(root->left);
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
void search(int k, struct node *root)
{
    if(root->key==k)
    {
        if(root->right==NULL && root->left==NULL)
        {
            printf("NULL<--%d-->NULL\n",root->key);
            return;
        }
        else if(root->right==NULL)
        {
            printf("%d<--%d-->NULL\n",root->left->key,k) ;
            return;
        }
        else if(root->left==NULL)
        {
            printf("NULL<--%d-->%d\n",k,root->right->key) ;
            return;
        }
        else
        {
            printf("%d<--%d-->%d\n",root->left->key,root->key,root->right->key);
            return;
        }
    }
    else if (k>root->key && root->right!=NULL)
        search(k,root->right);
    else if (k<root->key && root->left!=NULL)
        search(k,root->left);
    else
    {
        printf("%d is not in the tree....\n",k);
        return;
    }
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
        int k=root_->key;
        if(root->key==k)
        {
            root=delete(root,k) ;
            printf("%d is deleted\n",k);
            root=insert(root, k) ;
            printf("%d is inserted\n",k);
            if(!(treeisbalanced(root)))
                balance(root) ;
            return;
        }
        else if(k>=root->key)
        {
            if(k==root->right->key)
            {
                root->right=delete(root->right,k) ;
                printf("%d is deleted\n",k);
                root->right=insert(root->right, k) ;
                printf("%d is inserted\n",k);
                if(!(treeisbalanced(root)))
                    balance(root->right) ;
                return;
            }
            else if(k>root->right->key)
            {
                root->right->right=delete(root->right->right,k) ;
                printf("%d is deleted\n",k);
                root->right->right=insert(root->right->right, k) ;
                printf("%d is inserted\n",k);
                if(!(treeisbalanced(root)))
                    balance(root->right->right) ;//once try giving balance(root->right->right)
                return;
            }
            else
            {
                root->right->left=delete(root->right->left,k) ;
                printf("%d is deleted\n",k);
                root->right->left=insert(root->right->left, k) ;
                printf("%d is inserted\n",k);
                if(!(treeisbalanced(root)))
                    balance(root->right->left) ;//onec try giving balance(root->right->left)
                return;
            }
        }
        else
        {
            if(k==root->left->key)
            {
                root->left=delete(root->left,k) ;
                printf("%d is deleted\n",k);
                root->left=insert(root->left, k) ;
                printf("%d is inserted\n",k);
                if(!(treeisbalanced(root)))
                    balance(root) ;
                return;
            }
            else if(k>root->left->key)
            {
                root->left->right=delete(root->left->right,k) ;
                printf("%d is deleted\n",k);
                root->left->right=insert(root->left->right, k) ;
                printf("%d is inserted\n",k);
                if(!(treeisbalanced(root)))
                    balance(root->left->right) ;//once try giving balance(root->left->right)
                return;
            }
            else
            {
                root->left->left=delete(root->left->left,k) ;
                printf("%d is deleted\n",k);
                root->left->left=insert(root->left->left, k) ;
                printf("%d is inserted\n",k);
                if(!(treeisbalanced(root)))
                    balance(root->left->left) ;//once try giving balance(root->left->left)
                return;
            }
        }
    }
}
int main()
{
    int i,choice,o;
    printf("1.for normal tree\n2.balanced tree\n") ;
    scanf("%d",&o);
    while(1)
    {
        printf("1.to insert\n2.to search\n3.to delete\n");
        printf("4.for inorder traversal\n5.for preorder treversal\n6.for postordrer traversal\n") ;
        printf("7.for minimum value in the tree\n8.for maximum value in tree\n9.to check weather the tree is balanced or not\n") ;
        printf("10.for depth of the tree\n11.to get the value in the root\n") ;
        scanf("%d",&choice);
        if (choice==1 && o==1)
        {
            while(1)
            {
                printf("enter the value that you want to insert\n") ;
                scanf("%d",&i);
                if(i==-1)
                    break;
                else
                    root=insert(root,i);
            }
        }
        else if(choice==1 && o==2)
        {
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
                }
            }
        }
        else if(choice==2)
        {
            while(1)
            {
                printf("enter the element that you want to search for\n") ;
                scanf("%d",&i) ;
                if(i==-1)
                    break;
                search(i,root) ;
            }
        }
        else if(choice==3 && o==2)
        {
            printf ("enter the element that you want to delete\n");
            scanf("%d",&i) ;
            root=delete(root,i) ;
            balance(root) ;
        }
        else if(choice==3 && o==1)
        {
            printf ("enter the element that you want to delete\n");
            scanf("%d",&i) ;
            root=delete(root,i) ;
        }
        else if(choice==4)
            inorder(root);
        else if(choice==5)
            preorder(root);
        else if(choice==6)
            postorder(root) ;
        else if(choice==7)
            printf("minimum value in the tree is %d \n",minnode(root)->key);
        else if(choice==8)
            printf("maximum value in the tree is %d \n",maxnode(root)->key);
        else if(choice==9)
        {
            if(treeisbalanced(root))
                printf(" tree is balanced\n") ;
            else
                printf("tree is unbalanced\n") ;
        }
        else if(choice==10)
            printf("depth of the tree is %d\n",depth(root)) ;
        else if(choice==11)
            printf ("value in the root is %d\n",root->key) ;
        else
            printf("invalid input\nplease enter a valid input\n") ;
    }
}
