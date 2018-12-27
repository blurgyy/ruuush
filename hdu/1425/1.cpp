///std::sort();

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000010;

int n, m;
int a[maxn];

int main(){
    while(~scanf("%d%d", &n, &m)){
        for(int i = 0; i < n; ++ i)
            scanf("%d", a + i);
        sort(a, a + n);
        for(int i = n-1; i >= n-m; -- i){
            printf("%d%c", a[i], " \n"[i == n-m]);
        }
    }
    return 0;
}