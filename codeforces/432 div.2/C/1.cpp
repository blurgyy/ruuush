#include<cstdio>
#include<cmath>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1010;

int n;
int ans, out[20], p;
struct Vec
{
    int dir[6];
};
struct Points
{
    int coor[6];
    vector<Vec> Vector;
}input[20];
int tmp[6];

void add(int i, int j, Vec a)
{
    input[i].Vector.push_back(a);
    for(int i = 0; i < 5; ++ i)
        a.dir[i] = -a.dir[i];
    input[j].Vector.push_back(a);
}

bool check(int index)
{
    vector<Vec>::iterator iter, jter;
    for(iter = input[index].Vector.begin(); iter != input[index].Vector.end(); ++ iter)
    {
        for(jter = iter, ++ jter; jter != input[index].Vector.end(); ++ jter)
        {
            int prod = 0;
            for(int i = 0; i < 5; ++ i)
                prod += iter->dir[i] * jter->dir[i];
            if(prod > 0)return false;
        }
    }
    return true;
}

int main()
{
    while(~scanf("%d", &n))
    {
        ans = 0;
        memset(out, 0, sizeof(out));
        p = 0;
        if(n > 12)
        {
            while(n--)
                for(int i = 0; i < 5; ++ i)
                    scanf("%d", tmp + i);
            printf("0\n");
            continue;
        }
        for(int i = 0; i < n; ++ i)
        {
            for(int id = 0; id < 5; ++ id)
                scanf("%d", input[i].coor + id);
            for(int j = 0; j < i; ++ j)
            {
                Vec a;
                for(int k = 0; k < 5; ++ k)
                    a.dir[k] = input[j].coor[k] - input[i].coor[k];
                add(i, j, a);
            }
        }
        for(int i = 0; i < n; ++ i)
            if(check(i))
            {
                ++ ans;
                out[p++] = i + 1;
            }
        if(ans)
        {
            printf("%d\n", ans);
            for(int i = 0; i < p; ++ i)
                printf("%d%c", out[i], " \n"[i==p-1]);
        }
        else printf("0\n");
    }
    return 0;
}
