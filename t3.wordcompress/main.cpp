/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct sdata
{
    char data;
    struct sdata *next;
} SNODE;

// setlink : 根据读入的字符串初始化字符串链表
// outlink : 根据给定的字符串链表输出字符串
void setlink(SNODE *, char *), outlink(SNODE *);
// 返回字符串链表的长度
int listlen(SNODE *);
// 压缩字符串链表
SNODE *ziplist(SNODE *, SNODE *);
// 返回指向后缀开始的指针，若没有则指向NULL
SNODE *findlist(SNODE *, SNODE *);

int main()
{
    SNODE *head1, *head2, *head;
    char str1[100], str2[100];

    gets(str1);
    gets(str2);

    head1 = (SNODE *)malloc(sizeof(SNODE));
    head2 = (SNODE *)malloc(sizeof(SNODE));
    head = (SNODE *)malloc(sizeof(SNODE));
    head->next = head1->next = head2->next = NULL;

    setlink(head1, str1);
    setlink(head2, str2);

    head->next = ziplist(head1, head2);

    head->next = findlist(head1, head2);
    outlink(head);
    return 0;
}

void setlink(SNODE *head, char *str)
{
    SNODE *p;

    while (*str != '\0')
    {
        p = (SNODE *)malloc(sizeof(SNODE));
        p->data = *str;
        p->next = NULL;
        str++;
        head->next = p;
        head = p;
    }
    return;
}

void outlink(SNODE *head)
{
    while (head->next != NULL)
    {
        printf("%c", head->next->data);
        head = head->next;
    }
    printf("\n");
    return;
}

int listlen(SNODE *head)
{
    int len = 0;
    while (head->next != NULL)
    {
        len++;
        head = head->next;
    }
    return len;
}

SNODE *findlist(SNODE *head1, SNODE *head2)
{
    int m, n;
    SNODE *p1 = head1, *p2 = head2;

    m = listlen(head1);
    n = listlen(head2);
    while (m > n)
    {
        p1 = p1->next;
        m--;
    }
    while (m < n)
    {
        p2 = p2->next;
        n--;
    }

    while (p1->next != NULL && p1->next != p2->next)
    {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1->next;
}
/* Here is waiting for you!     */
/*
  SNODE * ziplist( SNODE * head1, SNODE * head2 )
  {
  }
*/

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

SNODE *ziplist(SNODE *head1, SNODE *head2)
{
    int m, m2, n, n2, merge = 0, end = 0;
    m2 = m = listlen(head1);
    n2 = n = listlen(head2);
    SNODE *p1 = head1->next, *p2 = head2->next;
    char t1[100] = {0}, t2[100] = {0};

    while (m > n)
    {
        p1 = p1->next;
        m--;
    }
    while (m < n)
    {
        p2 = p2->next;
        n--;
    }

    for (end = 0; m > 0; m--, end++)
    {
        t1[end] = p1->data;
        t2[end] = p2->data;
        p1 = p1->next;
        p2 = p2->next;
    }

    while (end-- > 0 && t1[end] == t2[end])
        merge++;

    if (merge == 0) return NULL;
    else
    {
        int q1, q2;
        q1 = m2 - merge;
        q2 = n2 - merge;

        while (q1-- > 0) head1 = head1->next;
        while (q2-- > 0) head2 = head2->next;

        head2->next = head1->next;
        return head1->next;
    }
}
