#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define N 4000
using namespace std;

typedef struct edge {
    int id, cost;
    inline bool operator<(const edge &a) const { return cost > a.cost; }
} edge;

vector<edge> edges[N];

bool connectedGraph(vector<edge>[], int);
long MST_Cost(vector<edge>[], int);

int main(void) {
    freopen("./test.in", "r", stdin);
    freopen("./test.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int f, t, c;
        cin >> f >> t >> c;
        edges[f].push_back({t, c});
        edges[t].push_back({f, c});
    }

    if (!connectedGraph(edges, n))
        cout << -1 << endl;
    else
        cout << MST_Cost(edges, n) << endl;

    return 0;
}

long MST_Cost(vector<edge> e[], int sum) {
    long cost = 0;
    bool *mark = (bool *)malloc(sizeof(bool) * N);
    memset(mark, 0, sizeof(bool) * N);
    priority_queue<edge> qe;

    mark[1] = true;
    for (int i = 0; i < e[1].size(); i++) qe.push(e[1][i]);
    while (sum > 1) {
        edge tmp = qe.top();
        qe.pop();
        if (mark[tmp.id] == true)
            continue;
        else {
            sum--;
            mark[tmp.id] = true;
            cost += tmp.cost;
            for (int i = 0; i < e[tmp.id].size(); i++)
                if (mark[e[tmp.id][i].id] == false)
                    qe.push(e[tmp.id][i]);
        }
    }

    free(mark);
    return cost;
}

bool connectedGraph(vector<edge> e[], int sum) {
    queue<int> q;
    bool *mark = (bool *)malloc(sizeof(bool) * N);
    memset(mark, 0, sizeof(bool) * N);

    mark[1] = true;
    q.push(1);
    while (q.empty() == false) {
        int now = q.front();
        q.pop();
        for (int j = 0; j < e[now].size(); j++) {
            int nxt = e[now][j].id;
            if (mark[nxt] == false) {
                mark[nxt] = true;
                q.push(nxt);
                sum--;
            }
        }
    }

    free(mark);
    return sum <= 1 ? true : false;
}