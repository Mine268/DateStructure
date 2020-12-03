#include <climits>
#include <iostream>
#define N 1000
#define BFOK(x) ((x) <= 1 && (x) >= -1)
#define MAX(x, y) ((x) > (y) ? (x) : (y))
using namespace std;

typedef struct node {
    char value;
    int height;
    struct node *parent, *left, *right;
    int getBF() {
        if (!this->left && !this->right)
            return 0;
        else if (this->left && !this->right)
            return this->left->height + 1;
        else if (!this->left && this->right)
            return -this->right->height - 1;
        else
            return this->left->height - this->right->height;
    }
    void updateHeight() {
        if (!this->left && !this->right)
            this->height = 0;
        else if (this->left && !this->right)
            this->height = this->left->height + 1;
        else if (!this->left && this->right)
            this->height = this->right->height + 1;
        else
            this->height = MAX(this->left->height, this->right->height) + 1;
    }
} node;

void insert(node *&, node *);
void rebalence(node *);
void leftRotate(node *);
void rightRotate(node *);
void preTranverse(node *);      // 前序遍历
void midTranverse(node *);      // 中序遍历
void posTranverse(node *);      // 后序遍历
void indentPrint(node *, int);  // 凹入遍历
void indent(int);
node *make(int);

node *mainroot = nullptr;

int main(void) {
    freopen("./test.in", "r", stdin);
    freopen("./test.out", "w", stdout);
    char tmp;
    while ((tmp = getchar()) && tmp != '\n')
        insert(mainroot, make(tmp));
    printf("Preorder: ");
    preTranverse(mainroot);
    printf("\nInorder: ");
    midTranverse(mainroot);
    printf("\nPostorder: ");
    posTranverse(mainroot);
    printf("\nTree:\n");
    indentPrint(mainroot, 0);
    return 0;
}

void indentPrint(node *r, int dep) {
    if (r) {
        indentPrint(r->right, dep + 1);
        indent(dep);
        printf("%c\n", r->value);
        indentPrint(r->left, dep + 1);
    }
}

void indent(int n) {
    while (n-- > 0) printf("    ");
}

void preTranverse(node *root) {
    if (root) {
        putchar(root->value);
        preTranverse(root->left);
        preTranverse(root->right);
    }
}

void midTranverse(node *root) {
    if (root) {
        midTranverse(root->left);
        putchar(root->value);
        midTranverse(root->right);
    }
}

void posTranverse(node *root) {
    if (root) {
        posTranverse(root->left);
        posTranverse(root->right);
        putchar(root->value);
    }
}

void rebalence(node *root) {
    if (BFOK(root->getBF()))
        return;
    else if (root->getBF() == 2) {
        if (root->left->getBF() == 1) {
            rightRotate(root);
            root->updateHeight();
            root->parent->updateHeight();
        } else {
            leftRotate(root->left);
            rightRotate(root);
            root->updateHeight();
            root->parent->left->updateHeight();
            root->parent->updateHeight();
        }
    } else {
        if (root->right->getBF() == -1) {
            leftRotate(root);
            root->updateHeight();
            root->parent->updateHeight();
        } else {
            rightRotate(root->right);
            leftRotate(root);
            root->updateHeight();
            root->parent->right->updateHeight();
            root->parent->updateHeight();
        }
    }
}

void insert(node *&root, node *nd) {
    if (root == nullptr) {
        nd->height = 0;
        root = nd;
    } else if (nd->value == root->value)
        return;
    else if (nd->value < root->value) {
        nd->parent = root;
        insert(root->left, nd);
        root->updateHeight();
    } else if (nd->value > root->value) {
        nd->parent = root;
        insert(root->right, nd);
        root->updateHeight();
    }
    rebalence(root);
    return;
}

void rightRotate(node *n) {
    if (!n->left)
        return;
    else if (!n->parent) {
        node *tmp1 = n, *tmp2 = n->left, *tmp3 = n->left->right;
        tmp1->left = tmp2->right;
        tmp2->right = tmp1;
        tmp1->parent = tmp2;
        tmp2->parent = nullptr;
        if (tmp3) tmp3->parent = tmp1;
        mainroot = tmp2;
    } else if (n == n->parent->right) {
        node *tmp1 = n->parent, *tmp2 = n, *tmp3 = n->left;
        tmp1->right = tmp3;
        tmp2->left = tmp3->right;
        tmp3->right = tmp2;
        tmp2->parent = tmp3;
        tmp3->parent = tmp1;
    } else {
        node *tmp1 = n->parent, *tmp2 = n, *tmp3 = n->left;
        tmp1->left = tmp3;
        tmp2->left = tmp3->right;
        tmp3->right = tmp2;
        tmp2->parent = tmp3;
        tmp3->parent = tmp1;
    }
}

void leftRotate(node *n) {
    if (!n->right)
        return;
    else if (!n->parent) {
        node *tmp1 = n, *tmp2 = n->right, *tmp3 = n->right->left;
        tmp1->right = tmp3;
        tmp2->left = tmp1;
        tmp1->parent = tmp2;
        tmp2->parent = nullptr;
        if (tmp3) tmp3->parent = tmp1;
        mainroot = tmp2;
    } else if (n == n->parent->left) {
        node *tmp2 = n, *tmp3 = n->right, *tmp1 = n->parent;
        tmp1->left = tmp3;
        tmp2->right = tmp3->left;
        tmp3->left = tmp2;
        tmp2->parent = tmp3;
        tmp3->parent = tmp1;
    } else {
        node *tmp1 = n->parent, *tmp2 = n, *tmp3 = n->right;
        tmp1->right = tmp3;
        tmp2->right = tmp3->left;
        tmp3->left = tmp2;
        tmp2->parent = tmp3;
        tmp3->parent = tmp1;
    }
}

node *make(int val) {
    node *tmp = (node *)malloc(sizeof(node));
    tmp->value = val;
    tmp->left = tmp->right = tmp->parent = nullptr;
    return tmp;
}