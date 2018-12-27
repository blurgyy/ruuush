#include<bits/stdc++.h>
using namespace std;
const int maxn = 30;

int n, a[maxn], arr[maxn];

int bs(int e, int arr[], int left = 0, int right = n){
    if(left >= right)return right;
    int mid((left + right) >> 1);
    if(e <= arr[mid])return bs(e, arr, left, mid);
    return bs(e, arr, mid + 1, right);
}

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            arr[i] = a[i];
        }
        sort(arr, arr + n);
        for(int i = 0; i < n; ++ i){
            int pos = bs(a[i], arr);
            if(pos == n-1)pos = -1;
            ++ pos;
            printf("%d%c", arr[pos]," \n"[i == n-1]);
        }
    }
    return 0;
}