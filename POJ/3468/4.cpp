#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
#define ll long long
using namespace std;

int n, q;
ll a[maxn];
char op[2];
struct segTree
{
    int left, right;
    ll sum, lazy;
    void update(ll val)
    {
        sum += (right - left + 1) * val;
        lazy += val;
    }
}Tree[4*maxn];

void pushUp(int index)
{
    Tree[index].sum = Tree[index<<1].sum + Tree[index<<1|1].sum;
}

void pushDown(int index)
{
    ll val = Tree[index].lazy;
    if(val)
    {
        Tree[index<<1].update(val);
        Tree[index<<1|1].update(val);
        Tree[index].lazy = 0;
    }
}

void Build(int nowNode, int left, int right)
{
    Tree[nowNode].lazy = 0;
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right)
    {
        Tree[nowNode].sum = a[left];
        return;
    }
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    pushUp(nowNode);
}

void Update(int nowNode, int uleft, int uright, int addVal)
{
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(uleft <= left && right <= uright)
    {
        Tree[nowNode].update(addVal);
        return;
    }
    int mid = (left + right)>>1;
    pushDown(nowNode);
    if(uleft <= mid)Update(nowNode<<1, uleft, uright, addVal);
    if(uright > mid)Update(nowNode<<1|1, uleft, uright, addVal);
    pushUp(nowNode);
}

ll Query(int nowNode, int qleft, int qright)
{
    ll ans = 0;
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(qleft <= left && right <= qright)return Tree[nowNode].sum;
    pushDown(nowNode);
    int mid = (left + right)>>1;
    if(qleft <= mid)ans += Query(nowNode<<1, qleft, qright);
    if(qright > mid)ans += Query(nowNode<<1|1, qleft, qright);
    pushUp(nowNode);
    return ans;
}

int main()
{
    while(~scanf("%d%d", &n, &q))
    {
        for(int i = 1; i <= n; i++)
            scanf("%lld", a + i);
        Build(1, 1, n);
        int a, b, c;
        while(q--)
        {
            scanf("%s", op);
            if(!strcmp(op, "C"))
            {
                scanf("%d%d%d", &a, &b, &c);
                Update(1, a, b, c);
            }
            if(!strcmp(op, "Q"))
            {
                scanf("%d%d", &a, &b);
                printf("%lld\n", Query(1, a, b));
            }
        }
    }
    return 0;
}

/**

10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4

*/
