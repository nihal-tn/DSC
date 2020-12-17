#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
struct node
{
    int n;
    struct node *right,*left;
};
struct node *root_;
struct node *temp_head;
void insert_1(int k)
{

    if ((temp_head->n>k) && (temp_head->left!=NULL))
    {
        temp_head=temp_head->left;
        insert_1(k);
    }
    else if ((temp_head->n<=k)&&(temp_head->right!=NULL))
    {
        temp_head=temp_head->right;
        insert_1(k);
    }
}
void insert_2(int k)
{
    if(k>=temp_head->n)
    {
        struct node *delta;
        delta=(struct node*)malloc(sizeof(struct node));
        delta->left=NULL;
        delta->right=NULL;
        delta->n=k;
        temp_head->right=delta;
        printf("%d is inserted to the right of %d \n",k,temp_head->n);
        return;
    }
    else if(k<temp_head->n)
    {
        struct node *delta;
        delta=(struct node*)malloc(sizeof(struct node));
        delta->left=NULL;
        delta->right=NULL;
        delta->n=k;
        temp_head->left=delta;
        printf("%d is inserted to the left of %d \n",k,temp_head->n);
        return;
    }
}
void insert(int k)
{
    temp_head=root_;
    insert_1(k);
    insert_2(k);
}
void search(int k)
{
    if(temp_head->n==k)
    {
        printf("%d is in the tree.....\n%d<--%d-->%d\n",k,temp_head->left,temp_head->n,temp_head->right);
        return;
    }
    else if (k>temp_head->n && temp_head->right!=NULL)
    {
        temp_head=temp_head->right;
        search(k);
    }
    else if (k<temp_head->n && temp_head->left!=NULL)
    {
        temp_head=temp_head->left;
        search(k);
    }
    else
    {
        printf("%d is not in the tree....\n",k);
        return;
    }
}
void inorder(struct node *temp_head)
{
    if (temp_head==NULL)
        return;
    inorder(temp_head->left);
    printf("%d\n",temp_head->n);
    inorder(temp_head->right);
}
void postorder(struct node *temp_head)
{
    if (temp_head==NULL)
        return;
    postorder(temp_head->left);
    postorder(temp_head->right);
    printf("%d\n",temp_head->n);
}
void preorder(struct node *temp_head)
{
    if (temp_head==NULL)
        return;
    printf("%d\n",temp_head->n);
    preorder(temp_head->left);
    preorder(temp_head->right);
}
int depth(struct node* temp_head)
{
    if (temp_head == NULL)
        return -1;
    int leftDepth = depth(temp_head->left);
    int rightDepth = depth(temp_head->right);
    if (leftDepth > rightDepth)
        return leftDepth + 1;
    else
        return rightDepth + 1;
}
struct node* min(struct node *temp)
{
    struct node *current=temp;
    while (current && current->left!=NULL)
    {
        current=current->left;
    }
    return current;
}
struct node* max(struct node *temp)
{
    struct node *current=temp;
    while (current && current->right!=NULL)
    {
        current=current->right;
    }
    return current;
}
int balance_factor(struct node * dummy)
{
    return depth(dummy->left) - depth(dummy->right) ;
}
struct node* delete_(struct node* root, int key)
{
    if (root == NULL)
        return root;
    if (key < root->n)
        root->left = delete_(root->left, key);
    else if (key > root->n)
        root->right = delete_(root->right, key);
    else
    {
        //write some code to delete root_ node from the tree....... 
        if (root->left == NULL)
        {
            struct node* temp = root->right;
            struct node* du=root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node* temp = root->left;
            struct node* du=root->left;
            free(root);
            return temp;
        }
        if(depth(root->right)>=depth(root->left))
        {
            struct node* temp = min(root->right);
            root->n = temp->n;
            root->right = delete_(root->right, temp->n);
        }
        else if(depth(root->right)<depth(root->left))
        {
            struct node* temp = max(root->left);
            root->n = temp->n;
            root->left = delete_(root->left, temp->n);
        }
    }
    return root;
}
bool is_Height_Balanced(struct node *root)
{
    int leftHeight, rightHeight;
    if(root == NULL)
        return true;
    leftHeight = depth(root->left);
    rightHeight = depth(root->right);
    if(abs(leftHeight - rightHeight) <= 1 &&
            is_Height_Balanced(root->right) &&
            is_Height_Balanced(root->left))
        return true;
    else
        return false;
}
void balance(struct node *dummy)
{
    if (dummy==NULL)
        return;
    balance(dummy->left);
    balance(dummy->right);
    if(!(is_Height_Balanced(dummy))) 
    {
        int k=dummy->n;
        temp_head=root_;
        root_=delete_(temp_head,dummy->n);
        printf("%d is deleted\n",k);
        insert(k);
    }
}
int main()
{
    int e,a,o,d,c;
    root_=(struct node*)malloc(sizeof(struct node));
    root_->left=NULL;
    root_->right=NULL;
    printf("enter the data in the root\n");
    scanf("%d",&root_->n);
    printf("for normal tree enter 1\nfor balanced tree enter 2\n") ;
    scanf("%d",&c);
    while(1)
    {
        printf("to enter the elements into the tree enter------------------------>1\n");
        printf("to search for the element if it is there in the tree enter------->2\n");
        printf("to display the elements in the tree in inorder format enter------>3\n");
        printf("to display the elements in the tree in preorder format enter----->4\n");
        printf("to display the elements in the tree in postorder format enter---->5\n");
        printf("to delete the elements in the tree enter------------------------->6\n");
        printf("to the depth of the tree enter----------------------------------->7\n") ;
        printf("to get the maximum value of the tree enter----------------------->8\n") ;
        printf("to get the minimum value of the tree enter----------------------->9\n") ;
        printf("to check the balance status of the tree enter-------------------->10\n") ;
        scanf("%d",&o);
        if(o==1 && c==1)
        {
            while(1)
            {
                printf("enter the data that you want to insert\n");
                scanf("%d",&a);
                if(a==-1)
                    break;
                else
                    insert(a);
            }
        }
        else if(o==1 && c==2)
        {
            while(1)
            {
                printf("enter the data that you want to insert\n");
                scanf("%d",&a);
                if(a==-1)
                    break;
                else
                {
                    insert(a);
                    temp_head=root_;
                    balance(temp_head);
                }
            }
        }
        else if(o==2)
        {
            printf("enter the element that you want to search for \n");
            scanf("%d",&e);
            temp_head=root_;
            search(e);
        }
        else if(o==3)
        {
            temp_head=root_;
            inorder(temp_head);
        }
        else if(o==4)
        {
            temp_head=root_;
            preorder(temp_head);
        }
        else if(o==5)
        {
            temp_head=root_;
            postorder(temp_head);
        }
        else if(o==6 && c==1)
        {
            struct node *tem=root_;
            printf("enter the element that you want to delete\n");
            scanf("%d",&e);
            root_=delete_(tem,e);
            printf("value in global root = %d \n",root_->n);
        }
        else if(o==6 && c==2) 
        {
            struct node *tem=root_;
            printf("enter the element that you want to delete\n") ;
            scanf("%d",&e) ;
            root_=delete_(tem,e);
            temp_head=root_;
            balance(temp_head);
            printf("value in global root = %d \n",root_->n);
        }
        else if(o==7)
        {
            temp_head=root_;
            d=depth(temp_head);
            printf("depth of the tree is %d\n",d);
        }
        else if(o==8)
        {
            temp_head=root_;
            struct node *max_=max(temp_head);
            printf("maximum value in the tree is %d ",max_->n);
        }
        else if(o==9)
        {
            temp_head=root_;
            struct node *min_=min(temp_head);
            printf("minimum value in the tree is %d ",min_->n);
        }
        else if(o==10)
        {
            temp_head=root_;
            if(is_Height_Balanced(temp_head))
            {
                printf(" tree is balanced\n") ;
            }
            else
            {
                printf("tree is unbalanced\n") ;
            }
        }
        else
        {
            printf("invalid input........\nenter a valid input\n");
        }
    }
}
