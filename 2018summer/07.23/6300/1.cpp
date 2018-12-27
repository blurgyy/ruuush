#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 100010;
const int _ = 1000000010;

struct cord{
    ll x, y;
    int id;
}a[maxn];
int T, n;

bool operator< (cord a, cord b){
    return b.x * a.y < a.x * b.y;
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        n *= 3;
        for(int i = 0; i < n; ++ i){
            scanf("%lld%lld", &a[i].x, &a[i].y);
            a[i].x += _;
            a[i].y += _;
            a[i].id = i + 1;
        }
        sort(a, a + n);
        for(int i = 0; i < n; i += 3){
            printf("%d %d %d\n", a[i].id, a[i+1].id, a[i+2].id);
        }
    }
    return 0;
}

/**

1
1 2
2 3
3 5

*/