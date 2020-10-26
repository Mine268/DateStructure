#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;
#define OPTMAT(x, y) ((x)->type == 0 && (x)->optr == (y))
#define N 100

int table[][9] = {
    {1, 1, -1, -1, -1, -1, -1, 1, 1}, // +
    {1, 1, -1, -1, -1, -1, -1, 1, 1}, // -
    {1, 1, 1, 1, 1, -1, -1, 1, 1}, // *
    {1, 1, 1, 1, 1, -1, -1, 1, 1}, // /
    {1, 1, 1, 1, 1, -1, -1, 1, 1}, // %
    {1, 1, 1, 1, 1, -1, -1, 1, 1}, // ^
    {-1, -1, -1, -1, -1, -1, -1, 0, -2}, // (
    {1, 1, 1, 1, 1, 1, -2, 1, 1}, // )
    {-1, -1, -1, -1, -1, -1, -1, -2, 0} // #
};

typedef struct node
{
    short type; // 0: optr, 1: num
    bool isAlpha;
    char optr;
    int value;
    struct node *next;
} node;

class exprList
{
public:
    node *head, *tail;
    static node *makenode(short type, char optr, long value, bool isAlpha)
    {
        node *tmp = (node *)malloc(sizeof(node));
        tmp->type = type;
        tmp->optr = optr;
        tmp->value = value;
        tmp->next = nullptr;
        tmp->isAlpha = isAlpha;
        return tmp;
    }

public:
    exprList()
    {
        this->head = exprList::makenode(-1, '\0', -1, false);
        this->head->next = this->head;
        this->tail = this->head;
    }

    void push(short type, char optr, long value, bool isAlpha)
    {
        node *tmp = exprList::makenode(type, optr, value, isAlpha);
        tmp->next = this->tail->next;
        this->tail->next = tmp;
        this->tail = tmp;
    }

    void pop()
    {
        node *tmp = this->head->next;
        this->head->next = this->head->next->next;
        this->tail->next = this->head->next;
        // free(tmp);
    }

    bool empty()
    {
        return this->head == this->tail;
    }

    // 查找语法错误，除法错误在运算中查找
    bool legal()
    {
        return true;
    }

    // 按照类别输出运算符和数字
    void toString()
    {
        node *tmp = this->head;
        while (tmp != this->tail)
        {
            tmp = tmp->next;
            if (tmp->type == 0)
                cout << "operator: " << tmp->optr << endl;
            else
                cout << "number: " << tmp->value << endl;
        }
    }

    // 析构函数
    void Destroy()
    {
        node *tmp, *ptmp;
        tmp = this->head->next;
        ptmp = this->head;

        while (tmp != tail)
        {
            free(ptmp);
            ptmp = tmp;
            tmp = tmp->next;
        }
        free(ptmp);
        free(tmp);
    }

    node *getHead()
    {
        return this->head;
    }

    node *getTail()
    {
        return this->tail;
    }
};

void answer();
void makechain(exprList &, char *);
bool isOptr(char);
bool isNumb(char);
// 比较前后优先级，<:-1，=:0，>:1
int proceed(char, char);
// 返回优先级层次
int righteous(char);

int main(void)
{
    int T;
    cin >> T;
    getchar();
    while (T-- > 0)
        answer();
    return 0;
}

void answer()
{
    char str[N];
    exprList exprChain;
    memset(str, 0, sizeof(char) * N);
    fgets(str, N, stdin);

    makechain(exprChain, str);

    if (exprChain.empty() == true)
        putchar('\n');
    else
    {
        stack<char> OPTR;
        OPTR.push('#');
        node *cur = exprChain.getHead()->next;
        while (!OPTMAT(cur, '#') || OPTR.top() != '#')
        {
            if (cur->type == 1)
            {
                if (cur->isAlpha == true)
                    putchar(cur->value);
                else
                    printf("%d", cur->value);
                cur = cur->next;
            }
            else
            {
                switch (proceed(OPTR.top(), cur->optr))
                {
                case -1:
                    OPTR.push(cur->optr);
                    cur = cur->next;
                    break;
                case 0:
                    OPTR.pop();
                    cur = cur->next;
                    break;
                case 1:
                    char tmpOptr = OPTR.top();
                    OPTR.pop();
                    putchar(tmpOptr);
                    break;
                }
            }
        }
        while (OPTR.size() != 1)
        {
            putchar(OPTR.top());
            OPTR.pop();
        }
        putchar('\n');
    }

    exprChain.Destroy();
    return;
}

void makechain(exprList &cur, char *str)
{
    int ind = 0;
    while (str[ind] != '\n')
    {
        if (isOptr(str[ind]) == true)
        {
            if (str[ind] != '-')
                cur.push(0, str[ind++], -1, false);
            else if (isNumb(str[ind + 1]) == false || (isNumb(str[ind + 1]) == true && ind != 0 && (isNumb(str[ind - 1]) || str[ind - 1] == ')')))
                cur.push(0, str[ind++], -1, false);
            else
            {
                long tmp = 0;
                long positive = str[ind] == '-' ? -1 : 1;
                if (positive == -1)
                    ind++;
                while (isNumb(str[ind]))
                {
                    tmp *= 10;
                    tmp += str[ind] - '0';
                    ind++;
                }
                tmp *= positive;
                cur.push(1, '\0', tmp, false);
            }
        }
        else
        {
            if (str[ind] >= 'a' && str[ind] <= 'z' || str[ind] >= 'A' && str[ind] <= 'Z')
                cur.push(1, '\0', str[ind++], true);
            else
            {
                long tmp = 0;
                long positive = str[ind] == '-' ? -1 : 1;
                if (positive == -1)
                    ind++;
                while (isNumb(str[ind]))
                {
                    tmp *= 10;
                    tmp += str[ind] - '0';
                    ind++;
                }
                tmp *= positive;
                cur.push(1, '\0', tmp, false);
            }
        }
    }
    return;
}

bool isOptr(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' || c == '(' || c == ')' || c == '#';
}

bool isNumb(char c)
{
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9';
}

int proceed(char c1, char c2)
{
    return table[righteous(c1)][righteous(c2)];
}

int righteous(char c)
{
    switch (c)
    {
    case '#':
        return 8;
    case '+':
        return 0;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 3;
    case '%':
        return 4;
    case '^':
        return 5;
    case '(':
        return 6;
    case ')':
        return 7;
    }
    return -2;
}
