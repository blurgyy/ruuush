///while for int true false return push_back make_pair printf
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n, a[maxn], cnt[maxn];
pair<int, int> rec[maxn];
int p1, p2, pr;

void init(){
    p1 = p2 = pr = 0;
    memset(rec, 0, sizeof(rec));
    memset(cnt, 0, sizeof(cnt));
}

void out(int arr[], int n){
    for(int i = 0; i < n; ++ i)
        printf("%d%c", arr[i], " \n"[i == n-1]);
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n)){
        init();
        for(int i = 0; i < n; ++ i)
            scanf("%d", a + i);
        for(int i = 1; i < n; ++ i){
            if(a[i-1] < a[i])
                cnt[i] = cnt[i-1] + 1;
            else cnt[i-1] = -1;
        }
        cnt[n] = -1;
        out(cnt, n+1);
        int prev = 0;
        for(int i = 0; i <= n; ++ i)
            if(cnt[i] == -1){
                rec[pr++] = make_pair(i - prev - 1, prev);
                prev = i;
            }
        sort(rec, rec + pr);
        printf("%d\n", a[rec[pr-1].second]);
    }
    return 0;
}