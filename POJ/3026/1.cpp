#include<cstdio>
#include<cstring>
#define maxn 60
#include<algorithm>
using namespace std;

int t, x, y;
char maze[maxn][maxn];

void in()
{
    getchar();
    for(int i = 0; i < y; i++)
        scanf("%s", maze[i]);
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &x, &y);
        in();

    }
}
