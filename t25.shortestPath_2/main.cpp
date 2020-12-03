#include <iostream>
#include <climits>
#include <cstring>
#define N 200
using namespace std;

int graph[N][N], buffer;

int main(void) {
    freopen("./test.in", "r", stdin);
    freopen("./test.out", "w", stdout);

    int n, e, start, dis[N];  // 源点到每一个点的最短路径
    bool mark[N];  // 该点的最短路径是否求出
    char r;
    buffer = scanf("%d,%d,%c", &n, &e, &r); getchar();
    start = r - 'a';
    memset(graph, INT_MAX, sizeof(int) * N * N);
    memset(dis, INT_MAX, sizeof(int) * N);
    memset(mark, false, sizeof(bool) * N);
    dis[start] = 0;
    mark[start] = true;

    for (int i = 0; i < e; i++) {
        char f, t;
        int c;
        buffer = scanf("<%c,%c,%d>", &f, &t, &c); getchar();
        graph[t - 'a'][f - 'a'] = c;
    }

    for (int count = 1; count < n; count++) {
        int shrtNode = INT_MAX, shrtFrom = -1, shrtLen = INT_MAX;
        for (int i = 0; i < n; i++)
            if (!mark[i])
                for (int j = 0; j < n; j++)
                    if (mark[j] && graph[i][j] != -1 && graph[i][j] < shrtLen) {
                        shrtNode = i;
                        shrtFrom = j;
                        shrtLen = graph[i][j];
                    }
        mark[shrtNode] = true;
        dis[shrtNode] = shrtLen + dis[shrtFrom];
    }

    for (int i = 0; i < n; i++)
            printf("%c:%d\n", i + 'a', dis[i]);

    return 0;
}
