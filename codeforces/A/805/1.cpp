#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int l, r;

int main(){
    while(~scanf("%d%d", &l, &r)){
        int diff = r - l;
        if(!diff)printf("%d\n", l);
        else printf("2\n");
    }
    return 0;
}