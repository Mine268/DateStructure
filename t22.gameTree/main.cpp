#include <climits>
#include <cstring>
#include <iostream>
#include <queue>
#define N 100
#define M 1000
#define ISLEAF(x) ((x)->childrenCount == 0)
#define MAX(x,y) (((x)>(y))?(x):(y))
using namespace std;

typedef struct node {
    char value;
    int depth;
    int height;
    int childrenCount;
    node *children[N];
} node;

node *make(char, int);
node *buildTree(char[], int, int, int);  // 字符左右下标，深度
node *searchNode(node *, char);          // 搜寻到符合内容的子节点
bool canWin(node *, int);   // 判断如果电脑下在这一步能不能赢
char getUserInput(node *);  // 获得用户的输入（包含player输出）
char getChar();
void buildTopHeight(node *r);  // 获得顶端节点的高度
void DFSPrint(node *);
void destroyTree(node *);

int main(void) {
    freopen("./test.in", "r", stdin);
    freopen("./test.out", "w", stdout);
    char str[M], choice;  // 对局中玩家的选择
    int len = 0;          // 字符串的长度
    bool con = true;      // 指示是否继续下一盘
    node *root, *now;     // now用来指示对局中当前的局势（节点）
    queue<node *> winner, unsure;  // 分别代表能够稳赢的和不确定能够稳赢的

    cin >> str;
    getchar();
    len = strlen(str);
    root = buildTree(str, 0, len - 1, 0);
    buildTopHeight(root);

    DFSPrint(root);

    while (con) {
        now = root;
        bool indicator = true;  // false表示当前下完棋的是电脑，否则是玩家
        // 谁先来
        cout << "Who play first(0:computer;1:player)?" << endl;
        if ((choice = getChar()) == '1') {
            choice = getUserInput(now);
            now = searchNode(now, choice);
        }

        while (!ISLEAF(now)) {
            if (indicator) {
                for (int i = 0; i < now->childrenCount; i++)
                    if (canWin(now->children[i], 0))
                        winner.push(now->children[i]);
                    else
                        unsure.push(now->children[i]);

                node *pcChoice = nullptr;
                int pcHeight;
                if (winner.empty() == false) {
                    pcHeight = INT_MAX;
                    while (winner.empty() == false) {
                        node *tmp = winner.front();
                        winner.pop();
                        if (tmp->height < pcHeight) {
                            pcHeight = tmp->height;
                            pcChoice = tmp;
                        }
                    }
                } else {
                    pcHeight = INT_MIN;
                    while (unsure.empty() == false) {
                        node *tmp = unsure.front();
                        unsure.pop();
                        if (tmp->height > pcHeight) {
                            pcHeight = tmp->height;
                            pcChoice = tmp;
                        }
                    }
                }
                cout << "computer:" << pcChoice->value << endl;
                now = pcChoice;
            } else {
                choice = getUserInput(now);
                now = searchNode(now, choice);
            }
            indicator = !indicator;
        }

        if (!indicator)
            cout << "Sorry,you lost." << endl;
        else
            cout << "Congratulate,you win." << endl;

        while (winner.empty() == false) winner.pop();
        while (unsure.empty() == false) unsure.pop();

        // 游戏结束，询问是否还要再来
        cout << "Continue(y/n)?" << endl;
        if ((choice = getChar()) == 'n') con = false;
    }

    destroyTree(root);
    return 0;
}

void buildTopHeight(node *r) {
    if (ISLEAF(r))
        r->height = 0;
    else {
        int res = INT_MIN;
        for (int i = 0; i < r->childrenCount; i++) {
            buildTopHeight(r->children[i]);
            res = MAX(res, r->children[i]->height);
        }
        r->height = res + 1;
    }
    return;
}

node *searchNode(node *r, char c) {
    for (int i = 0; i < r->childrenCount; i++)
        if (r->children[i]->value == c) return r->children[i];
    return nullptr;
}

char getUserInput(node *r) {
s:
    cout << "player:" << endl;
    char c = getchar();
    getchar();
    node *tmp = searchNode(r, c);
    if (!tmp) {
        cout << "illegal move." << endl;
        goto s;
    }
    return c;
}

char getChar() {
    char c = getchar();
    getchar();
    return c;
}

bool canWin(node *r, int d) {
    bool res;
    if (d % 2 == 0) {
        res = true;
        for (int i = 0; i < r->childrenCount; i++)
            if (ISLEAF(r->children[i]))
                res = res && false;
            else
                res = res && canWin(r->children[i], (d + 1) % 2);
    } else {
        res = true;
        for (int i = 0; i < r->childrenCount; i++)
            if (ISLEAF(r->children[i]))
                res = res && true;
            else
                res = res && canWin(r->children[i], (d + 1) % 2);
    }
    return res;
}

void destroyTree(node *r) {
    if (r == nullptr)
        return;
    else {
        for (int i = 0; i < r->childrenCount; i++) destroyTree(r->children[i]);
        free(r);
    }
}

void DFSPrint(node *r) {
    if (r == nullptr)
        return;
    else {
        putchar(r->value);
        putchar('\n');
        for (int i = 0; i < r->childrenCount; i++) DFSPrint(r->children[i]);
    }
}

node *buildTree(char str[], int m, int n, int dep) {
    if (m == n - 1)  // ()
        return nullptr;
    else if (m == n - 2)  // (a)
        return make(str[m + 1], dep);
    else {  // (a,(b,(c),(d)),(e,(f)),(g))
        node *sr = make(str[m + 1], dep);
        int i = m + 3, j = m + 3;
        while (i < n) {
            int count = 0;
            do {
                if (str[j] == '(')
                    count++;
                else if (str[j] == ')')
                    count--;
                j++;
            } while (count != 0);
            node *tmp = buildTree(str, i, j - 1, dep + 1);
            if (tmp) sr->children[sr->childrenCount++] = tmp;
            j++;
            i = j;
        }
        return sr;
    }
}

node *make(char c, int d) {
    node *tmp = (node *)malloc(sizeof(node));
    tmp->value = c;
    tmp->childrenCount = 0;
    tmp->depth = d;
    tmp->height = 0;
    return tmp;
}