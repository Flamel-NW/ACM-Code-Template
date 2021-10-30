// HDU-1710
#include <cstdio>
const int MAXN = 1100;

using namespace std;

struct node
{
    int value;
    node * l;
    node * r;

    node(int value = 0, node * l = nullptr, node * r = nullptr) : value(value), l(l), r (r) { };
};

int pre[MAXN], in[MAXN], post[MAXN]; // 先序、中序、后序
int k;

void buildtree(int l, int r, int &t, node * & root) // 建树
{
    int flag = -1;
    for (int i = l; i <= r; i++) // 先序的第1个数是根，找到对应的中序的位置
    {
        if (in[i] == pre[t])
        {
            flag = i;
            break;
        }
    }
    if (flag == -1)
    {
        return; // 结束
    }

    root = new node(in[flag]); // 新建结点
    t++;
    if (flag > l)
    {
        buildtree(l, flag - 1, t, root->l);
    }
    if (flag < r)
    {
        buildtree(flag + 1, r, t, root->r);
    }
}

void preorder(node * root) // 求先序序列
{
    if (root != nullptr)
    {
        post[k++] = root->value; // 输出
        preorder(root->l);
        preorder(root->r);
    }
}

void inorder(node * root) // 求中序序列
{
    if (root != nullptr)
    {
        inorder(root->l);
        post[k++] = root->value; // 输出
        inorder(root->r);
    }
}

void postorder(node * root) // 求后序序列
{
    if (root != nullptr)
    {
        postorder(root->l);
        postorder(root->r);
        post[k++] = root->value; // 输出
    }
}

void remove_tree(node * root) // 释放空间
{
    if (root != nullptr)
    {
        remove_tree(root->l);
        remove_tree(root->r);
        delete root;
        root = nullptr;
    }
}

int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &pre[i]);
        }
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &in[i]);
        }

        node * root;
        int t = 1;
        buildtree(1, n, t, root);
        
        k = 1; // 记录结点个数
        postorder(root);
        for (int i = 1; i < k; i++)
        {
            printf("%d%c", post[i], i == k - 1 ? '\n' : ' '); // 卡行末空格的正确方式
                // 作为验证，这里可以用preorder()和inorder()检查先序和中序遍历
        }
        remove_tree(root);
    }

    return 0;
}
