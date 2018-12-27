#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 200010
using namespace std;

int n, m;
int Grade[maxn];
char op[2];
struct seg
{
    int left, right;
    int max;
}Tree[4*maxn];

void pushUp(int index)
{
    while(index >>= 1)
        Tree[index].max = max(Tree[index<<1].max, Tree[index<<1|1].max);
}

void Build(int nowNode, int left, int right)
{
    Tree[nowNode].max = -1;
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    if(left == right)
    {
        Tree[nowNode].max = Grade[left];
        return;
    }
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid + 1, right);
    Tree[nowNode].max = max(Tree[nowNode<<1].max, Tree[nowNode<<1|1].max);
}

void Update(int nowNode, int index, int after)
{
    int left = Tree[nowNode].left, right = Tree[nowNode].right;
    if(left == right)
    {
        Tree[nowNode].max = after;
        pushUp(nowNode);
        return;
    }
    int mid = (left + right)>>1;
    if(index <= mid)Update(nowNode<<1, index, after);
    else Update(nowNode<<1|1, index, after);
}

int Query(int nowNode, int left, int right)///¼ÇµÃreturn ans !!!
{
    int ans = -1;
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(l > right || r < left)return -1;
    if(left <= l && r <= right)return Tree[nowNode].max;
    int mid = (l + r)>>1;
    if(l <= mid)ans = max(ans, Query(nowNode<<1, left, right));
    if(r > mid)ans = max(ans, Query(nowNode<<1|1, left, right));
    return ans;
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        for(int i = 1; i <= n; i++)
            scanf("%d", Grade + i);
        Build(1, 1, n);
        int a, b;
        while(m--)
        {
            scanf("%s", op);
            scanf("%d%d", &a, &b);
            if(!strcmp(op, "Q"))printf("%d\n", Query(1, a, b));
            if(!strcmp(op, "U"))Update(1, a, b);
        }
    }
    return 0;
}

/**

5 6
1 2 3 4 5
Q 1 5
U 3 6
Q 3 4
Q 4 5
U 2 9
Q 1 5

*/
