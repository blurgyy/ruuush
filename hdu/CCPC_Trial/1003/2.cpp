#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define maxn 5100
using namespace std;

int rel[maxn][maxn];
vector<int> rec1[maxn], rec0[maxn];

int main()
{
    int T;
    int n;
    scanf("%d", &T);
    while(T--)
    {
        memset(rel, 0, sizeof(rel));
        for(int i = 0; i < maxn; i++)
            rec0[i].clear(), rec1[i].clear();
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n-i; j++)
                scanf("%d", rel[i] + j+i);
        bool first0 = true, first1 = true;
        bool ans = true;
        bool esc = false;
        vector<int>::iterator k;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(i == j)continue;
                if(rel[i][j] && !first1)
                {
                    rec1[i].push_back(j);
                    for(k = rec1[i].begin(); k != rec1[i].end(); k++)
                    {
                        int now = *k;
                        if(rel[i][j])
                        {
                            ans = false;
                            esc = true;
                            break;
                        }
                    }
                }
                if(!rel[i][j] && !first0)
                {
                    rec0[i].push_back(j);
                    for(auto i = rec1[i].begin(); i != rec1[i].end(); i++)
                        if(!rel[i][j])
                        {
                            ans = false;
                            esc = true;
                            break;
                        }
                }
                if(rel[i][j] && first1)
                {
                    first1 = false;
                    rec1[i].push_back(j);
                }
                if(!rel[i][j] && first0)
                {
                    first0 = false;
                    rec0[i].push_back(j);
                }
                if(esc)break;
            }
            if(esc)break;
        }
        if(ans)printf("Great Team!\n");
        else printf("Bad Team!\n");
    }
    return 0;
}
