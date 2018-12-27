#include<bits/stdc++.h>
using namespace std;

int a[30];
bool rec[10];

int main(){
    int cnt = 0;
    for(int i = 1; i < 25; ++ i)
        scanf("%d", a + i);
    for(int j = 0; j < 6; ++ j){
        int i =  4 * j + 1;
        if(a[i] == a[i+1] && a[i+1] == a[i+2] && a[i+2] == a[i+3]){
            rec[j] = true;
            ++ cnt;
        }
    }
    if(cnt != 2){
        printf("NO\n");
        return 0;
    }
    if(rec[0] && rec[2] || rec[1] && rec[5] || rec[3] && rec[4]){
        if(rec[0] && rec[2]){
            if(a[13] == a[14] && a[5] == a[6] && a[17] == a[18] && a[21] == a[22]){
                if(a[15] == a[16] && a[7] == a[8] && a[19] == a[20] && a[23] == a[24]){
                    if(a[13] == a[7] && a[5] == a[19] && a[17] == a[23] && a[21] == a[15] || a[13] == a[24] && a[5] == a[15] && a[7] == a[17] && a[19] == a[22])
                        printf("YES\n");
                    else printf("NO\n");
                }
            }
        }
        else if(rec[1] && rec[5]){
            if(a[3] == a[4] && a[17] == a[19] && a[9] == a[10] && a[14] == a[16]){
                if(a[1] == a[2] && a[18] == a[20] && a[11] == a[12] && a[13] == a[15]){
                    if(a[3] == a[18] && a[17] == a[11] && a[9] == a[13] && a[14] == a[1] || a[3] == a[13] && a[14] == a[11] && a[9] == a[18] && a[19] == a[1])
                        printf("YES\n");
                    else printf("NO\n");
                }
            }
        }
        else {
            if(a[1] == a[3] && a[5] == a[7] && a[9] == a[11] && a[22] == a[24]){
                if(a[2] == a[4] && a[6] == a[8] && a[10] == a[12] && a[21] == a[23]){
                    if(a[1] == a[6] && a[5] == a[10] && a[9] == a[21] && a[22] == a[2] || a[1] == a[21] && a[22] == a[10] && a[9] == a[6] && a[5] == a[2])
                        printf("YES\n");
                    else printf("NO");
                }
            }
        }
    }
    else printf("NO\n");
    return 0;
}