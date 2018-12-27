//Fuck that

#include<bits/stdc++.h>
using namespace std;

int s, n, m;
int ans;

int exgcd(int a, int b, int& x, int& y){
    if(b == 1){
        x = 1;
        y = 0;
        return a;
    }
    int ret = exgcd(b, a%b, x, y);
    int t = x;
    x = y;
    y = t - (a/b) * y;
    return ret;
}

int main(){
    while(~scanf("%d%d%d", &s, &n, &m) && s || n || m){
        ans = 0;
        if(n > m)swap(n, m);
        if(s&1);
        else{
            s /= 2;
            if(n > s);
            else if(m > s){
                if(s % n);
                else ans = 1 + s / n;
            }
            else if(n == s || m == s)ans = 2;
            else{
                int x, y;
                int g = exgcd(n, m, x, y);
                if(s%g);
                printf("x = %d. y = %d\n", x, y);
                else if(x >= 0 && y >= 0)ans = 2 * (x + y) * s/g;
            }
        }
        if(ans)printf("%d\n", ans);
        else printf("NO\n");
    }
    return 0;
}