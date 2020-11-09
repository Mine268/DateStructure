#include <iostream>
#include <queue>
#include <cstring>
#define N 1000
#define size_t long
using namespace std;

typedef struct node
{
    char value;
    struct node *left, *right;
} node;

queue<node> que;

node *makeNode(char);
node *buildTree(char *, char *, size_t, size_t, size_t, size_t);

char in_seq[N], post_seq[N];
int main(void)
{
    node *root;
    scanf("%s", in_seq);
    getchar();
    scanf("%s", post_seq);
    getchar();

    size_t len = strlen(in_seq);
    root = buildTree(in_seq, post_seq, 0, len - 1, 0, len - 1);

    que.push(*root);
    while (que.empty() == false)
    {
        node tmp = que.front();
        que.pop();
        if (tmp.left != nullptr)
            que.push(*(tmp.left));
        if (tmp.right != nullptr)
            que.push(*(tmp.right));
        putchar(tmp.value);
    }
    putchar('\n');

    return 0;
}

node *buildTree(char I[], char P[], size_t i, size_t j, size_t m, size_t n)
{
    if (i > j)
        return nullptr;
    else if (i == j)
        return makeNode(I[i]);
    else
    {
        size_t s;
        for (s = i; s <= j && I[s] != P[n]; s++);
        node *tmp = makeNode(P[n]);
        tmp->left = buildTree(I, P, i, s - 1, m, m + (s - i) - 1);
        tmp->right = buildTree(I, P, s + 1, j, m + (s - i), n - 1);
        return tmp;
    }
}

node *makeNode(char c)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->value = c;
    tmp->left = tmp->right = nullptr;
    return tmp;
}