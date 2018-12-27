#include <bits/stdc++.h>
using namespace std;
const int maxn = 60;

int T, n, m;
int a[maxn], b[maxn];
int suma, sumb;
int minx, maxx;

int main(){
    scanf("%d", &T);
    while(T --){
        suma = sumb = 0;
        minx = 101;
        maxx = -1;
        scanf("%d%d", &n, &m);
        for(int i = 1; i < n; ++ i){
            scanf("%d", a + i);
            suma += a[i];
        }
        for(int i = 1; i <= m; ++ i){
            scanf("%d", b + i);
            sumb += b[i];
        }
        double avga = 1.0*suma/(n-1);   //after average for a
        double avgb = 1.0*sumb/m;       //before average for b
        for(int i = 0; i <= 100; ++ i){
            double tmpa = 1.0 * (suma + i) / n;
            double tmpb = 1.0 * (sumb + i) / (m + 1);
            if(avga > tmpa && tmpb > avgb){
                minx = min(minx, i);
                maxx = max(maxx, i);
            }
        }
        printf("%d %d\n", minx, maxx);
    }
    return 0;
}