#include <iostream>
#include <stack>
#include <cstring>
#include <queue>
#define N 1000
#define M 5000
#define ISNUM(x) ('a' <= (x) && 'z' >= (x))
#define ISOPE(x)                                                           \
    ((x) == '!' || (x) == '&' || (x) == '|' || (x) == '-' || (x) == '+' || \
     (x) == '(' || (x) == ')' || (x) == '#')
#define ISDIG(x) ((x) >= '0' && (x) <= '9')
using namespace std;

// ! & | - + ( ) #
const int priority[8][8] = {
    // 1:>  -1:<  0:=
    1,  1, 1, 1, 1, -1, 1, 1, -1, 1,  1,  1,  1,  -1, 1,  1,
    -1, 1, 1, 1, 1, -1, 1, 1, -1, 1,  1,  1,  1,  -1, 1,  1,
    -1, 1, 1, 1, 1, -1, 1, 1, -1, -1, -1, -1, -1, -1,  0, -2,
    1,  1, 1, 1, 1, -2, 1, 1, -1, -1, -1, -1, -1, -1, -2, -1};

typedef struct Node {
    enum TYPE { OPERAND, NUMBER };
    enum OPERATOR { NOT, AND, OR, IMPLI, EQUV };
    Node *left, *right;
    Node::TYPE type;
    char name;
    Node::OPERATOR optr;

    bool getValue(bool *table) {
        if (this->type == NUMBER)
            return table[(unsigned long long)(this->name)];
        else {
            if (this->optr == NOT)
                return !this->left->getValue(table);
            else {
                bool f1 = this->left->getValue(table),
                     f2 = this->right->getValue(table);
                switch (this->optr) {
                    case AND:
                        return f1 && f2;
                    case OR:
                        return f1 || f2;
                    case IMPLI:
                        return !f1 || f2;
                    case EQUV:
                        return f1 == f2;
                }
            }
        }
    }
} Node;

Node *root = nullptr;
char str[M];
char vars[N];

void insert(Node *&r, Node *o, Node *n);
Node *buildTree(char *);  // 构建树
Node *make(Node::OPERATOR);
Node *make(char);
int compare(char, char);
int cmp(const void *, const void *);
Node::OPERATOR convert(char);

int main(void) {
    bool b1[N], table[N];
    int varcount = 0;
    queue<int> min;  // 极小项，如果存在赋值使得命题公式为1，那么就是一个极小项
    queue<int> max;  // 极大项，如果存在赋值使得命题公式为0，那么就是一个极大项
    cin >> str;

    memset(b1, false, sizeof(bool) * N);
    int l = strlen(str);
    str[l] = '#';
    str[l + 1] = 0;
    for (int i = 0; str[i] != 0; i++)  // 统计命题变量的数量
        if (ISNUM(str[i]) && !b1[str[i]]) {
            if (!ISDIG(str[i + 1])) {
                vars[varcount++] = str[i];
                b1[str[i]] = true;
            } else {
                vars[varcount++] = str[i + 1];
                b1[str[i + 1]] = true;
            }
        }

    root = buildTree(str);
    qsort(vars, varcount, sizeof(char), cmp);
    long limit = 1 << varcount, j, t;
    for (long i = 0; i < limit; i++) {
        memset(table, false, sizeof(bool) * N);
        t = 0;
        j = i;
        while (j != 0) {
            table[vars[t++]] = j & 1;
            j >>= 1;
        }
        if (root->getValue(table))
            min.push(i);
        else
            max.push(i);
    }

    if (!min.empty())
        while (!min.empty()) {
            printf("m%d ", min.front());
            min.pop();
            if (!min.empty())
                printf("∨ ");  // ∨
        }
    else printf("0 ");
    printf(";");
    if (!max.empty())
        while (!max.empty()) {
            printf(" M%d", max.front());
            max.pop();
            if (!max.empty())
                printf(" ∧");  // ∧
        }
    else printf(" 1");
    putchar('\n');
    return 0;
}

int cmp(const void *a, const void *b) {
    return -*((char*)a) + *((char*)b);
}

Node *buildTree(char *str) {
    stack<char> OPTR;
    stack<Node *> OPND;
    int i = 0;
    char c = 0;
    OPTR.push('#');
    c = str[i++]; if (ISNUM(c) && ISDIG(str[i])) c = str[i++];
    while (c != '#' || OPTR.top() != '#') {
        if (!ISOPE(c)) {
            OPND.push(make(c));
            c = str[i++]; if (ISNUM(c) && ISDIG(str[i])) c = str[i++];
        } else {
            switch (compare(OPTR.top(), c)) {  // 1:>  -1:<  0:=
                case -1:
                    OPTR.push(c);
                    c = str[i++]; if (ISNUM(c) && ISDIG(str[i])) c = str[i++];
                    break;
                case 0:
                    OPTR.pop();
                    c = str[i++]; if (ISNUM(c) && ISDIG(str[i])) c = str[i++];
                    break;
                case 1:
                    char optrtmp = OPTR.top();
                    OPTR.pop();
                    if (optrtmp != '!') {
                        Node *a, *b;
                        b = OPND.top();
                        OPND.pop();
                        a = OPND.top();
                        OPND.pop();
                        Node *tmp = make(convert(optrtmp));
                        tmp->left = a;
                        tmp->right = b;
                        OPND.push(tmp);
                    } else {
                        Node *x = OPND.top();
                        OPND.pop();
                        Node *tmp = make(Node::NOT);
                        tmp->left = x;
                        OPND.push(tmp);
                    }
                    break;
            }
        }
    }
    return OPND.top();
}

Node::OPERATOR convert(char c) {
    switch(c) {
        case '!': return Node::NOT;
        case '&': return Node::AND;
        case '|': return Node::OR;
        case '-': return Node::IMPLI;
        case '+': return Node::EQUV;
    }
    return Node::NOT;
}

int compare(char a, char b) {
    int i, j;
    switch (a) {
        case '!':
            i = 0;
            break;
        case '&':
            i = 1;
            break;
        case '|':
            i = 2;
            break;
        case '-':
            i = 3;
            break;
        case '+':
            i = 4;
            break;
        case '(':
            i = 5;
            break;
        case ')':
            i = 6;
            break;
        case '#':
            i = 7;
            break;
    }
    switch (b) {
        case '!':
            j = 0;
            break;
        case '&':
            j = 1;
            break;
        case '|':
            j = 2;
            break;
        case '-':
            j = 3;
            break;
        case '+':
            j = 4;
            break;
        case '(':
            j = 5;
            break;
        case ')':
            j = 6;
            break;
        case '#':
            j = 7;
            break;
    }
    return priority[i][j];
}

Node *make(char val) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->left = tmp->right = nullptr;
    tmp->type = Node::TYPE::NUMBER;
    tmp->name = val;
    return tmp;
}

Node *make(Node::OPERATOR op) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->left = tmp->right = nullptr;
    tmp->type = Node::TYPE::OPERAND;
    tmp->optr = op;
    return tmp;
}

void insert(Node *&r, Node *o, Node *n) {
    if (r == nullptr)
        r = o;
    else {
        o->left = r;
        o->right = n;
        r = o;
    }
}