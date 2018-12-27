#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int mod = 256;

int reg;
struct Node{
    int id;
    int v, k;
    bool rec[mod];
}op[maxn];
int T;
int n;
char s[10];

void input(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i){
        scanf("%s", s);
        if(!strcmp(s, "add")){
            op[i].id = 1;
            scanf("%d", &op[i].v);
        }
        else if(!strcmp(s, "beq")){
            op[i].id = 2;
            scanf("%d%d", &op[i].v, &op[i].k);
        }
        else if(!strcmp(s, "bne")){
            op[i].id = 3;
            scanf("%d%d", &op[i].v, &op[i].k);
        }
        else if(!strcmp(s, "blt")){
            op[i].id = 4;
            scanf("%d%d", &op[i].v, &op[i].k);
        }
        else if(!strcmp(s, "bgt")){
            op[i].id = 5;
            scanf("%d%d", &op[i].v, &op[i].k);
        }
    }
}

int main(){
    scanf("%d", &T);
    while(T --){
        input();
        for(int i = 1; i <= n; ++ i){
            memset(op[i].rec, 0, sizeof(op[i].rec));
        }
        reg = 0;
        int now = 1;
        bool ans = true;
        while(true){
            if(now > n){
                ans = true;
                break;
            }
            if(op[now].rec[reg]){
                //printf("now = %d, reg = %d\n", now, reg);
                ans = false;
                break;
            }
            op[now].rec[reg] = true;
            if(op[now].id == 1){
                reg = (reg + op[now].v) % mod;
                now ++;
            }
            else if(op[now].id == 2){
                if(reg == op[now].v){
                    now = op[now].k;
                }
                else {
                    now ++;
                }
            }
            else if(op[now].id == 3){
                if(reg != op[now].v){
                    now = op[now].k;
                }
                else {
                    now ++;
                }
            }
            else if(op[now].id == 4){
                if(reg < op[now].v){
                    now = op[now].k;
                }
                else {
                    now ++;
                }
            }
            else if(op[now].id == 5){
                if(reg > op[now].v){
                    now = op[now].k;
                }
                else {
                    now ++;
                }
            }
        }
        if(ans){
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}