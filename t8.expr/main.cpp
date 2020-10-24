#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;
#define OPTMAT(x, y) ((x)->type == 0 && (x)->optr == (y))
#define N 1000

int table[][9] = {
    {1, 1, -1, -1, -1, -1, -1, 1, 1},
    {1, 1, -1, -1, -1, -1, -1, 1, 1},
    {1, 1, 1, 1, 1, -1, -1, 1, 1},
    {1, 1, 1, 1, 1, -1, -1, 1, 1},
    {1, 1, 1, 1, 1, -1, -1, 1, 1},
    {1, 1, 1, 1, 1, -1, -1, 1, 1},
    {-1, -1, -1, -1, -1, -1, -1, 0, -2},
    {1, 1, 1, 1, 1, 1, -2, 1, 1},
    {-1, -1, -1, -1, -1, -1, -1, -2, 0},
};

typedef struct node
{
    short type; // 0: optr, 1: num
    char optr;
    long value;
    struct node *next;
} node;

class List
{
public:
    node *head, *tail;
    static node *makenode(short type, char optr, long value)
    {
        node *tmp = (node *)malloc(sizeof(node));
        tmp->type = type;
        tmp->optr = optr;
        tmp->value = value;
        tmp->next = nullptr;
        return tmp;
    }

public:
    List()
    {
        this->head = List::makenode(-1, '\0', -1);
        this->head->next = this->head;
        this->tail = this->head;
    }

    void push(short type, char optr, long value)
    {
        node *tmp = List::makenode(type, optr, value);
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
        // ()
        node *tmp = this->head->next;
        long sum = 0;
        while (tmp != this->head)
        {
            if (OPTMAT(tmp, '('))
                sum++;
            else if (OPTMAT(tmp, ')'))
                sum--;
            if (sum < 0)
                return false;
            else
                tmp = tmp->next;
        }
        if (sum != 0)
            return false;

        tmp = this->head->next;
        while (tmp != this->head)
        {
            if (tmp->type == 1 && tmp->next->optr == '(')
                return false;
            tmp = tmp->next;
        }
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
void makechain(List &, char *);
bool isOptr(char);
bool isNumb(char);
// 比较前后优先级，<:-1，=:0，>:1
int proceed(char, char);
// 返回优先级层次
int righteous(char);
long calculate(long, char, long);

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
    List exprChain;
    memset(str, 0, sizeof(char) * N);
    fgets(str, N, stdin);

    // 检查非法字符，合法的字符为运算符和数字
    for (int i = 0; str[i] != '\n'; i++)
        if (!isNumb(str[i]) && !isOptr(str[i]))
        {
            cout << "error." << endl;
            return;
        }

    makechain(exprChain, str);
    // exprChain.toString();

    // TODO 在这里继续计算
    if (exprChain.legal() == false)
        cout << "error." << endl;
    else
    {
        stack<char> OPTR;
        stack<long> OPND;
        exprChain.push(0, '#', -1);
        OPTR.push('#');
        node *cur = exprChain.getHead(), *end = exprChain.getTail();

        if (cur->next->type == 0 && cur->next->optr == '-')
        {
            node *tmp = List::makenode(1, '\0', 0);
            tmp->next = cur->next;
            cur->next = tmp;
        }

        cur = cur->next;

        while (!OPTMAT(cur, '#') || OPTR.top() != '#')
        {
            if (cur->type == 1)
            {
                OPND.push(cur->value);
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
                    if (OPTR.size() == 1)
                    {
                        cout << "error." << endl;
                        return;
                    }
                    char tmpOptr = OPTR.top();
                    OPTR.pop();

                    if (OPND.empty() == true)
                    {
                        cout << "error." << endl;
                        return;
                    }
                    long tmpNum1 = OPND.top();
                    OPND.pop();

                    if (OPND.empty() == true)
                    {
                        cout << "error." << endl;
                        return;
                    }
                    long tmpNum2 = OPND.top();
                    OPND.pop();

                    if (tmpOptr == '/' && tmpNum1 == 0)
                    {
                        cout << "Divide 0." << endl;
                        return;
                    }
                    if (tmpOptr == '^' && tmpNum1 < 0)
                    {
                        cout << "error." << endl;
                        return;
                    }
                    OPND.push(calculate(tmpNum2, tmpOptr, tmpNum1));
                    break;
                }
            }
        }
        if (OPND.size() != 1)
        {
            cout << "error." << endl;
            return;
        }
        cout << OPND.top() << endl;
    }

    exprChain.Destroy();
    return;
}

void makechain(List &cur, char *str)
{
    int ind = 0;
    while (str[ind] != '\n')
    {
        if (isOptr(str[ind]) == true)
        {
            if (str[ind] != '-')
                cur.push(0, str[ind++], -1);
            else if (isNumb(str[ind + 1]) == false || (isNumb(str[ind + 1]) == true && ind != 0 && (isNumb(str[ind - 1]) || str[ind - 1] == ')')))
                cur.push(0, str[ind++], -1);
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
                cur.push(1, '\0', tmp);
            }
        }
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
            cur.push(1, '\0', tmp);
        }
    }
    return;
}

bool isOptr(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' || c == '(' || c == ')';
}

bool isNumb(char c)
{
    return c >= '0' && c <= '9';
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

long calculate(long a, char optr, long b)
{
    switch (optr)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '%':
        return a % b;
    case '^':
        long tmp = 1;
        while (b-- > 0)
            tmp *= a;
        return tmp;
    }
}