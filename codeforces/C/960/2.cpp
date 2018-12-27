#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 10010;

ll x, d;
ll rec[70];
map<ll, int> ans;

int bs(ll e, int left = 0, int right = 63){
    if(left >= right)return right;
    int mid = left + right >> 1;
    if(e <= rec[mid])return bs(e, left, mid);
    return bs(e, mid + 1, right);
}

int main(){
    rec[1] = 1;
    for(int i = 2; i < 64; ++ i)
        rec[i] = rec[i-1] << 1 | 1;
    while(~scanf("%I64d%I64d", &x, &d)){
        ans.clear();
        int cnt = 0;
        ll base = 1;

        while(x > 0){
            int pos = bs(x);
            if(x < rec[pos])pos -= 1;
            x -= rec[pos];
            ans[base] = pos;
            base += d + 1;
            cnt += pos;
        }

        printf("%d\n", cnt);
        for(auto i = ans.begin(); i != ans.end(); ++ i){
            while(i->second --)
                printf("%I64d ", i->first);
        }
        printf("\n");
    }
    return 0;
}