///submit-B
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define maxn 110
#define maxedge 10010
using namespace std;

int n;
int fa[maxn];

struct edge
{
    int start, dest;
    double cost;
}E[maxedge];
int p;

struct point
{
    double x, y, z;
    double radius;
}Point[maxn];

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

void init()
{
    for(int i = 0; i < n; i++)fa[i] = i;
    for(int i = 0; i < maxedge; i++)E[i].cost = 0;
    p = 0;
}

void add_point(int i, double x, double y, double z, double r)
{
    Point[i].x = x;
    Point[i].y = y;
    Point[i].z = z;
    Point[i].radius = r;
}

double square(double a)
{
    return a * a;
}

void add_edge(int a, int b, double dist)
{
    E[p].start = a;
    E[p].dest = b;
    E[p++].cost = dist;
    E[p].start = b;
    E[p].dest = a;
    E[p++].cost = dist;
}

bool operator < (edge a, edge b)
{
    return a.cost < b.cost;
}

bool Same(int x, int y)
{
    return Find(x) == Find(y);
}

int main()
{
    while(~scanf("%d", &n) && n)
    {
        init();
        double x, y, z, r;
        double ans = 0;
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf%lf%lf", &x, &y, &z, &r);
            add_point(i, x, y, z, r);
        }
        for(int i = 0; i < n; i++)
        {
            for(int j = i + 1; j < n; j++)///!!!此处j的循环若写成for(int j = 0; j < n; j++)就会TLE =.=只改了这里后就AC了。。
            {
                //if(i == j)continue;
                //printf("%d to %d, ", i, j);
                double x1 = Point[j].x, y1 = Point[j].y, z1 = Point[j].z, r1 = Point[j].radius;
                double x2 = Point[i].x, y2 = Point[i].y, z2 = Point[i].z, r2 = Point[i].radius;
                double dist = sqrt(square(x1 - x2) + square(y1 - y2) + square(z1 - z2));
                //printf("original dist = %lf, ", dist);
                dist = dist - r1 - r2;
                if(dist < 0)dist = 0;
                //printf("dist = %lf\n", dist);
                add_edge(j, i, dist);
            }
        }
        sort(E, E + p);
        for(int i = 0; i < p; i++)
        {
            int a = E[i].start, b = E[i].dest;
            double c = E[i].cost;
            if(Same(a, b))continue;
            ans += c;
            unite(a, b);
        }
        printf("%.3lf\n", ans);
    }
    return 0;
}
