///注意初始化pt=0, point.clear(), i:0->n, fa[i] = i
///尤其是point.clear();
///以及 不喜欢这种两个测试样例之间输出空行。。。有时不知道到底要先输出空行还是后输出。。

#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
#define maxn 510
using namespace std;

int n;
int fa[maxn];
vector<pair<double, double> > point;
int Case = 1;
double ans;

struct edge
{
    int start, dest;
    double cost;
}E[maxn * maxn];
int pt;

bool operator < (edge a, edge b)
{
    return a.cost < b.cost;
}

int Find(int x)
{
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

void unite(int x, int y)
{
    int t1 = Find(x), t2 = Find(y);
    if(t1 == t2)return;
    fa[t1] = t2;
}

bool Same(int x, int y)
{
    return Find(x) == Find(y);
}

void add_edge(int a, int b, double c)
{
    E[pt].start = a;
    E[pt].dest = b;
    E[pt++].cost = c;
}

double square(double a)
{
    return a * a;
}

void init()
{
    point.clear();
    for(int i = 0; i < maxn; i++)fa[i] = i;
    pt = 0;
    ans = 0;
}

int main()
{
    while(~scanf("%d", &n) && n)
    {
        if(Case > 1)printf("\n");
        init();
        double x, y;
        while(n--)
        {
            scanf("%lf%lf", &x, &y);
            point.push_back(make_pair(x, y));
        }
        for(int i = 0; i < point.size(); i++)
            for(int j = i+1; j < point.size(); j++)
            {
                double x1 = point[i].first, y1 = point[i].second;
                double x2 = point[j].first, y2 = point[j].second;
                double len = sqrt(square(x1 - x2) + square(y1 - y2));
                add_edge(i, j, len);
            }
        sort(E, E + pt);
/*
        for(int i = 0; i < pt; i++)
            printf("%8.2lf", E[i].cost);
        printf("\n");
*/
        for(int i = 0; i < pt; i++)
        {
            int a = E[i].start, b = E[i].dest;
            double c = E[i].cost;
            if(Same(a, b))continue;
            unite(a, b);
            ans += c;
        }
        printf("Case #%d:\nThe minimal distance is: %.2lf\n", Case++, ans);
    }
    return 0;
}
/**
5
0 0
0 1
1 1
1 0
0.5 0.5
*/
