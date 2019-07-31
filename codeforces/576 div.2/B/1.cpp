#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

ll h, l;

int main(){
    while(~scanf("%lld%lld", &h, &l)){
        printf("%f\n", 1.0 * (h*h + l*l) / (2.0 * h) - h);
    }
    return 0;
}
