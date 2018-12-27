#include<cstdio>
#include<cstring>
#define maxn 50010

int T;
int n;
int a[maxn];
char op[5];
int Case = 1;
struct seg
{
    int left, right;
    int sum;
}Tree[4*maxn];

void pushUp(int index)
{
    Tree[index].sum = Tree[index<<1].sum + Tree[index<<1|1].sum;
}

void Build(int nowNode, int left, int right)
{
    Tree[nowNode].sum = 0;
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right)
    {
        Tree[nowNode].sum = a[left];
        return;
    }
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid + 1, right);
    pushUp(nowNode);
}

void Update(int nowNode, int index, int addVal)
{
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(l == r)
    {
        Tree[nowNode].sum += addVal;
        return;
    }
    int mid = (l + r)>>1;
    if(index <= mid)Update(nowNode<<1, index, addVal);
    else Update(nowNode<<1|1, index, addVal);
    pushUp(nowNode);
}

int Query(int nowNode, int left, int right)
{
    int ans = 0;
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(left <= l && r <= right)return Tree[nowNode].sum;
    int mid = (l + r)>>1;
    if(left <= mid)ans += Query(nowNode<<1, left, right);
    if(right > mid)ans += Query(nowNode<<1|1, left, right);
    return ans;
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        printf("Case %d:\n", Case++);
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%d", a + i);
        Build(1, 1, n);
        int x, y;
        while(true)
        {
            scanf("%s", op);
            if(!strcmp(op, "End"))break;
            scanf("%d%d", &x, &y);
            if(!strcmp(op, "Add"))Update(1, x, y);
            if(!strcmp(op, "Sub"))Update(1, x, -y);
            if(!strcmp(op, "Query"))printf("%d\n", Query(1, x, y));
        }
    }
    return 0;
}
