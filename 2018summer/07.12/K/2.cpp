#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50;

char s[maxn];

bool check(ll n){
    if(n == 1)return false;
    if(n == 2)return true;
    if(!(n & 1))return false;
    int top = sqrt(n) + 2;
    for(int i = 3; i < top; ++ i){
        if(n % i == 0)return false;
    }
    return true;
}

int main(){
    while(~scanf("%s", s)){
        int len = strlen(s);
        ll n = 0;
        bool ans = true;
        for(int i = 0; i < len; ++ i){
            int pos = len - i - 1;
            if(s[pos] == '3' || s[pos] == '4' || s[pos] == '7'){
                ans = false;
                break;
            }
            ll add = 0;
            if(s[pos] == '6')add = 9;
            else if(s[pos] == '9')add = 6;
            else add = s[pos] - '0';
            n *= 10;
            n += add;
        }
        if(!ans){
            printf("no\n");
            continue;
        }
        printf("n = %lld\n", n);
        if(check(n)){
            printf("yes\n");
            continue;
        }
        printf("no\n");
    }
    return 0;
}