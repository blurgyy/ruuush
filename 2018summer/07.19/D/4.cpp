#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000010;

int n;
int a[maxn], b[maxn];

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
        }
        b[0] = 0;
        for(int i = 1; i <= n; ++ i){
            b[i] = a[i-1] - b[i-1];
        }
        for(int i = 0; i <= n; ++ i){
            printf("%d%c", b[i], " \n"[i == n]);
        }
        int mine = 
    }
    return 0;
}