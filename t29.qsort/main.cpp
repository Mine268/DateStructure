#include <cstring>
#include <iostream>
#include <vector>
#define N 1000
#define K 100
using namespace std;

int num[N] = {0}, cnt = 0;
vector<int> medians;

void Quick_Sort(int[], int, int);
int median(int, int, int);
int quick(int, int);
void Qsort(int, int);

int main(void) {
    char str[K] = {0};
    for (int i = 0; true; i++) {
        scanf("%s", str);
        if (str[0] == '#') break;
        num[i] = atoi(str);
        cnt++;
    }

    Qsort(0, cnt - 1);

    cout << "After Sorting:\n";
    for (int i = 0; i < cnt; i++) cout << num[i] << ' ';
    cout << "\nMedian3 Value:\n" ;
    if (medians.empty())
        cout << "none\n";
    else {
        for (int x : medians)
            cout << x << ' ';
        cout << endl;
    }
    return 0;
}

void Quick_Sort(int b[], int start, int end) {
	if (start >= end) return;
	else {
        int i = start, j = start;
        while (j < end) {
            if (b[j] >= b[end]) j++;
            else swap(b[i++], b[j++]);
        }
        swap(b[end], b[i]);
        Quick_Sort(b, start, i - 1);
        Quick_Sort(b, i + 1, end);
	}
}

int median(int a, int b, int c) {
    if (num[a] > num[c]) swap(num[a], num[c]);
    if (num[a] > num[b]) swap(num[a], num[b]);
    if (num[c] > num[b]) swap(num[c], num[b]);
    swap(num[c], num[b - 1]);

    medians.push_back(num[b - 1]);
    return num[b - 1];
}

int quick(int left, int right) {
    if (right - left < 5) {
        Quick_Sort(num, left, right);
        return -1;
    } else {
        int base = median(left, right, (left + right) / 2);
        int i = left, j = right - 1;
        while (i < j) {
            while (i < j && num[++i] < base) ;
            while (i < j && num[--j] > base) ;
            swap(num[i], num[j]);
        }
        swap(num[i], num[right - 1]);
        return i;
    }
}

void Qsort(int left, int right) {
    if (left < right) {
        int middle = quick(left, right);
        if (middle != -1) {
            Qsort(left, middle - 1);
            Qsort(middle + 1, right);
        }
    }
}
