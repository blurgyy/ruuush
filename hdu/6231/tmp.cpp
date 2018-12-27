#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int T, n, k, a[maxn], b[maxn];
ll m;

ll inline count(int val, int ub){   //@param
    ll ret = 0, cnt = (a[0] >= val);
    int f = 0, r = 1;
    while(r <= n){
        if(cnt >= ub){
            ret += n - r + 1;
            f ++;
            if(a[f-1] >= val)
                cnt --;
        }
        else {
            r ++;
            if(a[r-1] >= val)
                cnt ++;
        }
    }
    return ret;
}

bool check(int val){
    return count(val + 1, k) >= m;
}

int bs(int arr[], int left, int right){
    if(left >= right)return arr[right];
    int mid((left + right) >> 1);
    if(check(arr[mid]))return bs(arr, mid + 1, right);
    return bs(arr, left, mid);
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d%d%lld", &n, &k, &m);
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            b[i] = a[i];
        }
        sort(b, b + n);
        printf("%d\n", bs(b, 0, n-1));
    }
    return 0;
}