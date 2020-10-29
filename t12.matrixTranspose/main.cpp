#include <iostream>
using namespace std;

#define MAXSIZE 125
typedef int ElemType;
typedef struct
{
    int i, j;
    ElemType e;
} Triple;
typedef struct
{
    Triple data[MAXSIZE + 1];
    int mu, nu, tu;
    // row, col, non-zero
}TSMatrix;

void IniMatrix(TSMatrix &mat, int mu, int nu, int tu);
void MatrixTranspose(TSMatrix &T, TSMatrix S);

int main(void)
{
    int m, n, t;
    TSMatrix S, T;

    cin >> m >> n >> t;
    IniMatrix(S, m, n, t);
    IniMatrix(T, n, m, t);

    for (int i = 1; i <= t; i++)
        scanf("%d%d%d", &S.data[i].i, &S.data[i].j, &S.data[i].e);

    MatrixTranspose(T, S);

    return 0;
}

void MatrixTranspose(TSMatrix &T, TSMatrix S)
{
    int num[MAXSIZE] = {0}, cpot[MAXSIZE] = {0};
    for (int col = 1; col <= S.nu; col++)
        num[col] = 0;
    for (int t = 1; t <= S.tu; t++)
        ++num[S.data[t].j];
    cpot[1] = 1;
    for (int col = 2; col <= S.nu; col++)
        cpot[col] = cpot[col - 1] + num[col - 1];

    printf("num:");
    for (int i = 1; i <= S.nu; i++)
        printf("%d,", num[i]);
    printf("\ncpot:");
    for (int i = 1; i <= S.nu; i++)
        printf("%d,", cpot[i]);

    for (int p = 1; p <= S.tu; p++)
    {
        int col = S.data[p].j, q = cpot[col];
        T.data[q].i = S.data[p].j;
        T.data[q].j = S.data[p].i;
        T.data[q].e = S.data[p].e;
        cpot[col]++;
    }

    putchar('\n');
    for (int i = 1; i <= T.tu; i++)
        printf("%d,%d,%d\n", T.data[i].i, T.data[i].j, T.data[i].e);
}

void IniMatrix(TSMatrix &mat, int mu, int nu, int tu)
{
    mat.mu = mu;
    mat.nu = nu;
    mat.tu = tu;
}
