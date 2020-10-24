#include <iostream>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;

class List
{
private:
    typedef struct node
    {
        short type; // 0: optr, 1: num
        char optr;
        long value;
        struct node *next;
    } node;
    node *head, *tail;
    static node* makenode(short type, char optr, long value)
    {
        node *tmp = (node *)malloc(sizeof(node));
        tmp->type = type;
        tmp->optr = optr;
        tmp->value = value;
        tmp->next = nullptr;
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
        free(tmp);
    }

    node *front()
    {
        return this->head->next;
    }

    bool empty()
    {
        return this->head == this->tail;
    }

    // 查找语法错误，除法错误在运算中查找
    bool legal()
    {
        return true;

        // 括号匹配
        node *tmp = this->head->next, *ptmp = nullptr;
        int kuohao = 0;
        while (tmp != this->head)
        {
            if (tmp->type == 0 && tmp->optr == '(')
                kuohao++;
            else if (tmp->type == 0 && tmp->optr == ')')
            {
                kuohao--;
                if (kuohao < 0)
                    return false;
            }
            tmp = tmp->next;
        }
        if (kuohao != 0) return false;

        // 符号运用错误
        tmp = this->head->next;
        ptmp = this->head;
        while (tmp != this->head)
        {
            // 第一个如果是操作符，那么直接错误
            if (tmp == this->head->next)
            {
                if (tmp->type == 0 && tmp->optr != '(' && (tmp->optr != '-' || (tmp->next->optr != '(')))
                    // 第一个是操作符且不是左括号
                    return false;
                else
                {
                    // 第一个是数字
                    ptmp = tmp;
                    tmp = tmp->next;
                }
            }
            else if (tmp == this->tail)
            {
                if (tmp->type == 0 && tmp->optr != ')')
                    // 如果最后一个是操作符，且不是右括号，那么直接错误
                    return false;
                else
                {
                    ptmp = tmp;
                    tmp = tmp->next;
                }
            }
            else
            {
                /* 对于中间的节点按照类型进行判断
                // - 如果是数字，那么
                    数字的读入方式决定了数字本身不会出现语法错误，唯一可能的错误是多重括号包裹
                    若是非负数，那么以下情况错误
                        // - 前后紧邻数字，则错误
                        数字读入的时候不可能出现前后节点都是数字的情况
                        - 被完整的括号包裹，错误
                    负数后头不可能再出现数字节点，只可能出现操作符，可以交给操作符来判断
                    // - 若是负数，那么以下情况错误
                        // - 后面直接接着一个数字（前方不可能直接接上数字，这是造表规则决定的）
                - 如果是符号
                    - 非括号
                        - 前方必须是数字或右括号 )
                        - 后方必须是数字或左括号 (
                    - 括号
                        - 如果是左括号 (，如果前面是一个数字/右括号或者后面是一个非左括号的操作符，则错误
                        - 如果是右括号 )，如果后头是一个数字/左括号或者牵头是一个非右括号的操作符，则错误
                    // - 除号
                        // - 不为0，即后一个数字不为0（这是运算时错误，不在编译时解决）
                */
                if (tmp->type == 0)
                {
                    bool flag2 = false;
                    switch (tmp->optr)
                    {
                        case '(':
                            if (ptmp->type == 1 || (ptmp->type == 0 && ptmp->optr == ')') ||
                            (tmp->next->type == 0 && tmp->next->optr != '('))
                                return false;
                            break;
                        case ')':
                            if (tmp->next->type == 1 || (tmp->next->type == 0 && tmp->next->optr == '(') ||
                            (ptmp->type == 0 && ptmp->optr != ')'))
                                return false;
                            break;
                        case '^':
                            if (tmp->next->next == this->tail)
                                return false;
                            if ((tmp->next->type == 0 && tmp->next->optr == '-') &&
                            !(tmp->next->next->type == 0 && tmp->next->next->optr == '('))
                                return false;
                            if ((ptmp->type == 0 && ptmp->optr != ')') ||
                            (tmp->next->type == 0 && tmp->next->optr != '(' && tmp->next->optr != '-'))
                                return false;
                            break;
                        case '-':
                            if (ptmp->type == 0 && ptmp->optr == '^' &&
                            tmp->next->type == 0 && tmp->next->optr == '(')
                                flag2 = true;

                            if ((ptmp->type == 1 || (ptmp->type == 0 && ptmp->optr == ')')) &&
                            (tmp->next->type == 1 || (tmp->next->type == 0 && tmp->next->optr == ')')))
                                flag2 = true;

                            if (flag2 == false)
                                return false;
                            break;
                        default:
                            if ((ptmp->type == 0 && ptmp->optr != ')') ||
                            (tmp->next->type == 0 && tmp->next->optr != '('))
                                return false;
                    }
                }
                ptmp = tmp;
                tmp = tmp->next;
            }
        }

        // TODO 多余括号

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
};

#define N 500
void answer();
void makechain(List&, char*);
bool isOptr(char);
bool isNumb(char);
// 比较前后优先级，-1低，0相等，1高
short proceed(char, char);
// 返回优先级层次
int righteous(char);

int main(void)
{
    int T;
    cin >> T; getchar();
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
    /*
3
1+2-3/4*5/6%7^10^(11/12)-12+(1+2)--13
    */
    if (exprChain.legal() == false)
        cout << "error." << endl;
    else
    {
        stack<char> OPTR;
        stack<long> OPND;
    }

    exprChain.Destroy();
    return;
}

void makechain(List &cur, char *str)
{
    int ind = 0;
    bool isNum = false;
    while (str[ind] != '\n')
    {
        if (isOptr(str[ind]) == true)
        {
            if (str[ind] != '-')
                cur.push(0, str[ind++], -1);
            else
                if (isNumb(str[ind + 1]) == false || (isNumb(str[ind + 1]) == true && ind != 0 && (isNumb(str[ind - 1]) || str[ind - 1] == ')')))
                    cur.push(0, str[ind++], -1);
                else goto l1;
        }
        else
        {
            l1:
            long tmp = 0;
            long positive = str[ind] == '-' ? -1 : 1;
            if (positive == -1) ind++;
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

short proceed(char c1, char c2)
{
    return righteous(c1) >= righteous(c2);
}

int righteous(char c)
{
    switch (c)
    {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '%': return 2;
        case '^': return 3;
        case '(': return 4;
        case ')': return 0;
    }
}
