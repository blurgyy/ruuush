#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const size_t maxn = 200010;
const int inf = 0x3f3f3f3f;

int n, m, k;
int a[maxn];
struct node{
    int id, val;
    bool operator< (const node &rhs){return val == rhs.val ? id < rhs.id : val < rhs.val;}
}arr[maxn];

int main(){
    while(~scanf("%d%d%d", &n, &m, &k)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            arr[i].id = i;
            arr[i].val = a[i];
        }
        sort(arr, arr + n);
        ll ans = 0;
        int lim = m * k;
        for(int i = n-1; i >= n-lim; -- i){
            ans += arr[i].val;
            a[arr[i].id] = inf;
        }
        printf("%lld\n", ans);
        for(int i = 0, cnt = 0, output = 0; i < n-1; ++ i){
            if(a[i] == inf){
                cnt ++;
            }
            if(cnt == m){
                printf("%d ", i+1);
                cnt = 0;
                output ++;
            }
            if(output == k-1){
                break;
            }
        }
        printf("\n");
    }
    return 0;
}
