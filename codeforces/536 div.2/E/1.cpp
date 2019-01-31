// MISC, just ignore
////MISC failed

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n, m, k;
struct seg{
    int s, t, d;
    int w;
    int dur;
    double ev;
    bool operator< (const seg &rhs){
        // return dur == rhs.dur ? d > rhs.d : dur < rhs.dur;
        return ev > rhs.ev;
    }
    void input(){
        scanf("%d%d%d%d", &s, &t, &d, &w);
        dur = t - s + 1;
        ev = w / dur;
    }
}a[maxn];

int main(){
    while(~scanf("%d%d%d", &n, &m, &k)){
        for(int i = 1; i <= k; ++ i){
            a[i].input();
        }
        sort(a+1, a+1 + k);
        for(int i = 1; i <= k; ++ i){
            if(a[i].dur <= m){
                m -= a[i].dur;
            }
        }
    }
    return 0;
}