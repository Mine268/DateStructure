#include <iostream>
#include <string>
using namespace std;

#define OK 1
#define FAIL 0

typedef int Status;
typedef enum
{
    ATOM,
    LIST
} ElemTag;
typedef char AtomType;
typedef struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType atom;
        struct
        {
            struct GLNode *hp, *tp;
        } ptr;
    };
} * GList, GLNode;

Status CreateGList(GList &L, string S); // 根据字符串 S 表示的广义表内容建立广义表数据结构；
GList GetHead(GList L);                 // 取表头运算
GList GetTail(GList L);                 // 取表尾运算
void DestroyGList(GList &L);            // 销毁广义表 L
void PrintGList(GList L);               // 显示广义表 L 内容
void _PrintGList(GList L);              // 显示广义表 L 内容
Status sever(string &str, string &hstr);

int main(void)
{
    GList list;
    string str;
    char choic;
    cin >> str;
    getchar();

    CreateGList(list, str);
    printf("generic list: ");
    PrintGList(list);

    while (list != nullptr && list->ptr.hp != nullptr && list->tag != ATOM)
    {
        choic = getchar();
        getchar();
        if (choic == '1')
        {
            DestroyGList(list->ptr.tp);
            list = list->ptr.hp;
            printf("destroy tail\nfree list node\ngeneric list: ");
        }
        else
        {
            GList tmp = list;
            list = list->ptr.tp;
            DestroyGList(tmp->ptr.hp);
            printf("free head node\nfree list node\ngeneric list: ");
        }
        PrintGList(list);
    }

    return 0;
}

void PrintGList(GList L)
{
    if (L == nullptr) printf("()");
    else if (L->tag == ATOM)
        putchar(L->atom);
    else
    {
        putchar('(');
        _PrintGList(L);
        putchar(')');
    }
    putchar('\n');
}

// (a,(b,(c,d)),e,f)
void _PrintGList(GList L)
{
    if (L == nullptr || L->ptr.hp == nullptr)
        return;
    if (L->tag == ATOM)
    {
        putchar(L->atom);
        return;
    }
    else
    {
        while (L != nullptr)
        {
            if (L->ptr.hp != nullptr && L->ptr.hp->tag == ATOM)
                _PrintGList(L->ptr.hp);
            else
            {
                putchar('(');
                _PrintGList(L->ptr.hp);
                putchar(')');
            }
            L = L->ptr.tp;
            if (L != nullptr)
                putchar(',');
        }
    }
}

void DestroyGList(GList &L)
{
    if (L == nullptr)
        return;
    if (L->tag == ATOM)
        free(L);
    else
    {
        DestroyGList(L->ptr.hp);
        DestroyGList(L->ptr.tp);
        free(L);
        L = nullptr;
    }
    return;
}

Status CreateGList(GList &L, string S)
{
    if (S.empty() == true)
        L = nullptr;
    else
    {
        L = (GList)malloc(sizeof(GLNode));
        if (L == nullptr)
            return FAIL;
        if (S.length() == 1)
        {
            L->tag = ATOM;
            L->atom = S.c_str()[0];
        }
        else
        {
            L->tag = LIST;
            GList p = L, q;
            // sub 为脱去外层括号的 S
            // hsub 为第一个表项
            string sub, hsub;
            sub = S.substr(1, S.size() - 2);

            do
            {
                sever(sub, hsub);
                // cout << hsub << ' ' << sub << endl;
                CreateGList(p->ptr.hp, hsub); // 建立表头
                q = p;
                if (sub.empty() == false)
                {
                    p = (GLNode *)malloc(sizeof(GLNode));
                    if (p == nullptr)
                        return FAIL;
                    p->tag = LIST;
                    q->ptr.tp = p;
                }
            } while (sub.empty() == false);
            q->ptr.tp = nullptr;
        }
    }
    return OK;
}

Status sever(string &str, string &hstr)
{
    int n = str.length(), i = 0, k = 0;
    char ch;
    do
    {
        ch = str.substr(i, 1).c_str()[0];
        i++;
        if (ch == '(')
            k++;
        else if (ch == ')')
            k--;
    } while (i < n && (ch != ',' || k != 0));
    if (i < n)
    {
        hstr = str.substr(0, i - 1);
        str = str.substr(i, n - i);
    }
    else
    {
        char tmp[1000];
        str.copy(tmp, str.length(), 0);
        tmp[str.length()] = 0;
        str.clear();
        hstr.assign(tmp);
    }
    return OK;
}

GList GetHead(GList L)
{
    if (L->tag == ATOM)
        return nullptr;
    else
        return L->ptr.hp;
}

GList GetTail(GList L)
{
    if (L->tag == ATOM)
        return nullptr;
    else
        return L->ptr.tp;
}