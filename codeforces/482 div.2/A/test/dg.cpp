#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;

int main(){
    srand(time(NULL));
    n = rand();
    m = rand();
    printf("%lld\n", n * n * m);
    return 0;
}