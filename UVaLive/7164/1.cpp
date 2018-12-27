#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
using namespace std;

string out[2][7] = {"", "Yakk", "Doh", "Seh", "Ghar", "Bang", "Sheesh", "", "Habb Yakk", "Dobara", "Dousa", "Dorgy", "Dabash", "Dosh"};
int Case = 1;

int main()
{
    int T;
    int a, b;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &a, &b);
        printf("Case %d: ", Case++);
        if(a == 5 && b == 6 || a == 6 && b == 5)
        {
            printf("Sheesh Beesh\n");
            continue;
        }
        if(a != b)
        {
            cout << out[0][max(a, b)] << ' ' << out[0][min(a, b)] << endl;
            continue;
        }
        cout << out[1][a] << endl;
    }
    return 0;
}
