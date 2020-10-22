#include <iostream>
#include <cstring>
using namespace std;

class polyn
{
private:
    typedef struct node
    {
        // 分别表示系数与指数
        long long coef, expn;
        struct node *next, *prev;
    } node;
    node *head;
    node *tail;

    // 快速创建节点
    static node *createNode(long long coef, long long expn)
    {
        node *tmp = (node *)malloc(sizeof(node));
        tmp->coef = coef;
        tmp->expn = expn;
        tmp->next = nullptr;
        tmp->prev = nullptr;
        return tmp;
    }

    // 返回头指针（非表头）
    node *getFirst()
    {
        return this->head->next;
    }

    // 返回表头
    node *getHead()
    {
        return this->head;
    }

public:
    // 构造函数
    polyn()
    {
        this->head = (node *)malloc(sizeof(node));
        this->head->next = nullptr;
        this->head->prev = nullptr;
        this->tail = head;
    }

    // 析构函数
    ~polyn()
    {
        node *ind = this->head, *pnd = ind;
        while (ind != nullptr)
        {
            ind = ind->next;
            free(pnd);
            pnd = ind;
        }
        this->head->next = nullptr;
    }

    // 追加节点到末尾
    void addNode(node *val)
    {
        this->tail->next = val;
        val->prev = this->tail;
        this->tail = val;
        return;
    }
    void addNode(long long coef, long long expn)
    {
        node *val = polyn::createNode(coef, expn);
        this->addNode(val);
        return;
    }

    // 输出多项式
    void printString()
    {
        node *ind = this->head->next;
        if (ind == nullptr)
        {
            cout << "<0,0>" << endl;
            return;
        }
        while (ind != nullptr)
        {
            printf("<%lld,%lld>", ind->coef, ind->expn);
            if (ind->next != nullptr)
                putchar(',');
            else
                putchar('\n');
            ind = ind->next;
        }
        return;
    }

    // 多项式相加，加到自己身上
    void addPolyn(polyn p1)
    {
        node *h1 = this->getFirst(), *ph1 = this->getHead(), *h2 = p1.getFirst();
        while (h1 != nullptr && h2 != nullptr)
        {
            if (h1->expn > h2->expn) // 如果此时被加入的单项式次数偏小
            {
                node *tmp = polyn::createNode(h2->coef, h2->expn);
                tmp->next = h1;
                tmp->prev = h1->prev;
                h1->prev->next = tmp;
                h1->prev = tmp;

                h2 = h2->next;
                ph1 = h1->prev;
            }
            else if (h1->expn < h2->expn)
            { // 如果此时被加入的单项式次数偏大
                h1 = h1->next;
                ph1 = ph1->next;
            }
            else
            { // 如果此时被加入的单项式次数相同
                long long coefSum = h1->coef + h2->coef;
                if (coefSum != 0)
                {   // 系数之和不为0，系数相加
                    h1->coef = coefSum;
                    h1 = h1->next;
                    h2 = h2->next;
                }
                else
                {   // 系数之和为0，节点删除
                    node *tmp = h1;
                    if (h1->next != nullptr)
                    {   // 如果当前节点不是最后一个
                        h1->prev->next = h1->next;
                        h1->next->prev = h1->prev;
                        h1 = h1->next;
                        ph1 = ph1->next;
                        h2 = h2->next;
                    } else {
                        // 如果当前节点是最后一个
                        h1->prev->next = h1->next;
                        h1 = h1->next;
                        h2 = h2->next;
                    }
                    free(tmp);
                }
            }
        }

        // 将剩余节点接上
        while (h2 != nullptr)
        {
            node *tmp = polyn::createNode(h2->coef, h2->expn);
            ph1->next = tmp;
            tmp->prev = ph1;
            ph1 = ph1->next;
            h2 = h2->next;
        }

        return;
    }
};

int main(int n, char **args)
{
    int flag;
    cin >> flag;

    if (flag == 0) return 0;
    else
    {
        polyn p[3];
        long long length, coef, expn;

        for (size_t i = 0; i < 3; i++)
        {
            cin >> length;
            for (long long j = 0; j < length; j++)
            {
                scanf("%lld %lld", &coef, &expn);
                p[i].addNode(coef, expn);
            }
        }

        p[0].printString();
        p[1].printString();
        p[2].printString();

        p[0].addPolyn(p[1]);
        p[0].printString();

        p[0].addPolyn(p[2]);
        p[0].printString();
    }

    return 0;
}
