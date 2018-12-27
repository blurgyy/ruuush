#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
ll a[maxn], pref[maxn];

int bs(ll e, ll arr[], int left = 0, int right = n-1){
    if(left >= right)return right;
    int mid((left + right) >> 1);
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n)){
        scanf("%I64d", a);
        pref[0] = a[0];
        for(int i = 1; i < n; ++ i){
            scanf("%I64d", a + i);
            pref[i] = pref[i-1] + a[i];
        }
        for(int i = 0; i < n; ++ i)
            printf("%lld ", pref[i]);
        printf("\n");
        if(pref[n-1] & 1){
            printf("NO\n");
            continue;
        }
        ll sum = pref[n-1] >> 1;
        int pos = bs(sum, pref);
        if(pref[pos] == sum){
            printf("YES\n");
            continue;
        }
        //pos --;
        printf("pref[%d] = %I64d\n", pos, pref[pos]);
        bool ans = false;
        for(int j = pos; j < n; ++ j){
            for(int i = j; i < n; ++ i){
                //printf("%lld, %lld\n", sum - pref[pos], a[i] - a[pos]);
                /*if(sum - pref[pos] == a[i] - a[pos]){
                    //printf("%lld, %lld - %lld = %lld\n", sum - pref[pos], a[i], a[pos], a[i] - a[pos]);
                    //printf("%d!!\n", sum - pref[pos] == a[i] - a[pos]);
                    ans = true;
                    break;
                }*/
                if(sum - pref[pos-1]){

                }
            }
        }
        if(ans)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

/**

10
9 6 8 2 5 5 8 9 2 2


100
9 9 72 55 14 8 55 58 35 67 3 18 73 92 41 49 15 60 18 66 9 26 97 47 43 88 71 97 19 34 48 96 79 53 8 24 69 49 12 23 77 12 21 88 66 9 29 13 61 69 54 77 41 13 4 68 37 74 7 6 29 76 55 72 89 4 78 27 29 82 18 83 12 4 32 69 89 85 66 13 92 54 38 5 26 56 17 55 29 4 17 39 29 94 3 67 85 98 21 14

*/