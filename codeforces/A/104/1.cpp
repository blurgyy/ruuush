#include<bits/stdc++.h>
using namespace std;

int n, ans[30] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 15, 4, 0, 0, 0, 0, 0};

int main(){
    while(~scanf("%d", &n))
        printf("%d\n", ans[n]);
    return 0;
}