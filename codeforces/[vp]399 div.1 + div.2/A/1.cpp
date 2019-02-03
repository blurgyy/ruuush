#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int n;
int a[maxn];

int main(){
    // while(~scanf("%d", &n)){
    scanf("%d", &n);{
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        sort(a, a + n);
        int maxx = a[n-1], minx = a[0];
        int cnt = 0;
        for(int i = 0; i < n; ++ i){
            if(a[i] != maxx && a[i] != minx){
                cnt ++;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}