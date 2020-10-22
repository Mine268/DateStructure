#include <iostream>
#include <stack>
using namespace std;
#define N 101

typedef struct
{
    int x, y;
} node;

bool mark[N][N];
int map[N][N];
stack<node> ds;

bool valid(node cur, int m, int n);
node nextPose(node cur, int i);
bool dfs(node cur, node endpos, int m, int n);

int main(void)
{
    int m, n;
    bool canpass = false;
    cin >> m >> n;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &map[j][i]);

    mark[0][0] = true;
    ds.push({0, 0});

    canpass = dfs({0, 0}, {m - 1, n - 1}, m, n);

    if (canpass == false)
        cout << "There is no solution!" << endl;
    else
    {
        stack<node> printStack;
        while (ds.empty() == false)
        {
            printStack.push(ds.top());
            ds.pop();
        }
        while (printStack.empty() == false)
        {
            cout << "<" << printStack.top().y + 1 << "," << printStack.top().x + 1 << "> ";
            printStack.pop();
        }
        cout << endl;
    }

    return 0;
}

bool dfs(node cur, node endpos, int m, int n)
{
    if (cur.x == endpos.x && cur.y == endpos.y)
        return true;
    else
    {
        bool flag = false;
        for (int i : {1, 2, 3, 4})
        {
            node nextpos = nextPose(cur, i);
            if (valid(nextpos, m, n) == true && mark[nextpos.x][nextpos.y] == false)
            {
                ds.push(nextpos);
                mark[nextpos.x][nextpos.y] = true;
                flag = dfs(nextpos, endpos, m, n);

                if (flag == true) break;
                else
                {
                    mark[nextpos.x][nextpos.y] = false;
                    ds.pop();
                }
            }
        }
        return flag;
    }
}

node nextPose(node cur, int i)
{
    switch (i)
    {
    case 1:
        return {cur.x, cur.y + 1};
        break;
    case 2:
        return {cur.x + 1, cur.y};
        break;
    case 3:
        return {cur.x, cur.y - 1};
        break;
    case 4:
        return {cur.x - 1, cur.y};
        break;
    }
}

bool valid(node cur, int m, int n)
{
    if (cur.x < 0 || cur.y < 0 || cur.x >= m || cur.y >= n)
        return false;
    if (map[cur.x][cur.y] == 1)
        return false;
    return true;
}
