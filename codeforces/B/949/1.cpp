#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, x;
int q;

int main(){
	while(~scanf("%I64d%d", &n, &q)){
        while(q--){
            scanf("%I64d", &x);
            while(!(x&1))
                x += (n - (x >> 1));
            printf("%I64d\n", (x + 1) >> 1);
        }
    }
    return 0;
}