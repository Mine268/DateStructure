/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} NODE;

void output(NODE *, int);
void change(int, int, NODE *);

void output(NODE *head, int kk)
{
    int k = 0;

    printf("0.");
    while (head->next != NULL && k < kk)
    {
        printf("%d", head->next->data);
        head = head->next;
        k++;
    }
    printf("\n");
}

int main()
{
    int n, m, k;
    NODE *head;

    scanf("%d%d%d", &n, &m, &k);
    head = (NODE *)malloc(sizeof(NODE));
    head->next = NULL;
    head->data = -1;
    change(n, m, head);
    output(head, k);
    return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

#include <set>
#include <vector>
#include <algorithm>
using namespace std;

NODE *makeNode(int val)
{
    NODE *tmp = (NODE *)malloc(sizeof(NODE));
    tmp->next = NULL;
    tmp->data = val;
    return tmp;
}

typedef struct RNODE
{
    int remain;
    NODE *node;
} RNODE;

void change(int n, int m, NODE *head)
{
    vector<RNODE> nodeSet;
    int dividend = n * 10, divisor = m, remainder = -1, quotient = 0;
    NODE *thead = head;

    while (remainder != 0 /* || nodeSet.find(*makeNode(remainder))._Ptr == NULL*/ )
    {
        quotient = dividend / divisor;
        remainder = dividend % divisor;
        dividend = remainder * 10;

        bool flag = true;
        NODE *start;
        for (long long i = 0; i < nodeSet.size(); i++)
            if (nodeSet[i].remain == remainder)
            {
                flag = false;
                start = nodeSet[i].node;
                break;
            }
        if (flag) // todo: 当前余数未出现过
        {
            NODE *tmp = makeNode(quotient);

            thead->next = tmp;
            thead = thead->next;
            nodeSet.push_back({remainder, tmp});
        }
        else
        {
            NODE *tmp = makeNode(quotient);

            thead->next = tmp;
            thead = thead->next;
            thead->next = start->next;
            break;
        }
    }

    return;
}
