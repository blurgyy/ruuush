#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 50010
using namespace std;

int n, m;
bool hotel[maxn];
bool op;
struct segTree
{
    int left, right;
    bool occupied, lazy;
    void update(bool upd)
    {
        occupied = upd;
        lazy = upd;
    }
}Tree[4*maxn];

void pushUp(int index)
{
    Tree[index].occupied = Tree[index<<1].occupied && Tree[index<<1|1].occupied;
}

void pushDown(int index)
{
    bool upd = Tree[index].lazy;
    if(upd != -1)
    {
        Tree[index<<1].update(upd);
        Tree[index<<1].update(upd);
        Tree[index].lazy = -1;
    }
}

void Build(int nowNode, int left, int right)
{
    Tree[nowNode].lazy = -1;
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right)
    {
        Tree[nowNode].occupied = hotel[left];
        return;
    }
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    pushUp(nowNode);
}

void Update(int nowNode, int uleft, int uright, bool change)
{
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(uleft <= l && r < uright)
    {
        Tree[nowNode].occupied
    }
}

int Query(int nowNode, int length)
{

}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        memset(hotel, 0, sizeof(hotel));
        Build(1, 1, n);
        int X, D;
        while(m--)
        {
            scanf("%d", &op);
            if(op == 1)
            {
                scanf("%d", D);
                int ans = Query(1, D);
                printf("%d\n", ans);
                Update(1, ans, ans + D - 1, 1);
            }
            else
            {
                scanf("%d%d", &X, &D);
                Update(1, X, X + D - 1, 0);
            }
        }
    }
    return 0;
}
