#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int n;
int x[maxn];
int diff[maxn]; ///diff[i] = a[i] - a[i+2];

int main(){
    freopen("in.in", "r", stdin);
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", x + i);
        }
        for(int i = 1; i < n; ++ i){
            diff[i-1] = x[i-1] - x[i];
        }
        for(int i = 2; i < n; ++ i){
            diff[i] += diff[i-2];
        }

        int maxx = -inf;
        bool aux = true;
        for(int i = 2; i < n; i += 2){
            maxx = max(maxx, diff[i]);
        }
        if(x[0] - maxx < 0){
            aux = false;
            printf("0\n");
            continue;
        }
        int tmp = x[0] - maxx;
        maxx = -inf;
        for(int i = 3; i < n; i += 2){
            maxx = max(maxx, diff[i]);
        }
        if(min(x[0], x[1]) < maxx){
            aux = false;
        }
        if(aux){
            printf("%d\n", min(tmp, min(x[0], x[1]) - maxx));
        }
    }
    return 0;
}