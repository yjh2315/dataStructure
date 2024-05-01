#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct StackNode
{
    element item;
    struct StackNode *link;
} StackNode;

typedef struct
{
    StackNode *top;
} LinkedStackType;

void push(LinkedStackType *s, element item)
{
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    if (temp == NULL)
    {
        fprintf(stderr, "error\n");
        return;
    }
    else
    {
        temp->item = item;
        temp->link = s->top;
        s->top = temp;
    }
}

element pop(LinkedStackType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "error\n");
        exit(1);
    }
    else
    {
        StackNode *temp = s->top;
        int item = temp->item;
        s->top = s->top->link;
        free(temp);
        return item;
    }
}

int is_empty(LinkedStackType *s)
{
    if (s == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    LinkedStackType *top = (LinkedStackType *)malloc(sizeof(LinkedStackType));
    push(top, 10);
    push(top, 11);

    printf("%d\n", pop(top));
    printf("%d\n", pop(top));
}