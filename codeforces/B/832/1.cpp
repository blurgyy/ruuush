///Forget this one...
///should get some sleep
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 30
#define maxlen 100010
using namespace std;

char good[maxn] = {0};
char pattern[maxlen] = {0};
char query[maxlen];
int n;

void init()
{
    memset(good, 0, sizeof(good));
    memset(pattern, 0, sizeof(pattern));
}

bool in_good(char c)
{
    int len = strlen(good);
    for(int i = 0; i < len; i++)
        if(c == good[i])return true;
    return false;
}

bool kmp(char pat[], char orig[])
{
    int len1 = strlen(pat), len2 = strlen(orig);
    int next[maxn] = {0};
    next[0] = -1;
    int i = 0, j = -1;
    while(i < len1)
    {
        if(j == -1 || pat[i] == pat[j])next[++i] = ++j;
        else j = next[j];
    }
    for(i = 0; i < len1; i++)
        printf("%d ", next[i]);
    printf("\n");
    i = 0;
    j = 0;
    while(i < len2)
    {
        printf("%d\n", i);
        if(j == -1 || pat[j] == orig[i])
        {
            i++;
            j++;
        }
        else j = next[j];
        if(j == len1)return true;
    }
    return false;
}

int main()
{
    init();
    while(~scanf("%s", good))
    {
        scanf("%s", pattern);
        scanf("%d", &n);
        while(n--)
        {
            scanf("%s", query);
            int lenq = strlen(query), lenp = strlen(query);
            if(lenq > lenp || lenq + 1 < lenp)
            {
                printf("NO\n");
                continue;
            }
            bool met = false;
            bool ans = true, esc = false;
            for(int i = 0; i < lenp; i++)
            {
                if(pattern[i] == '*')met = true;
                if(met)
                {
                    /*
                    if(lenp == lenq)
                    {
                        if(!in_good(query[i]))
                        {
                            for(int j = i+1; j < lenp; j++)
                            {
                                if(pattern[j] != '?' && pattern[j] == query[j] || pattern[j] == '?' && in_good(query[j]))continue;
                                ans = false;
                            }
                        }
                        else ans = false;
                    }
                    else
                    {
                        for(int j = i+1; j < lenp; j++)
                        {
                            if(pattern[j] != '?' && pattern[j] == query[j-1] || pattern[j] == '?' && in_good(query[j-1]))continue;
                            ans = false;
                        }
                    }
                    break;
                    */
                    if(lenp == lenq)
                    {
                        if(!in_good(query[i]))
                        {
                            for(int j = i+1; j < lenp; j++)
                            {
                                if(pattern[j] != '?' && pattern[j] == query[j] || pattern[j] == '?' && in_good(query[j]))continue;
                                ans = false;
                            }
                        }
                        else ans = false;
                    }
                    else if(i == lenp-1)ans = true;
                    else if(i + 1 == lenp - 1)
                        if(pattern[i+1] == query[lenq-1])ans = true;
                        else ans = false;
                    else ans = kmp(pattern + i + 1, query + i);
                }
                else if(pattern[i] != '?' && query[i] != pattern[i] || pattern[i] == '?' && !in_good(query[i])){
                    ans = false;
                    break;
                }
            }
            if(ans)printf("YES\n");
            else printf("NO\n");
        }
        init();
    }
    return 0;
}

/**

abc
a?a?a*a
4
abacaba
abaca
apapa
aaaaax

*/
