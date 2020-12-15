#include<stdlib.h>
#include<stdio.h>
struct node
{
    int n;
    struct node *right,*left;
};
struct node *root;
struct node *temp_head, *prev;
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
    }
}
void insert(int k)
{
    temp_head=root;
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
void delete_(int k,struct node *temp_hea)
{
    if(temp_hea->n==k)
    {
        printf("%d<--%d-->%d\n",temp_hea->left,temp_hea,temp_hea->right);
        if(temp_hea->right==NULL && temp_hea->left==NULL)
        {
            //node is leaf
            if(prev->right->n==k)
            {
                prev->right=NULL;
            }
            else if(prev->left->n==k)
            {
                prev->left=NULL;
            }
            printf("successfully deleted %d \n",temp_hea->n);
            free(temp_hea);
            return;
        }
        else if(temp_hea->right==NULL && temp_hea->left!=NULL)
        {
            //node has only one child (only left child) 
            if(prev->right->n==k)
            {
                prev->right=temp_hea->left;
                free(temp_hea) ;
            }
            else if(prev->left->n==k)
            {
                prev->left=temp_hea->left;
                free(temp_hea);
            }
            printf("successfully deleted %d \n",temp_hea->n);
            return;
        }
        else if(temp_hea->right!=NULL && temp_hea->left==NULL)
        {
            //node has only one child (only right child) 
            if(prev->right->n==k)
            {
                prev->right=temp_hea->right;
                free(temp_hea) ;
            }
            else if(prev->left->n==k)
            {
                prev->left=temp_hea->right;
                free(temp_head);
            }
            printf("successfully deleted %d \n",temp_hea->n);
            return;
        }
        else if(temp_hea->right!=NULL && temp_hea->left!=NULL)
        {
            //if node has two children
            
        }
    }

    else if (k>temp_hea->n && temp_hea->right!=NULL)
    {
        prev=temp_hea;
        delete_(k, temp_hea->right);
    }
    else if (k<temp_hea->n && temp_hea->left!=NULL)
    {
        prev=temp_hea;
        delete_(k, temp_hea->left);
    }
    else
    {
        printf("%d is not in the tree....\n",k);
        return;
    }
}
int main()
{
    int e,a,o,d;
    root=(struct node*)malloc(sizeof(struct node));
    root->left=NULL;
    root->right=NULL;
    printf("enter the data in the root\n");
    scanf("%d",&root->n);
    while(1)
    {
        printf("to enter the elements into the tree enter 1\n");
        printf("to search for the element if it is there in the tree enter 2\n");
        printf("to display the elements in the tree in inorder format enter 3\n");
        printf("to display the elements in the tree in preorder format enter 4\n");
        printf("to display the elements in the tree in postorder format enter 5\n");
        printf("to delete the elements in the tree enter 6\n");
        printf("to the depth of the tree enter 7\n") ;
        scanf("%d",&o);
        if(o==1)
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
        else if(o==2)
        {
            printf("enter the element that you want to search for \n");
            scanf("%d",&e);
            temp_head=root;
            search(e);
        }
        else if(o==3)
        {
            temp_head=root;
            inorder(temp_head);
        }
        else if(o==4)
        {
            temp_head=root;
            preorder(temp_head);
        }
        else if(o==5)
        {
            temp_head=root;
            postorder(temp_head);
        }
        else if(o==6)
        {
            temp_head=root;
            printf("enter the element that you want to delete\n");
            scanf("%d",&e);
            delete_(e, temp_head);
        }
        if(o==7)
        {
            temp_head=root;
            d=depth(temp_head);
            printf("depth of the tree is %d\n",d);
        }

        else
        {
            printf("invalid input........\nenter a valid input\n");
        }
    }
}
