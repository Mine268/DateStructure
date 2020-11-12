#include <iostream>
#include <cstdlib>
#include <cstring>
#define N 30
using namespace std;

typedef struct node
{
    char val;
    struct node *left, *right;
} node;

typedef struct
{
    char val;
    int l;
    int r;
} dataNode, *dataSet;

node *make(char);
node *buildtree(dataSet, int);

int main(void)
{
    freopen("./test.in", "r", stdin);
    freopen("./test.out", "w", stdout);

    dataNode data1[N], data2[N];
    int n;
    node *t1, *t2;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char c1, c2, c3;
        scanf("%c %c %c", &c1, &c2, &c3);
        data1[i].val = c1;
        data1[i].l = c2 != '-' ? c2 - '0' : -1;
        data1[i].r = c3 != '-' ? c3 - '0' : -1;
    }
    for (int i = 0; i < n; i++)
    {
        char c1, c2, c3;
        scanf("%c %c %c", &c1, &c2, &c3);
        data2[i].val = c1;
        data2[i].l = c2 != '-' ? c2 - '0' : -1;
        data2[i].r = c3 != '-' ? c3 - '0' : -1;
    }

    t1 = buildtree(data1, n);
    t2 = buildtree(data2, n);

    return 0;
}

node *buildtree(dataSet ds, int n)
{
    int mark[N], root = 0;
    memset(mark, 0, sizeof(int) * N);
    for (int i = 0; i < n; i++)
    {
        if (ds[i].l != -1)
            mark[ds[i].l] = 1;
        if (ds[i].r != -1)
            mark[ds[i].r] = 1;
    }
    while (mark[root] == 1)
        root++;

    return nullptr;
}

node *make(char c)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->val = c;
    tmp->left = tmp->right = nullptr;
    return tmp;
}