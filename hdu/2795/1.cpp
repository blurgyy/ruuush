#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 200010
using namespace std;

int h, w, n;
struct segTree
{
    int left, right;
    int max;
}Tree[4*maxn];

void pushUp(int index)
{
    Tree[index].max = max(Tree[index<<1].max, Tree[index<<1|1].max);
}

void Build(int nowNode, int left, int right)
{
    Tree[nowNode].left = left;
    Tree[nowNode].right = right;
    Tree[nowNode].max = w;
    if(left == right)return;
    int mid = (left + right)>>1;
    Build(nowNode<<1, left, mid);
    Build(nowNode<<1|1, mid+1, right);
    pushUp(nowNode);
}

int Find(int nowNode, int width)
{
    if(Tree[nowNode].max < width)return 0;
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(l == r)
    {
        Tree[nowNode].max -= width;
        while(nowNode >>= 1)
            pushUp(nowNode);
        return l;
    }
    int a = Find(nowNode<<1, width);
    if(a)return a;
    return Find(nowNode<<1|1, width);
}
/*
void Update(int nowNode, int index, int new_width)
{
    int l = Tree[nowNode].left, r = Tree[nowNode].right;
    if(l == r)
    {
        Tree[nowNode].max -= new_width;
        return;
    }
    int mid = (l + r)>>1;
    if(index <= mid)Update(nowNode<<1, index, new_width);
    else Update(nowNode<<1|1, index, new_width);
    pushUp(nowNode);
}
*/
int main()
{
    while(~scanf("%d%d%d", &h, &w, &n))
    {
        if(h > n)h = n;
        Build(1, 1, h);
        int anno;
        while(n--)
        {
            scanf("%d", &anno);
            int node = Find(1, anno);
            if(node)printf("%d\n", node);
            else printf("-1\n");
        }
    }
    return 0;
}

/**

3 5 5
2
4
3
3
3

*/
