#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 20010;

int n, p;
int a[maxn];
ll s, pref[maxn];

int index(int e, int left = 0, int right = n-1){
    //printf("left = %d, right = %d\n", left, right);
    if(left >= right)return right;
    int mid = left + right + 1 >> 1;
    if(e < a[mid])return index(e, left, mid - 1);
    return index(e, mid, right);
}

bool check(int wgh){
    int idx = index(wgh);
    ll ans = pref[n-1] - pref[idx] - (n-1-idx)*wgh;
    printf("ans = %lld\n", ans);
    return ans <= s;
}

int bs(int left = a[0], int right = a[n-1]){
    if(left >= right)return right;
    int mid = left + right >> 1;
    printf("left = %d, right = %d\n", left, right);
    if(check(mid))return bs(left, mid);
    return bs(mid + 1, right);
}

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i)
            scanf("%d", a + i);
        sort(a, a + n);
        for(int i = 0; i < n; ++ i)
            printf("%d%c", a[i], " \n"[i == n-1]);
        /*int val;
        while(~scanf("%d", &val))
            printf("a[%d] = %d\n", index(val), val);*/
        memset(pref, 0, sizeof(pref));
        pref[0] = a[0];
        for(int i = 1; i < n; ++ i)
            pref[i] = pref[i-1] + a[i];
        scanf("%d%lld", &p, &s);
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