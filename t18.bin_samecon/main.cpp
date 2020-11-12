#include <iostream>
#include <queue>
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
    int l, r;
} dataNode, *dataSet;

node *make(char);
node *buildtree(dataSet, int, int);
bool judgeSame(node*, node*);
void printtree(node*);

int main(void)
{
    freopen("./test.in", "r", stdin);
    freopen("./test.out", "w", stdout);

    dataNode data1[N], data2[N];
    int n = 0, m = 0, r1 = -1, r2 = -1;
    node *t1 = nullptr, *t2 = nullptr;

    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        char c1, c2, c3;
        scanf("%c %c %c", &c1, &c2, &c3);
        getchar();
        data1[i].val = c1;
        data1[i].l = c2 != '-' ? c2 - '0' : -1;
        data1[i].r = c3 != '-' ? c3 - '0' : -1;
        if (c1 == 'A')
            r1 = i;
    }
    scanf("%d", &m);
    getchar();
    for (int i = 0; i < m; i++)
    {
        char c1, c2, c3;
        scanf("%c %c %c", &c1, &c2, &c3);
        getchar();
        data2[i].val = c1;
        data2[i].l = c2 != '-' ? c2 - '0' : -1;
        data2[i].r = c3 != '-' ? c3 - '0' : -1;
        if (c1 == 'A')
            r2 = i;
    }

    t1 = buildtree(data1, r1, n);
    t2 = buildtree(data2, r2, m);

    if (judgeSame(t1, t2))
        printf("Yes.\n");
    else
        printf("No.\n");

    return 0;
}

node *buildtree(dataSet ds, int r, int n)
{
    if (r == -1 || r >= n)
        return nullptr;
    else
    {
        node *sr = make(ds[r].val);
        if (ds[r].l != r)
            sr->left = buildtree(ds, ds[r].l, n);
        else
            return nullptr;
        if (ds[r].r != r)
            sr->right = buildtree(ds, ds[r].r, n);
        else
            return nullptr;
        return sr;
    }
}

void printtree(node *t)
{
    queue<node*> q;
    q.push(t);
    while (q.empty() == false)
    {
        node *tmp = q.front();
        q.pop();
        if (tmp == nullptr)
            cout << '#';
        else
        {
            cout << tmp->val;
            q.push(tmp->left);
            q.push(tmp->right);
        }
    }
}

bool judgeSame(node *r1, node *r2)
{
    if (r1 == nullptr && r2 == nullptr)
        return true;
    else if (r1 == nullptr || r2 == nullptr)
        return false;
    else
    {
        bool f1, f2, f3;
        f1 = r1->val == r2->val;
        f2 = judgeSame(r1->left, r2->left) && judgeSame(r1->right, r2->right);
        f3 = judgeSame(r1->left, r2->right) && judgeSame(r1->right, r2->left);
        return f1 && (f2 || f3);
    }
}

node *make(char c)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->val = c;
    tmp->left = tmp->right = nullptr;
    return tmp;
}