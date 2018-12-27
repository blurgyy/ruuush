/**
    不知所云。。
    搞不出
    咸鱼
*/

/**
    K, A, N, C, E mean and, or, not, implies, and equals as defined in the truth table below.
    Only five letters: p, q, r, s, t listed!
*/
#include<cstdio>
#include<algorithm>
#include<cstring>
#define maxn 200
using namespace std;

bool flag = false;

bool input()
{
    char c;
    scanf("%c", &c);
    if(c == 10)return flag;
    if(c == 'K')return inK();
    if(c == 'A')return inA();
    if(c == 'N')return inN();
    if(c == 'C')return inC();
    if(c == 'E')return inE();
    return c;
}

bool inK()
{
    char a, b;
    scanf("%c%c", &a, &b);
    return false;
}

bool inA()
{
    char a, b;
    scanf("%c%c", &a, &b);

}

int main()
{
    char wff[maxn];
    while(~scanf("%s", wff))
    {
        int time = 32;
        bool those[5] = {0};
        for(int i = 0; i < 32; i++)
        {

        }
    }
}
