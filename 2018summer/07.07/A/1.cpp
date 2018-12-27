/// Nope
///!!! note that if(n == 1) then the answer should be **ZERO**
#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;

int T;
int n, k, pnp, pkp;
int pn[maxn], pk[maxn];
int cntn[maxn], cntk[maxn];

int bs(int arr[], int e, int left, int right){
    if(left >= right)return right;
    int mid = left + right >> 1;
    if(e <= arr[mid])return bs(arr, e, left, mid);
    return bs(arr, e, mid + 1, right);
}

void proc(){
    int bound = sqrt(n) + 1;
    for(int i = 2; i <= bound; ++ i){
        if(n == 1)break;
        if(n % i == 0){
            pn[pnp] = i;
            while(n % i == 0){
                n /= i;
                cntn[pnp] ++;
            }
            pnp ++;
        }
    }
    bound = sqrt(k) + 1;
    for(int i = 2; i <= bound; ++ i){
        if(k == 1)break;
        if(k % i == 0){
            pk[pkp] = i;
            //printf("pk[%d] = %d, i = %d\n", pkp, pk[pkp], i);
            while(k % i == 0){
                k /= i;
                cntk[pkp] ++;
            }
            pkp ++;
            //printf("k = %d\n", k);
        }
    }
    if(n != 1){
        pn[pnp] = n;
        cntn[pnp ++] ++;
    }
    if(k != 1){
        pk[pkp] = k;
        cntk[pkp ++] ++;
    }
}

void init(){
    memset(pn, 0, sizeof(pn));
    memset(pk, 0, sizeof(pk));
    memset(cntn, 0, sizeof(cntn));
    memset(cntk, 0, sizeof(cntk));
    pnp = pkp = 0;
}

int main(){
    scanf("%d", &T);
    while(T --){
        init();
        scanf("%d%d", &n, &k);
        proc();
/*
        printf("pn:\t");
        for(int i = 0; i < pnp; ++ i){
            printf("%d(%d) ", pn[i], cntn[i]);
        }
        printf("\n");
        printf("pk:\t");
        for(int i = 0; i < pkp; ++ i){
            printf("%d(%d) ", pk[i], cntk[i]);
        }
        printf("\n");
*/
        bool ans = true;
        int mx = 0;
        for(int i = 0; i < pnp; ++ i){
            int pos = bs(pk, pn[i], 0, pkp - 1);
            if(pk[pos] != pn[i]){
                //printf("%d != %d\n", pk[pos], pn[i]);
                ans = false;
            }
            double tmp = cntn[i] * 1.0 / (cntk[pos] * 1.0);
            mx = max(mx, (int)ceil(tmp));
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