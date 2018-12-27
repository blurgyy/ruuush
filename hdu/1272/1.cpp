#include<cstdio>
#include<map>
#include<set>
#define maxn 10010
using namespace std;

int a, b;
bool ans;
//map<int, int> tree;
set<int> rec;
int fa[maxn];

int Find_tree(int x)
{
    return fa[x] == x ? x : fa[x] = Find_tree(fa[x]);
    //return tree[x] == 0 ? x : fa[x] = Find_tree(tree[x]);
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
    //tree.clear();
    rec.clear();
    ans = true;
}

void out()
{
    if(!ans)printf("No\n");
    else
    {
        //map<int, int>::iterator i = tree.begin();
        set<int, int>::iterator i = rec.begin();
        int only = Find_tree(*i);
        //int only = Find_tree((*i).first);
        //printf("only = %d\n", only);
        for(; i != rec.end(); i++)
            if(Find_tree((*i)/*.first*/) != only)
            {
                ans = false;
                break;
            }
        if(!ans)printf("No\n");
        else printf("Yes\n");
    }
}

bool Same(int a, int b)
{
    return Find_tree(a) == Find_tree(b);
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
        if(rec.find(b) == rec.end())
        {
            rec.insert(b);
            unite(b, a);
        }
        else
        {
            if(Same(a, b))ans = false;
        }
        /*
        if(tree[b] && ans)ans = false;
        else if(tree[b] == 0)
        {
            tree[b] = a;
            unite(b, a);
        }
        */
    }
}
