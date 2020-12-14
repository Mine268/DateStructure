#include <iostream>
#define N 1000
#define PARENT(x) ((x - 1) >> 1)
#define LEFT(x) (((x) << 1) + 1)
#define RIGHT(x) (((x) << 1) + 2)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
using namespace std;

typedef struct heap {
    int *data;
    int size;

    heap() {
        this->data = (int *)malloc(sizeof(int) * N);
        this->size = 0;
    }

    void print() {
        for (int i = 0; i < this->size; i++) printf("%d ", this->data[i]);
        putchar('\n');
    }
} heap;

void buildheap(heap *);
void buildheap_re(heap *, int);
void insert(heap *, int);
int extract(heap *);

int main(void) {
    heap h;
    int m, n;
    cin >> m;
    h.size = m;
    for (int i = 0; i < m; i++) {
        cin >> n;
        h.data[i] = n;
    }
    buildheap(&h);
    h.print();
    extract(&h);
    h.print();
    extract(&h);
    h.print();
    return 0;
}

void buildheap(heap *h) {
    int n = PARENT(h->size - 1);
    while (n >= 0)
        buildheap_re(h, n--);
}

void buildheap_re(heap *h, int k) {
    if (k > PARENT(h->size - 1)) return;
    else if (RIGHT(k) >= h->size && h->data[LEFT(k)] > h->data[k]) {
        int tmp = h->data[k];
        h->data[k] = h->data[LEFT(k)];
        h->data[LEFT(k)] = tmp;
    } else if (RIGHT(k) < h->size) {
        int maxval = MAX(h->data[LEFT(k)], h->data[RIGHT(k)]);
        int maxind = (maxval == h->data[LEFT(k)]) ? LEFT(k) : RIGHT(k);
        if (maxval > h->data[k]) {
            int tmp = h->data[k];
            h->data[k] = h->data[maxind];
            h->data[maxind] = tmp;
            buildheap_re(h, maxind);
        }
    }
    return;
}

int extract(heap *h) {
    int res = h->data[0], now = 0;
    h->data[0] = h->data[h->size-- - 1];
    while ((RIGHT(now) < h->size &&
            h->data[now] < MAX(h->data[LEFT(now)], h->data[RIGHT(now)])) ||
           (LEFT(now) < h->size && h->data[now] < h->data[LEFT(now)])) {
        int swapind = LEFT(now);
        if (RIGHT(now) < h->size)
            if (h->data[LEFT(now)] < h->data[RIGHT(now)]) swapind = RIGHT(now);
        int tmp = h->data[swapind];
        h->data[swapind] = h->data[now];
        h->data[now] = tmp;
        now = swapind;
    }
    return res;
}

void insert(heap *h, int v) {
    int now = h->size;
    h->data[h->size++] = v;
    while (now && h->data[now] > h->data[PARENT(now)]) {
        int tmp = h->data[now];
        h->data[now] = h->data[PARENT(now)];
        h->data[PARENT(now)] = tmp;
        now = PARENT(now);
    }
}
