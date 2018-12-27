#include<cstdio>
#include<algorithm>
using namespace std;

char building[30][150] = {0};

bool checkDone(int row, int m)
{
    for(int i = 1; i <= m+2; i++)
        if(building[row][i] != '0')return false;
    return true;
}

int main()
{
    int n, m;
    while(~scanf("%d%d\n", &n, &m))
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m + 2; j++)
            {
                scanf("%c", building[i] + j);
            }
            getchar();
        }

    }
    return 0;
}
