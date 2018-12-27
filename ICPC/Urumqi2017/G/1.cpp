#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100010;

char s1[maxn], s2[20], op[5];
int T;
int Next[20];
int N;

void Get_next()
{
    int i = 0, j = -1;
    int len = strlen(s2);
    memset(Next, 0, sizeof(Next));
    Next[0] = -1;
    while(i < len)
    {
        if(j == -1 || s2[i] == s2[j])
        {
            while(s2[Next[j]] == s2[j])j = Next[j];
            Next[++i] = ++j;
        }
        else j = Next[j];
    }
}

int KMP(int s, int e)
{
	int plen = strlen(s2);
	int i = s, j = 0, ans = 0;
	while(i < e)
    {
        if(j == -1 || s1[i] == s2[j])
            ++ i, ++ j;
        else
            j = Next[j];
        if(j == plen)
            ++ ans, j = Next[j];
    }
	return ans;
}

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%s%s", &N, s1, s2);
        Get_next();
        while(N--)
        {
            scanf("%s", op);
            if(!strcmp(op, "C"))
            {
                int pos;
                char change[5];
                scanf("%d%s", &pos, change);
                s1[pos-1] = change[0];
            }
            else
            {
                int s, e;
                scanf("%d%d", &s, &e);
                --s;
                printf("%d\n", KMP(s, e));
            }
        }
    }
    return 0;
}
