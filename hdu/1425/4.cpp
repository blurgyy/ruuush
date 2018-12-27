//#include<bits/stdc++.h>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 1000010;

int n, m;
int a[maxn], as[maxn];

int main(){
    while(~scanf("%d%d", &n, &m)){
        memset(as, 0, sizeof(as));
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            ++ as[a[i] + 500000];
        }
        for(int i = maxn-1; i >= 0; -- i)
            while(as[i]-- > 0 && m > 0)
                printf("%d%c", i - 500000, " \n"[--m == 0]);
    }
    return 0;
}