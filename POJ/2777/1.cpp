#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;

int l, t, o;
int ans[35] = {false};
char op[2];
struct segTree
{
    int left, right;
    int lazy;
    bool vis[35];
    void update(int val)
    {
        memset(vis, false, sizeof(vis));
        vis[val] = true;
        lazy = val;
    }
}Tree[4*maxn];

void pushUp(int index)
{
    memset(Tree[index].vis, 0, sizeof(Tree[index].vis));
    for(int i = 1; i <= t; i++)
        if(Tree[index<<1].vis[i] || Tree[index<<1|1].vis[i])
            Tree[index].vis[i] = true;
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

void inline record(int index)
{
    /*printf("rec: ");
    for(int i = 1; i <= t; i++)printf("%d ", Tree[index].vis[i]);
    printf("\n");*/
    for(int i = 1; i <= t; ++i)
        if(Tree[index].vis[i])ans[i] = true;
}

void Build(int nowNode, int left, int right)
{
    //printf("Build: %d %d %d\n", nowNode, left, right);

    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].lazy = 0;
    Tree[nowNode].vis[1] = true;
    if(left == right)return;
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    pushUp(nowNode);
}

void Update(int nowNode, int uleft, int uright, int after)
{
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
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
        record(nowNode);
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
    scanf("%d%d%d", &l, &t, &o);
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
            if(!strcmp(op, "P"))
            {
                scanf("%d%d", &a, &b);
                Query(1, min(a, b), max(a, b));
                int cnt = 0;
                for(int i = 1; i <= t; i++)
                    if(ans[i])cnt++;
                printf("%d\n", cnt);
                memset(ans, 0, sizeof(ans));
            }
        }
    }
    return 0;
}

/**

2 2 4
C 1 1 2
P 1 2
C 2 2 2
P 1 2

*/
