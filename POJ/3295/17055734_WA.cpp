#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 150
using namespace std;

char s[maxn];

bool check(int p, int q, int r, int ss, int t)
{
    bool temp[2] = {false};
    int ptr = 0;
    for(int i = strlen(s)-1; i >= 0; i--)
    {
        if(ptr == 2)ptr = 0;
        if(s[i] == 'p')
            temp[ptr++] = p;
        else if(s[i] == 'q')
            temp[ptr++] = q;
        else if(s[i] == 'r')
            temp[ptr++] = r;
        else if(s[i] == 's')
            temp[ptr++] = ss;
        else if(s[i] == 't')
            temp[ptr++] = t;
        else if(s[i] == 'K')
        {
            bool ret = temp[0] && temp[1];
            temp[0] = ret;
            ptr = 1;
        }
        else if(s[i] == 'A')
        {
            bool ret = temp[0] || temp[1];
            temp[0] = ret;
            ptr = 1;
        }
        else if(s[i] == 'N')
        {
            temp[ptr-1] = !temp[ptr-1];
        }
        else if(s[i] == 'C')
        {
            bool ret;
            if(temp[0] == temp[1])ret = 1;
            else if(temp[0] == 1 && temp[1] == 0)ret = 1;
            else ret = 0;
            temp[0] = ret;
            ptr = 1;
        }
        else if(s[i] == 'E')
        {
            bool ret = (temp[0] == temp[1]);
            temp[0] = ret;
            ptr = 1;
        }
    }
    return temp[0];
}

int main()
{
    while(~scanf("%s", s))
    {
        if(strcmp(s, "0") == 0)break;
        bool flag = false;
        for(int a = 0; a < 2; a++)
        {
            for(int b = 0; b < 2; b++)
            {
                for(int c = 0; c < 2; c++)
                {
                    for(int d = 0; d < 2; d++)
                    {
                        for(int e = 0; e < 2; e++)
                        {
                            if(check(a, b, c, d, e) == false)
                            {
                                flag = true;
                                break;
                            }
                        }
                        if(flag)break;
                    }
                    if(flag)break;
                }
                if(flag)break;
            }
            if(flag)break;
        }
        if(flag)printf("not\n");
        else printf("tautology\n");
    }
    return 0;
}
