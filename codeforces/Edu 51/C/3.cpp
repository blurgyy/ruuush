#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

struct nOde{
    int v;
    int pos;
}st[maxn];
int n;
int side;
int cnt[maxn];
int ans[maxn];
int cnts[2];

bool operator< (nOde a, nOde b){
    return cnt[a.v] == cnt[b.v] ? a.v < b.v : cnt[a.v] < cnt[b.v];
}

int main(){
    while(~scanf("%d", &n)){
        memset(cnt, 0, sizeof(cnt));
        memset(cnts, 0, sizeof(cnts));
        memset(ans, 0, sizeof(ans));
        side = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d", &st[i].v);
            cnt[st[i].v] ++;
            st[i].pos = i;
        }
        sort(st, st + n);
        int tmp;
        for(int i = 0; i < n; ++ i){
            if(cnt[st[i].v] == 1){
                ans[st[i].pos] = side;
                cnts[side] ++;
                side = 1 - side;
            }
            else if(cnt[st[i].v] == 2){
                continue;
            }
            else {
                if(cnts[0] == cnts[1]){
                    ans[st[i].pos] = tmp;
                }
                else if(cnts[0] < cnts[1]){
                    ans[st[i].pos] = 0;
                    cnts[0] ++;
                    tmp = 1;
                }
                else {
                    ans[st[i].pos] = 1;
                    cnts[1] ++;
                    tmp = 0;
                }
            }
        }
        //printf("%d %d\n", cnts[0], cnts[1]);
        if(cnts[0] != cnts[1]){
            printf("NO\n");
        }
        else {
            printf("YES\n");
            for(int i = 0; i < n; ++ i){
                if(ans[i]){
                    printf("A");
                }
                else {
                    printf("B");
                }
            }
            printf("\n");
        }
    }
    return 0;
}