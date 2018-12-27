#include<cstdio>
#include<map>
#include<set>
#define maxn 1010
using namespace std;

int a, b;
bool ans;
map<int, int> tree;
set<int> rec;
int fa[maxn];
int Case = 1;

int Find_tree(int x)
{
    return tree[x] == 0 ? x : fa[x] = Find_tree(tree[x]);
}

void init()
{
    for(int i = 0; i < maxn; i++)
        fa[i] = i;
    tree.clear();
    rec.clear();
    ans = true;
}

void out()
{
    if(!ans)printf("Case %d is not a tree.\n", Case++);
    else
    {
        set<int>::iterator i = rec.begin();
        int only = Find_tree(*i);
        for(; i != rec.end(); i++)
            if(Find_tree(*i) != only)
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
        rec.insert(b);
        if(tree[b] && ans)ans = false;
        else if(tree[b] == 0)tree[b] = a;
    }
}
