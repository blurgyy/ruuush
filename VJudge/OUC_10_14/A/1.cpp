#include<bits/stdc++.h>
using namespace std;
const int maxn = 2010;

int n;
int x[maxn], y[maxn];
int all[maxn<<1], p;

int bs(int e, int left = 0, int right = p-1){
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(all[mid] < e)return bs(e, mid+1, right);
    return bs(e, left, mid);
}

int main(){
    while(~scanf("%d", &n)){
        p = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d", x + i);
            all[p++] = x[i];
        }
        for(int i = 0; i < n; ++ i){
            scanf("%d", y + i);
            all[p++] = y[i];
        }
        sort(all, all + p);
        int cnt = 0;
        for(int i = 0; i < n; ++ i)
            for(int j = 0; j < n; ++ j){
                int m = x[i] ^ y[j];
                if(all[bs(m)] == m)
                    ++ cnt;
            }
        //printf("cnt = %d\n", cnt);
        if(cnt&1)printf("Koyomi\n");
        else printf("Karen\n");
    }
    return 0;
}