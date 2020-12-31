#include <iostream>
#include <queue>
#include <cstring>
#define N 100
using namespace std;

int map[N][N];
bool mark[N];
queue<int> q;

int main(void) {
    int n = 0;
    char tmp = '\0';

    while (tmp != '\n') {
        tmp = getchar();
        map[0][n++] = tmp == '0' ? 0 : 1;
        tmp = getchar();
    }

    for (int i = 1; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &map[i][j]);

    for (int m = 0; m < n; m++) {
        memset(mark, 0, sizeof(bool) * N);
        q.push(m);
        while (!q.empty()) {
            int tmp = q.front();
            q.pop();
            for (int i = 0; i < n; i++)
                if (!mark[i] && map[tmp][i] == 1) {
                    map[m][i] = 1;
                    mark[i] = true;
                    q.push(i);
                }
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            printf("%d", map[i][j]);
            if (j < n - 1) putchar(' ');
            else putchar('\n');
        }

    return 0;
}
