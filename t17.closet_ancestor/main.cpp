#include <iostream>
#include <cstring>
#define N 1050
#define ull unsigned long long
using namespace std;

int main(void)
{
    int n, tree[N], mark[N], i, j;
    memset(tree, 0, sizeof(int) * N);
    memset(mark, 0, sizeof(int) * N);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> tree[i];
    cin >> i >> j;

    i--; j--;
    if (tree[0] == 0)
        printf("ERROR: T[%d] is NULL\n", i + 1);
    else if (tree[i] == 0)
        printf("ERROR: T[%d] is NULL\n", i + 1);
    else if (tree[j] == 0)
        printf("ERROR: T[%d] is NULL\n", j + 1);
    else
    {
        while (i > 0)
        {
            mark[i] = -1;
            i = (i - 1) >> 1;
        }
        while (j > 0 && mark[j] != -1)
        {
            mark[j] = -1;
            j = (j - 1) >> 1;
        }
        printf("%d %d\n", j + 1, tree[j]);
    }

    return 0;
}
/*
15
4 3 5 1 0 9 7 0 2 0 0 10 0 6 8
*/