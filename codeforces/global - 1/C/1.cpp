#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxq = 1010;

int q, a;
int pow2[50];
int ans[50];

void init(){
    pow2[0] = 1;
    for(int i = 1; i < 50; ++ i) pow2[i] = pow2[i-1] * 2;
    for(int i = 0; i < 50; ++ i) pow2[i] --;
    ans[1] = 1;
    ans[2] = 1;
    ans[3] = 5;
    ans[4] = 1;
    ans[5] = 21;
    ans[6] = 1;
    ans[7] = 85;
    ans[8] = 73;
    ans[9] = 341;
    ans[10] = 89;
    ans[11] = 1365;
    ans[12] = 1;
    ans[13] = 5461;
    ans[14] = 4681;
    ans[15] = 21845;
    ans[16] = 1;
    ans[17] = 87381;
    ans[18] = 1;
    ans[19] = 349525;
    ans[20] = 299593;
    ans[21] = 1398101;
    ans[22] = 178481;
    ans[23] = 5592405;
    ans[24] = 1082401;
    ans[25] = 22369621;
}

int main(){
    init();
    scanf("%d", &q);
    while(q --){
        scanf("%d", &a);
        for(int i = 2; i < 50; ++ i){
            if(pow2[i] == a){
                printf("%d\n", ans[i-1]);
                break;
            }
            if(pow2[i] > a){
                printf("%d\n", pow2[i]);
                break;
            }
        }
    }
    return 0;
}