#include<cstdio>
#include<cstring>
#include<map>
#define maxn 10010
#include<algorithm>
using namespace std;

int n;
int Case = 1;

struct cord
{
    int c[15];
};

bool able(cord a)
{
    for(int i = 0; i < 11; i++)
        if(a.c[i] != -1)return true;
    return false;
}

bool operator < (cord a, cord b)
{
    for(int i = 0; i < 10; i++)
        if(a.c[i] < b.c[i])return true;
        else return false;
}

bool operator == (cord a, cord b)
{
    if(a < b)return false;
    if(b < a)return false;
    return true;
}

map<cord, cord> path;

int main()
{
    while(~scanf("%d", &n) && n)
    {
        bool ans = false;
        int tmp = 0;
        cord s, e;
        for(int i = 0; i < n; i++)
            scanf("%d", s.c + i);
        for(int i = 0; i < n; i++)
            scanf("%d", e.c + i);
        cord a, b;
        scanf("%d", &tmp);
        while(tmp != -1)
        {
            a.c[0] = tmp;
            for(int i = 1; i < n; i++)
                scanf("%d", a.c + i);
            for(int i = 0; i < n; i++)
                scanf("%d", b.c + i);
            path[a] = b;
            scanf("%d", &tmp);
        }
        cord temp = s;
        while(able(path[temp]))
        {
            cord bla = temp;
            temp = path[temp];
            for(int i = 0; i < 12; i++)
                path[bla].c[i] = -1;
            if(temp == e)
            {
                ans = true;
                break;
            }
        }
        if(ans)printf("Maze #%d can be travelled\n", Case++);
        else printf("Maze #%d cannot be travelled\n", Case++);
    }
    return 0;
}