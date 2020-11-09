#include <iostream>
#include <cstring>
using namespace std;

typedef struct node
{
    char value;
    struct node *left, *right;
} node;

node* makeNode(char);
node* buildtree(char *, size_t, size_t);
void preTranverse(node*);
void midTranverse(node*);
void bakTranverse(node*);
void indentPrint(node*, size_t);
void printInd(size_t);
void swapTree(node *);
size_t leafCount(node *);

int main(void)
{
    char str[200] = {0};
    scanf("%s", str);
    node *root = buildtree(str, 0, strlen(str));

    // origin tree
    cout << "BiTree" << endl;
    indentPrint(root, 0);
    cout << "pre_sequence  : ";
    preTranverse(root);
    cout << endl << "in_sequence   : ";
    midTranverse(root);
    cout << endl << "post_sequence : ";
    bakTranverse(root);
    cout << endl << "Number of leaf: " << leafCount(root) << endl;

    swapTree(root);
    cout << "BiTree swapped" << endl;
    indentPrint(root, 0);
    cout << "pre_sequence  : ";
    preTranverse(root);
    cout << endl << "in_sequence   : ";
    midTranverse(root);
    cout << endl << "post_sequence : ";
    bakTranverse(root);
    cout << endl;

    return 0;
}

void swapTree(node *T)
{
    if (T == nullptr)
        return;
    else
    {
        swapTree(T->left);
        swapTree(T->right);
        node *tmp = T->left;
        T->left = T->right;
        T->right = tmp;
        return;
    }
}

size_t leafCount(node *T)
{
    if (T == nullptr)
        return 0;
    else if (T->left == nullptr && T->right == nullptr)
        return 1;
    else return leafCount(T->left) + leafCount(T->right);
}

void printInd(size_t i)
{
    i *= 4;
    for (size_t c = 0; c < i; c++)
        putchar(' ');
}

void indentPrint(node *T, size_t dep)
{
    if (T == nullptr)
        return;
    else
    {
        printInd(dep);
        putchar(T->value);
        putchar('\n');
        indentPrint(T->left, dep + 1);
        indentPrint(T->right, dep + 1);
        return;
    }
}

void preTranverse(node *T)
{
    if (T == nullptr)
        return;
    else
    {
        putchar(T->value);
        preTranverse(T->left);
        preTranverse(T->right);
    }
}

void midTranverse(node *T)
{
    if (T == nullptr)
        return;
    else
    {
        midTranverse(T->left);
        putchar(T->value);
        midTranverse(T->right);
    }
}

void bakTranverse(node *T)
{
    if (T == nullptr)
        return;
    else
    {
        bakTranverse(T->left);
        bakTranverse(T->right);
        putchar(T->value);
    }
}

node* buildtree(char *s, size_t i, size_t t)
{
    if (s[i] == '#' || i >= t)
        return nullptr;
    else
    {
        node *tmp = makeNode(s[i]);
        tmp->left = buildtree(s, 2 * i + 1, t);
        tmp->right = buildtree(s, 2 * i + 2, t);
        return tmp;
    }
}

node* makeNode(char c)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->left = tmp->right = nullptr;
    tmp->value = c;
    return tmp;
}