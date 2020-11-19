#include <iostream>
#include <cstdio>
#define N 10000
using namespace std;

typedef struct node
{
    bool tag;
    struct node *left, *right;
} node;

int buffer;
node *make();
bool judge(char[], node*);

int main(void)
{
    // freopen("./test.in", "r", stdin);
    // freopen("./test.out", "w", stdout);

    long n;
    char tmp[N];
    bool flag = true;
    node *root = make();
    cin >> n;
    while (n-- > 0 && flag)
    {
        cin >> tmp;
        getchar();
        if (!judge(tmp, root))
            flag = false;
    }

    if (flag)
        cout << "YES" << endl;
    else
        cout << tmp << endl;
    return 0;
}

bool judge(char str[], node *r)
{
    int i = 0;
    bool flag1 = true, flag2 = false;
    while (str[i] != '\0')
    {
        if (str[i] == '0')
        {
            if (r->left == nullptr)
            {
                r->left = make();
                flag2 = true;
                if (r->tag == true)
                    flag1 = false;
            }
            r = r->left;
        }
        else
        {
            if (r->right == nullptr)
            {
                r->right = make();
                flag2 = true;
                if (r->tag == true)
                    flag1 = false;
            }
            r = r->right;
        }
        i++;
    }
    r->tag = true;
    if (flag2 == false)
        return false;
    return flag1;
}

node *make()
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->tag = false;
    tmp->right = tmp->left =nullptr;
    return tmp;
}
