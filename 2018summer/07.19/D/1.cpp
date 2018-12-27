#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int n;
int a[maxn], seq[maxn];
int minx, pos;
bool aux;

void expand(int pos){
    aux = true;
    minx = inf;
    for(int i = pos - 1; i >= 0; -- i){
        seq[i] = a[i+1] - seq[i+1];
        //printf("seq[%d] = %d\n", i, seq[i]);
        if(seq[i] < 0){
            aux = false;
            return;
        }
        if((pos - i) & 1){
            minx = min(minx, seq[i]);
        }
    }
    for(int i = pos + 1; i <= n; ++ i){
        seq[i] = a[i] - seq[i-1];
        //printf("seq[%d] = %d\n", i, seq[i]);
        if(seq[i] < 0){
            aux = false;
            return;
        }
        if((i - pos) & 1){
            minx = min(minx, seq[i]);
        }
    }
    /*
    printf("in expand:\n");
    for(int i = 0; i <= n; ++ i){
        printf("%d ", seq[i]);
    }
    printf("\n");
    */
}

int main(){
    while(~scanf("%d", &n)){
        minx = inf;
        pos = -1;

        for(int i = 1; i <= n; ++ i){
            scanf("%d", a + i);
            if(minx > a[i]){
                minx = a[i];
                pos = i;
            }
        }
        //printf("minx = %d, pos = %d\n", minx, pos);
        seq[pos] = 0;
        expand(pos);
        if(!aux){
            seq[pos-1] = 0;
            expand(pos-1);
        }
        if(!aux){
            printf("0\n");
        }
        else {
            printf("%d\n", minx + 1);
        }
    }
    return 0;
}