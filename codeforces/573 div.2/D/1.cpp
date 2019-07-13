#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100010;

int n;
int a[maxn];
int dist[maxn];

int main(){
    while(~scanf("%d", &n)){
        ll sum = 0, dsum = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d", a + i);
            sum += a[i];
        }
        sort(a, a + n);

        bool cslnb = false;
        int cnt = 0;
        for(int i = 1; i < n; ++ i){
            int add = a[i] - a[i-1] - 1;
            if(add < 0){
                add = 0;
                if(a[i] == 0){
                    cslnb = true;
                    break;
                }
                if(i > 1 && a[i-2] == a[i] - 1){
                    cslnb = true;
                    break;
                }
                cnt ++;
            }
            if(cnt == 2){
                cslnb = true;
                break;
            }
        }
        if(cslnb){
            printf("cslnb\n");
            continue;
        }

        dist[0] = 0;
        for(int i = 1; i < n; ++ i){
            dist[i] = min(dist[i-1]+1, a[i]);
            dsum += dist[i];
        }
        ll mov = sum - dsum;
        // printf("mov = %lld\n", mov);
        if(mov & 1){
            printf("sjfnb\n");
        }
        else {
            printf("cslnb\n");
        }
    }
    return 0;
}
