#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 200010
using namespace std;

int h, w, n;
int announcement;
struct segTree
{
    int left, right;
    int maxRoom;
}Tree[4*maxn];

void pushUp(int index)
{
    Tree[index].maxRoom = max(Tree[index<<1].maxRoom, Tree[index<<1|1].maxRoom);
}

void Build(int nowNode, int left, int right)
{
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].maxRoom = w;
    if(left == right)return;
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    pushUp(nowNode);
}

int Find(int nowNode, int width)
{
    if(Tree[nowNode].maxRoom < width)return -1;
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(l == r)
    {
        Tree[nowNode].maxRoom -= width;
        while(nowNode >>= 1)pushUp(nowNode);
        return l;
    }
    int ans = Find(nowNode<<1, width);
    if(ans != -1)return ans;
    return Find(nowNode<<1|1, width);
}

int main()
{
    while(~scanf("%d%d%d", &h, &w, &n))
    {
        if(h > n)h = n;
        Build(1, 1, h);
        while(n--)
        {
            scanf("%d", &announcement);
            int node = Find(1, announcement);
            printf("%d\n", node);
        }
    }
    return 0;
}

/**

2 100 5
100 10 1 98 9

*/
