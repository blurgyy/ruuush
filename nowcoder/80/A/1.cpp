#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;
const ll mod = 1e9 + 7;

char s[maxn];
int idx[256];
ll ans;

void init(){
    for(int i = 'a'; i <= 'z'; ++ i)
        idx[i] = idx[i-32] = 2;
    idx['i'] = idx['I'] = idx['l'] = idx['L'] = 4;
    for(int i = '0'; i <= '9'; ++ i)
        idx[i] = 1;
    idx['0'] = idx['o'] = idx['O'] = 3;
}

int main(){
    init();
    while(~scanf("%s", s)){
        ans = 1;
        for(int i = 0, len = strlen(s); i < len; ++ i)
            ans = ans * idx[s[i]] % mod;
        printf("%lld\n", ans);
    }
    return 0;
}