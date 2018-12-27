#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 10010;

int T, n, k;
int pf[2][maxn];    ///0 for n, 1 for k
int cnt[2][maxn];   ///0 for n, 1 for k
int pn, pk;

void proc(){
    int bound = sqrt(n) + 2;
    for(int i = 2; i < bound; ++ i){
        if(n == 1)break;
        if(n % i == 0){
            pf[0][pn] = i;
            while(n % i == 0){
                cnt[0][pn] ++;
                n /= i;
            }
            pn ++;
        }
    }
    if(n != 1){
        pf[0][pn] = n;
        cnt[0][pn] ++;
        pn ++;
    }
    bound = sqrt(k) + 2;
    for(int i = 2; i < bound; ++ i){
        if(k == 1)break;
        if(k % i == 0){
            pf[1][pk] = i;
            while(k % i == 0){
                cnt[1][pk] ++;
                k /= i;
            }
            pk ++;
        }
    }
    if(k != 1){
        pf[1][pk] = k;
        cnt[1][pk] ++;
        pk ++;
    }
}

void out(int arr[], int end){
    for(int i = 0; i < end; ++ i){
        printf("%d%c", arr[i], " \n"[i == end-1]);
    }
}

void de8g(){
    out(pf[0], pn);
    out(cnt[0], pn);
    printf("\n");
    out(pf[1], pk);
    out(cnt[1], pk);
    printf("\n");
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%d", &n, &k);
        if(n == 1){
            printf("0\n");
        }
        proc();
        //de8g();
        bool ans = true;
        int mx = -1;
        for(int i = 0; i < pn; ++ i){
            int now = pf[0][i];
            if(k % now != 0){
                ans = false;
                break;
            }
            for(int pos = 0; pos < pk; ++ pos){
                if(pf[1][pos] == now){
                    int tmp = cnt[0][i] / cnt[1][pos];
                    if(cnt[0][i] % cnt[1][pos])
                        tmp ++;
                    mx = max(mx, tmp);
                }
            }
        }
        if(ans){
            printf("%d\n", mx);
        }
        else {
            printf("unbounded\n");
        }
    }
    return 0;
}