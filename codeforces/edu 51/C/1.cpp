#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

struct nOde{
    int v;
    int pos;
}st[maxn];
int n;
int cnt[maxn];
bool ans[maxn];
int cnta, cntb;

bool operator< (nOde a, nOde b){
    return cnt[a.v] == cnt[b.v] ? a.v < b.v : cnt[a.v] < cnt[b.v];
}

int main(){
    while(~scanf("%d", &n)){
        memset(cnt, 0, sizeof(cnt));
        cnta = cntb = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d", &st[i].v);
            cnt[st[i].v] ++;
            st[i].pos = i;
        }
        sort(st, st + n);
        for(int i = 0; i < n; ++ i){
            if(cnt[st[i].v] == 1){
                if(cnta <= cntb){
                    cnta ++;
                    ans[st[i].pos] = false;
                }
                else {
                    cntb ++;
                    ans[st[i].pos] = true;
                }
            }
            else if(cnt[st[i].v] == 2){
                cnta ++;
                cntb ++;
                ans[st[i++].pos] = true;
                ans[st[i].pos] = false;
            }
            else if(cnt[st[i].v] == 3){
                if(cnta == cntb){
                    ans[st[i].pos] = false;
                    ans[st[++i].pos] = false;
                    ans[st[++i].pos] = false;
                }
                if(cnta < cntb){
                    cnta ++;
                    ans[st[i].pos] = false;
                    ans[st[++i].pos] = true;
                    ans[st[++i].pos] = true;
                }
                else {
                    cntb ++;
                    ans[st[i].pos] = true;
                    ans[st[++i].pos] = false;
                    ans[st[++i].pos] = false;
                }
            }
            else {
                if(cnta == cntb)continue;
                if(cnta < cntb){
                    cnta ++;
                    ans[st[i].pos] = false;
                    while(i < n && st[i+1].v == st[i].v){
                        ans[st[++i].pos] = true;
                        cntb ++;
                    }
                }
                else {
                    cntb ++;
                    ans[st[i].pos] = true;
                    while(i < n && st[i+1].v == st[i].v){
                        ans[st[++i].pos] = false;
                        cnta ++;
                    }
                }
            }
        }
        if(cnta != cntb){
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        for(int i = 0; i < n; ++ i){
            if(ans[i]){
                printf("B");
            }
            else {
                printf("A");
            }
        }
        printf("\n");
    }
    return 0;
}