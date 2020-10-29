#include <iostream>
#include <cstring>
#define MAXSIZE 200
#define MAXRC 200

typedef int ElemType;

typedef struct
{
    int i, j;
    ElemType e;
} Triple;
typedef struct
{
    Triple data[MAXSIZE + 1];
    int rpos[MAXRC + 1];
    int mu, nu, tu;
} RLSMatrix;

using namespace std;

void iniMat(RLSMatrix &M);
void MatMulti(RLSMatrix M, RLSMatrix N, RLSMatrix &Q);

int main(void)
{
    RLSMatrix M1, M2, Q;
    iniMat(M1);
    iniMat(M2);
    MatMulti(M1, M2, Q);

    printf("%d\n%d\n%d\n", Q.mu, Q.nu, Q.tu);
    for (int i = 1; i <= Q.tu; i++)
        printf("%d,%d,%d\n", Q.data[i].i, Q.data[i].j, Q.data[i].e);

    return 0;
}

void MatMulti(RLSMatrix M, RLSMatrix N, RLSMatrix &Q)
{
    Q.mu = M.mu;
    Q.nu = N.nu;
    Q.tu = 0;
    int ctemp[MAXRC + 1] = {0};
    if (M.tu * N.tu == 0)
        return;
    else
    {
        for (int arow = 1; arow <= M.mu; arow++)
        {
            memset(ctemp, 0, sizeof(int) * (MAXRC + 1));
            Q.rpos[arow] = Q.tu + 1;

            int tp = 0;
            if (arow < M.mu)
                tp = M.rpos[arow + 1];
            else
                tp = M.tu + 1;

            for (int p = M.rpos[arow]; p < tp; p++)
            {
                int brow = M.data[p].j;
                int t = 0;
                if (brow < N.mu)
                    t = N.rpos[brow + 1];
                else
                    t = N.tu + 1;

                for (int q = N.rpos[brow]; q < t; q++)
                {
                    int ccol = N.data[q].j;
                    ctemp[ccol] += M.data[p].e * N.data[q].e;
                }
            }

            for (int ccol = 1; ccol <= Q.nu; ccol++)
                if (ctemp[ccol] != 0)
                    Q.data[++Q.tu] = {arow, ccol, ctemp[ccol]};
        }
    }
    return;
}

void iniMat(RLSMatrix &M)
{
    scanf("%d%d%d", &M.mu, &M.nu, &M.tu);
    for (int i = 1; i <= M.tu; i++)
        scanf("%d%d%d", &M.data[i].i, &M.data[i].j, &M.data[i].e);

    int num[MAXSIZE + 1] = {0};
    for (int row = 1; row <= M.mu; row++)
        num[row] = 0;
    for (int t = 1; t <= M.tu; t++)
        ++num[M.data[t].i];
    M.rpos[1] = 1;
    for (int row = 2; row <= M.mu; row++)
        M.rpos[row] = M.rpos[row - 1] + num[row - 1];

    return;
}
