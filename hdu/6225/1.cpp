#include<bits/stdc++.h>
using namespace std;

int n;
int a, b, c, d;

int main(){
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    scanf("%d", &n);
    while(n--){
        scanf("%d%d%d%d", &a, &b, &c, &d);
        printf("%d\n", a + b + c + d);
    }
    return 0;
}
