#include<cstdio>
#include<map>
#define maxn 110
using namespace std;

int a, b;
bool ans;
map<int, int> tree;
int fa[maxn];
int Case = 1;

int Find_tree(int x)
{
    return tree[x] == 0 ? x : fa[x] = Find_tree(tree[x]);
}

void unite(int x, int y)
{
    int f1 = Find_tree(x), f2 = Find_tree(y);
    if(f1 == f2)return;
    fa[f1] = f2;
}

void init()
{
    for(int i = 0; i < maxn; i++)
        fa[i] = i;
    tree.clear();
    ans = true;
}

void out()
{
    if(!ans)printf("Case %d is not a tree.\n", Case++);
    else
    {
        map<int, int>::iterator i = tree.begin();
        int only = Find_tree((*i).first);
        //printf("only = %d\n", only);
        for(; i != tree.end(); i++)
            if(Find_tree((*i).first) != only)
            {
                ans = false;
                break;
            }
        if(!ans)printf("Case %d is not a tree.\n", Case++);
        else printf("Case %d is a tree.\n", Case++);
    }
}

int main()
{
    init();
    while(~scanf("%d%d", &a, &b) && (a != -1 && b != -1))
    {
        if(a == 0 && b == 0)
        {
            out();
            init();
            continue;
        }
        if(tree[b] && ans)ans = false;
        else if(tree[b] == 0)
        {
            tree[b] = a;
            unite(b, a);
        }
    }
}
