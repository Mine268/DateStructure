/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
} NODE;

NODE *find(NODE *, int *);
void outputring(NODE *);
void change(int, int, NODE *);
void outputring(NODE *pring)
{
    NODE *p;
    p = pring;
    if (p == NULL)
        printf("NULL");
    else
        do
        {
            printf("%d", p->data);
            p = p->next;
        } while (p != pring);
    printf("\n");
    return;
}

int main()
{
    int n, m;
    NODE *head, *pring;

    scanf("%d%d", &n, &m);
    head = (NODE *)malloc(sizeof(NODE));
    head->next = NULL;
    head->data = -1;

    change(n, m, head);
    pring = find(head, &n);
    printf("ring=%d\n", n);
    outputring(pring);

    getchar(); getchar();

    return 0;
}

/* Here is waiting for you.
void change( int n, int m, NODE * head )
{
}

NODE * find( NODE * head, int * n )
{
}
*/

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

#include <string.h>
NODE *create(int num)
{
    NODE *ptr = (NODE *)malloc(sizeof(NODE));
    ptr->next = NULL;
    ptr->data = num;
    return ptr;
} // 创建节点

void change(int n, int m, NODE *head)
{
    n += m;
    m *= 10;
    n %= m;
    int mark[m], t1 = -1, c = 0; // t1是整除结果
    NODE *tmp1 = head, *tmp2 = NULL;
    memset(mark, 0, sizeof(mark));
    do
    {
        c++;
        n *= 10;
        t1 = n / m;
        n %= m;
        mark[n] += c;

        tmp2 = create(t1);
        tmp1->next = tmp2;
        tmp1 = tmp1->next;
    } while (mark[n] - c == 0);

    int start = mark[n] - c;
    NODE *pstart = head, *pend = head;
    while (pend->next != NULL)
    {
        pend = pend->next;
        if (start >= 0)
        {
            pstart = pstart->next;
            start--;
        }
    }

    if (n == 0)
        pstart->next = NULL;
    else
        pend->next = pstart;
}

NODE *find(NODE *head, int *n)
{
    NODE *p = head;
    int len = 0;
    while (p->next != NULL && p->next->data >= 0)
    {
        p->next->data *= -1;
        p->next->data -= 1;
        p = p->next;
        len++;
    }
    *n = 0;
    if (p->next == NULL)
    {
        *n = 0;
        return NULL;
    }
    else
    {
        p = p->next;
        while (p->next->data < 0)
        {
            p->next->data += 1;
            p->next->data *= -1;
            p = p->next;
            (*n)++;
        }
        return p;
    }
}