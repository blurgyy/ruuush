#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 20010;

struct node{
    int v, cnt;
}a[maxn];
int n, p, pt, cnt[maxn], pcnt[maxn];
ll s, pref[maxn];

bool operator< (node a, node b){
    return a.v < b.v;
}

int index(int e, int left = 0, int right = pt-1){    ///a[index] >= e
    if(left >= right)return right;
    int mid = left + right >> 1;
    if(e <= a[mid].v)return index(e, left, mid);
    return index(e, mid + 1, right);
}

bool check(int wgh){
    int idx = index(wgh);   ///a[idx] >= wgh;
    ll ans = 0;
    if(idx == pt - 1)return true;
    if(a[idx].v == wgh){
        if(idx)
            ans = (pref[pt-1] - pref[idx-1] - 1LL * (pcnt[pt-1] - pcnt[idx-1]) * wgh) * p;
        else 
            ans = (pref[pt-1] - 1LL * pcnt[pt-1] * wgh) * p;
    }
    else {
        ans = 1LL * (pref[pt-1] - pref[idx-1]) * p;
        ans -= (1LL * (pcnt[pt-1] - pcnt[idx-1]) * wgh) * p;
    }
    return ans <= s;
}

int bs(int left = 1, int right = a[pt-1].v){
    //printf("range: %d %d\n", left, right);
    if(left >= right)return right;
    int mid = left + right >> 1;
    if(check(mid))return bs(left, mid);
    return bs(mid + 1, right);
}

int main(){
    while(~scanf("%d", &n)){
        memset(cnt, 0, sizeof(cnt));
        int x;
        for(int i = 0; i < n; ++ i){
            scanf("%d", &x);
            cnt[x] ++;
        }
        scanf("%d%lld", &p, &s);
        pt = 0;
        for(int i = 1; i < maxn; ++ i){
            if(cnt[i]){
                a[pt].v = i;
                a[pt++].cnt = cnt[i];
            }
        }
        memset(pref, 0, sizeof(pref));
        memset(pcnt, 0, sizeof(pcnt));
        pref[0] = a[0].v * a[0].cnt;
        pcnt[0] = a[0].cnt;
        for(int i = 1; i < pt; ++ i){
            pref[i] = pref[i-1] + a[i].v * a[i].cnt;
            pcnt[i] = pcnt[i-1] + a[i].cnt;
        }
        printf("%d\n", bs());
    }
    return 0;
}

/**

4
6 7 8 9
1 3

5
11 14 6 13 11
4 68

*/