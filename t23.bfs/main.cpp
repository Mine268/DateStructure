#include <iostream>
#include <queue>
#define N 100
using namespace std;

bool map[N][N], mark[N];
queue<int> q;

int main(void) {
    freopen("./test.in", "r", stdin);
    freopen("./test.out", "w", stdout);

    int n = 0, a = 0, b = 0;
    char list[N], c;
    while ((c = getchar()) != '*') {
        list[n++] = c;
        getchar();
    }

    scanf("%d,%d", &a, &b);
    while (a != -1 && b != -1) {
        map[a][b] = true;
        map[b][a] = true;
        scanf("%d,%d", &a, &b);
    }

    cout << "the ALGraph is" << endl;
    for (int i = 0; i < n; i++) {
        cout << list[i];
        for (int j = n - 1; j >= 0; j--)
            if (map[j][i])
                cout << ' ' << j;
        cout << endl;
    }

    cout << "the Breadth-First-Seacrh list:";
    for (int j = 0; j < n; j++) {
        if (mark[j] == false) {
            mark[j] = true;
            q.push(j);
            while (q.empty() == false) {
                int now = q.front();
                q.pop();
                for (int i = n - 1; i >= 0; i--)
                    if (map[i][now] == true && mark[i] == false) {
                        q.push(i);
                        mark[i] = true;
                    }
                cout << list[now];
            }
        }
    }
    cout << endl;

    return 0;
}