#include <iostream>

using namespace std;

class mystack
{
private:
    typedef struct node
    {
        int value;
        struct node *next;
    } node;

    static node *makenode(int value)
    {
        node *ret = (node *)malloc(sizeof(node));
        ret->value = value;
        ret->next = nullptr;
        return ret;
    }

    node *head;

public:
    mystack()
    {
        this->head = mystack::makenode(-1);
    }

    void push(int value)
    {
        node *into = mystack::makenode(value);
        into->next = this->head->next;
        this->head->next = into;
    }

    void pop()
    {
        node *todel = this->head->next;
        this->head->next = this->head->next->next;
        free(todel);
    }

    int top()
    {
        return this->head->next->value;
    }

    bool empty()
    {
        if (this->head->next == nullptr)
            return true;
        else
            return false;
    }
};

void judge(int);

int main(void)
{
    int a, b;
    scanf("%d%d", &a, &b);
    while (a != 0 && b != 0)
    {
        while (b-- > 0)
            judge(a);
        scanf("%d%d", &a, &b);
        if (a != 0 && b != 0)
            putchar('\n');
    }
    return 0;
}

void judge(int n)
{
    int cur, topline = 1;
    mystack stk;
    stk.push(topline - 1);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &cur);
        if (cur < stk.top())
        {
            cout << "No" << endl;
            while (i++ < n - 1)
                scanf("%*d");
            return;
        }
        else if (cur == stk.top())
            stk.pop();
        else
        {
            while (topline < n + 1 && topline - 1 != cur)
            {
                stk.push(topline);
                topline++;
            }
            if (topline == n + 1 && topline - 1 != cur)
            {
                cout << "No" << endl;
                while (i++ < n - 1)
                    scanf("%*d");
                return;
            }
            else
                stk.pop();
        }
    }
    cout << "Yes" << endl;
}
