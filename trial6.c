#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct stack
{
    int size;
    int top;
    char *array;
};
char peek(struct stack *s)
{
    return s->array[s->top-1];
}
int isempty(struct stack *s)
{
    if(s->top==0)
    return 1;
    return 0;
}
int isfull(struct stack *s)
{
    if(s->top==s->size)
    return 1;
    return 0;
}
void push(struct stack *s,char c)
{
    if(!isfull(s))
    {
        s->array[s->top]=c;
        s->top++;
    }
}
char pop(struct stack *s)
{
    if(!isempty(s))
    {
        s->top--;
        return s->array[s->top];
    }
}
int prefference(char ch)
{
    if(ch == '*' || ch=='/')
        return 3;
    else if(ch == '+' || ch=='-')
        return 2; 
    else
        return 0;
}
int isoperator(char ch)
{
    if(ch=='+' || ch=='-' ||ch=='*' || ch=='/') 
        return 1;
    else
        return 0;
}
char* convert(char *infix)
{
    struct stack *s=(struct stack*)malloc(sizeof(struct stack));
    s->size=10;
    s->top=0;
    s->array=(char*)malloc(10*sizeof(char));
    char *postfix=(char*)malloc((strlen(infix)+1)*sizeof(char));
    int i=0,j=0;
    while(infix[i]!='\0')
    {
        if(!isoperator(infix[i]))
        {
            postfix[j]=infix[i];
            i++;
            j++;
        }
        else
        {
            if(prefference(infix[i])>prefference(peek(s)))
            {
                push(s,infix[i]);
                i++;
            }
            else
            {
                postfix[j]=pop(s);
                j++;
            }
        }
    }
    while (!isempty(s))
    {
        postfix[j]=pop(s);
        j++;
    }
    postfix[j]='\0';
    return postfix;
}
int main()
{
    char * infix = (char*)malloc(sizeof(char));
    printf("enter the infix notation\n");
    scanf("%s",infix);
    printf("postfix is %s", convert(infix));
}