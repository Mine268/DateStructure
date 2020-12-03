#include <iostream>
#define N 1000
using namespace std;

typedef struct node {
    int value;
    struct node *parent, *left, *right;
} node;

void insert(node *&, node *);
void midTranverse(node *);
void indentPrint(node *, int);
void indent(int);
node *make(int);

node *root = nullptr;

int main(void) {
    freopen("./test.in", "r", stdin);
    freopen("./test.out", "w", stdout);

    int tmp = -1;
    do {
        scanf("%d", &tmp);
        if (!tmp) break;
        else insert(root, make(tmp));
    } while (true);
    indentPrint(root, 0);
    putchar('\n');
    midTranverse(root);
    putchar('\n');
    return 0;
}

void indentPrint(node * r, int dep) {
    if (r) {
        indentPrint(r->left, dep + 1);
        indent(dep);
        printf("%d\n", r->value);
        indentPrint(r->right, dep + 1);
    }
}

void indent(int n) {
    while (n-- > 0)
        printf("    ");
}

void midTranverse(node *root) {
    if (root) {
        midTranverse(root->left);
        printf(" %d", root->value);
        midTranverse(root->right);
    }
}

void insert(node *&root, node *nd) {
    if (root == nullptr)
        root = nd;
    else {
        node *now = root;
        bool flag = true;
        while (flag) {
            if (nd->value < now->value) {
                if (now->left)
                    now = now->left;
                else
                    flag = false;
            } else {
                if (now->right)
                    now = now->right;
                else
                    flag = false;
            }
        }
        if (nd->value < now->value) {
            now->left = nd;
            nd->parent = now;
        } else {
            now->right = nd;
            nd->parent = now;
        }
    }
    return;
}

node *make(int val) {
    node *tmp = (node *)malloc(sizeof(node));
    tmp->value = val;
    tmp->left = tmp->right = tmp->parent = nullptr;
    return tmp;
}