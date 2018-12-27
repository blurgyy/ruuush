#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200010;
const int rightend = 2000000000;

int n, h;
int l[maxn], r[maxn];
int a[maxn];
ll pref[maxn];

template<class T>
int bs(T arr[], T e, int left, int right){//lower_bound
    if(left >= right)return right;
    int mid = left + (right - left) / 2;
    if(e <= arr[mid])return bs(arr, e, left, mid);
    return bs(arr, e, mid + 1, right);
}

int in_flow(int pos){//0:left point; 1:inside 2:right point; 3:outside
    int pl = bs(l, pos, 1, n);
    int pr = bs(r, pos, 1, n);
    if(l[pl] == pos)return 0;
    if(l[pr] < pos && pos < r[pr])return 1;
    if(r[pr] == pos)return 2;
    if(r[pl-1] < pos && l[pl] > pos)return 3;
}

int sum(int left, int right){
    int status = in_flow(right);
    int pos1, pos2;
    int ret = 0;
    pos1 = bs(l, left, 1, n) - 1;
    if(status == 0){
        pos2 = bs(l, right, 1, n) - 1;
    }
    else if(status == 1){
        pos2 = bs(r, right, 1, n);
        ret += right - l[pos2--];
    }
    else if(status == 2){
        pos2 = bs(r, right, 1, n);
    }
    else if(status == 3){
        pos2 = bs(l, right, 1, n) - 1;
    }
    return ret + pref[pos2] - pref[pos1];
}

int height(int start, int pos){
    return h - (pos - start) + sum(start, pos);
}

int dist(int start, int left, int right){
    if(left >= right){
        return right - start;
    }
    int mid = left + (right - left) / 2;
    int curans = height(start, mid);
    if(curans <= 0)return dist(start, left, mid);
    return dist(start, mid + 1, right);
}

void init(){
    pref[0] = 0;
}

int main(){
    //freopen("out.out", "w", stdout);
    l[0] = -2;
    r[0] = -1;
    while(~scanf("%d%d", &n, &h)){
        init();
        for(int i = 1; i <= n; ++ i){
            scanf("%d%d", l + i, r + i);
            a[i] = r[i] - l[i];
            pref[i] = pref[i-1] + a[i];
        }
        n ++;
        l[n] = rightend + 1;
        r[n] = rightend + 2;
        int ans = -1;
        for(int i = 1; i <= n; ++ i){
            ans = max(ans, dist(l[i], l[i], rightend));
        }
        printf("%d\n", ans);
    }
    return 0;
}