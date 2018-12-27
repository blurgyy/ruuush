#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#define maxn 10010
using namespace std;

int a, b;
int fa[maxn];
set<int> in;

int Find(int x)
{
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

void unite(int x, int y)
{
    int f1 = Find(x), f2 = Find(y);
    if(f1 == f2)return;
    fa[f1] = f2;
}

void init()
{
    for(int i = 0; i < maxn; i++)
        fa[i] = i;
    in.clear();
}

void out()
{
    int ans = 0;
    set<int>::iterator i;
    for(i = in.begin(); i != in.end(); i++)
    {
        //  printf("fa[%d] = %d\n", *i, fa[*i]);
        if(fa[*i] == *i)ans++;
    }
    printf("\n");
    if(ans > 1)printf("no\n");
    else printf("yes\n");
}

int main()
{
    while(~scanf("%d%d", &a, &b) && (a != -1 &&b != -1))
    {
        if(a == 0 && b == 0)
        {
            out();
            init();
            continue;
        }
        in.insert(a);
        in.insert(b);
        unite(a, b);
    }
}
