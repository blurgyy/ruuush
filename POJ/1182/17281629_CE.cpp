#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
const int N = 50000 + 5;
int fa[3 * N];
int n, k, x, y;

int init(int n)
{
    for(int i = 0; i <= n; i++)
        fa[i] = i;
}
int find(int x)
{
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void unite(int x, int y)
{
    int xx = find(x);
    int yy = find(y);
    if(xx != yy)
    {
        fa[xx] = yy;
    }
}
bool same(int x, int y)
{
    return find(x) == find(y);
}

void solve()
{
    scanf("%d%d", &n, &k);
    init(3*n);
    int ans = 0;
    while(k--)
    {
        int op;
        scanf("%d%d%d", &op, &x, &y);
        x--; y--;
        if(x < 0 || x >= n || y < 0 || y >= n)
        {
            ans++;
            continue;
        }
        if(op == 1)
        {
            if(same(x, y + n) || same(x, y + 2 * n))
            {
                ans++;
            }
            else
            {
                unite(x, y);
                unite(x + n, y + n);
                unite(x + 2 * n, y + 2 * n);
            }
        }
        else
        {
            if(same(x, y) || same(x, y + 2 * n))
            {
                ans++;
            }
            else
            {
                unite(x, y + n);
                unite(x + n, y + 2 * n);
                unite(x + 2 * n, y);
            }
        }
    }
    printf("%d\n", ans);
}

int main()
{
    solve();
    return 0;
}