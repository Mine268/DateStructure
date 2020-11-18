#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    int freq;
    Node *left, *right;

    Node(int v)
    {
        this->freq = v;
        this->left = this->right = nullptr;
    }

    static Node *getNode(int v) // not recommanded
    {
        Node *tmp;
        tmp = (Node*)malloc(sizeof(Node));
        tmp->freq = v;
        tmp->left = tmp->right = nullptr;
        return tmp;
    }

    int getWPL()
    {
        return this->getWPL(0);
    }

private:
    int getWPL(int dep)
    {
        if (this->right == nullptr && this->left == nullptr)
            return this->freq * dep;
        else
            return this->left->getWPL(dep + 1) + this->right->getWPL(dep + 1);
    }
};

class Node_Compare
{
public:
    bool operator () (Node* &a, Node* &b)
    {
        return a->freq > b->freq;
    }
};

int main(void)
{
    priority_queue<Node*, vector<Node*>, Node_Compare> Q;
    Node *r = nullptr, *subr = nullptr;
    long n;
    cin >> n;
    while (n-- > 0)
    {
        int tmp;
        cin >> tmp;
        Q.push(Node::getNode(tmp));
    }

    while (Q.size() > 1)
    {
        r = Q.top();
        Q.pop();
        subr = Q.top();
        Q.pop();

        Node *tmp = Node::getNode(r->freq + subr->freq);
        tmp->right = r;
        tmp->left = subr;
        Q.push(tmp);
    }
    r = Q.top();
    Q.pop();

    cout << "WPL=" << r->getWPL() << endl;

    return 0;
}
