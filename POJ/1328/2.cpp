///NOPE
#include<cstdio>
#include<cmath>
#include<set>
#include<algorithm>
using namespace std;

struct cord
{
    int x;
    int y;
};

bool operator < (cord a, cord b)
{
    return a.x < b.x;
}

int main()
{
    typedef set<cord>::iterator IT;
    int Case = 1, n, d;
    while(~scanf("%d%d", &n, &d))
    {
        d *= d;
        set<cord> in;
        int i, x, y;
        cord node;
        for(i = 0; i < n; i++)
        {
            scanf("%d%d", x, y);
            node.x = x;
            node.y = y;
            in.insert(node);
        }
        IT it;
        for(it = in.begin(), it++; it != in.end(); it++)
        {
            double x = (*it).x;
            double y = (*it).y;
            double nx = x - sqrt(d - y*y);
            IT i;
            for(i = in.begin(); i != it; i++)
            {
                if(outrange((*i).x, (*i).y, nx, d))
            }
        }
    }
}
