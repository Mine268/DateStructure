#include <iostream>
#define N 1000
using namespace std;

/*
degree[][0] 入度
degree[][1] 出度
*/
int degree[N][2];
bool mark[N];

int main(void) {
    char tmp = '\0';
    while (tmp != '\n') {
        tmp = getchar();
        mark[tmp] = true;
        tmp = getchar();
    }

    int max = 0, min = 0;
    char x, y;
    tmp = '\0';
    while (tmp != '\n') {
        // x -> y
        scanf("<%c,%c>", &x, &y);
        tmp = getchar();
        degree[x][1]++;
        degree[y][0]++;
    }

    for (int i = 0; i < N; i++)
        if (mark[i] && degree[i][0] == 0) {
            if (min++ != 0) putchar(',');
            putchar(i);
        }
    putchar('\n');

    for (int i = 0; i < N; i++)
        if (mark[i] && degree[i][1] == 0) {
            if (max++ != 0) putchar(',');
            putchar(i);
        }
    putchar('\n');

    return 0;
}