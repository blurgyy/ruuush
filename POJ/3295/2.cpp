/**
    改毁了。。。
        明天必须搞出来
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 150
#define MAXN 1010
using namespace std;

char s[maxn];
bool temp[MAXN] = {false};
int ptr = 0;

bool check(int p, int q, int r, int ss, int t)
{
    for(int i = strlen(s)-1; i >= 0; i--)
    {
        if(s[i] == 'p')temp[ptr++] = p;
        else if(s[i] == 'q')temp[ptr++] = q;
        else if(s[i] == 'r')temp[ptr++] = r;
        else if(s[i] == 's')temp[ptr++] = ss;
        else if(s[i] == 't')temp[ptr++] = t;
        else if(s[i] == 'K')
        {
            bool t1 = temp[--ptr];
            bool t2 = temp[--ptr];
            temp[ptr++] = (t1&&t2);
        }
        else if(s[i] == 'A')
        {
            bool t1 = temp[--ptr];
            bool t2 = temp[--ptr];
            temp[ptr++] = (t1||t2);
        }
        else if(s[i] == 'N')
        {
            bool t = temp[--ptr];
            temp[ptr++] = (!t);
        }
        else if(s[i] == 'C')
        {
            bool t1 = temp[--ptr];
            bool t2 = temp[--ptr];
            if(t1 == true && t2 == false)temp[ptr++] = false;
            else temp[ptr++] = true;
        }
        else if(s[i] == 'E')
        {
            bool t1 = temp[--ptr];
            bool t2 = temp[--ptr];
            if(t1 == t2)temp[ptr++] = true;
            else temp[ptr++] = false;
        }
    }
}

bool sol()
{
    for(int a = 0; a < 2; a++)
        for(int b = 0; b < 2; b++)
            for(int c = 0; c < 2; c++)
                for(int d = 0; d < 2; d++)
                    for(int e = 0; e < 2; e++)
                    {
                        check(a, b, c, d, e);
                        if(temp[0] == false)return false;
                    }
    return true;
}

int main()
{
    while(~scanf("%s", s))
    {
        if(strcmp(s, "0") == 0)break;
        if(sol())printf("tautology\n");
        else printf("not\n");
    }
    return 0;
}
