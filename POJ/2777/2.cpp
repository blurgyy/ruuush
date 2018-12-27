#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;

int l, t, o;
char op[2];
int ans = 0;
struct segTree
{
    int left, right;
    int rec;
    int lazy;
    void update(int val)
    {
        rec = 1;
        lazy = val;
        val--;
        rec <<= val;
    }
}Tree[4*maxn];

void pushUp(int index)
{
    Tree[index].rec = 0;///记得每次要先归零
    Tree[index].rec |= Tree[index<<1].rec | Tree[index<<1|1].rec;
}

void pushDown(int index)
{
    int val = Tree[index].lazy;
    if(val)
    {
        Tree[index<<1].update(val);
        Tree[index<<1|1].update(val);
        Tree[index].lazy = 0;
    }
}

void Build(int nowNode, int left, int right)
{
    //printf("%d %d %d\n", nowNode, left ,right);
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].rec = 1;
    if(left == right)return;
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    pushUp(nowNode);
}

void Update(int nowNode, int uleft, int uright, int after)
{
    int l = Tree[nowNode].left, r = Tree[nowNode].right;

    //printf("Update: %d %d %d\n", nowNode, l, r);

    if(uleft <= l && r <= uright)
    {
        Tree[nowNode].update(after);
        return;
    }
    pushDown(nowNode);
    int mid = (l + r)>>1;
    if(uleft <= mid)Update(nowNode<<1, uleft, uright, after);
    if(uright > mid)Update(nowNode<<1|1, uleft, uright, after);
    pushUp(nowNode);
}

void Query(int nowNode, int qleft, int qright)
{
    int l = Tree[nowNode].left, r = Tree[nowNode].right;

    //printf("Query: %d %d %d\n", nowNode, l, r);

    if(qleft <= l && r <= qright)
    {
        //printf("%d %d\n", nowNode, Tree[nowNode].rec);
        ans |= Tree[nowNode].rec;
        return;
    }
    pushDown(nowNode);
    int mid = (l + r)>>1;
    if(qleft <= mid)Query(nowNode<<1, qleft, qright);
    if(qright > mid)Query(nowNode<<1|1, qleft, qright);
    pushUp(nowNode);
}

int main()
{
    while(~scanf("%d%d%d", &l, &t, &o))
    {
        Build(1, 1, l);
        int a, b, c;
        while(o--)
        {
            scanf("%s", op);
            if(!strcmp(op, "C"))
            {
                scanf("%d%d%d", &a, &b, &c);
                Update(1, min(a, b), max(a, b), c);
            }
            else
            {
                scanf("%d%d", &a, &b);
                Query(1, min(a, b), max(a, b));
                int cnt = 0;
                while(ans)
                {
                    if(ans & 1)cnt++;
                    ans >>= 1;
                }
                printf("%d\n", cnt);
                ans = 0;
            }
        }
    }
    return 0;
}
