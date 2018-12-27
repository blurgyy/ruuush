#include<bits/stdc++.h>
using namespace std;
const int maxn = 300;

char a[maxn], b[maxn];
char ans[maxn];
int p, cnt[maxn];

void init(){
    memset(ans, 0, sizeof(ans));
    p = 0;
    memeset(cnt, 0, sizeof(cnt));
}

bool cmp(char x, char y){
    return x > y;
}

bool check(char* a, char* b, int len){
    for(int i = 0; i < len; ++ i)
        if(a[i] >= b[i])return false;
    return true;
}

int main(){
    while(~scanf("%s%s", a, b)){
        int len = strlen(a);
        if(len < strlen(b)){
            sort(a, a + len, cmp);
            printf("%s\n", a);
            continue;
        }
        /*int test[] = {0, 1, 2, 3, 4, 5};
        do{
            for(int i = 0; i < 6; ++ i)
                printf("%d%c", test[i], " \n"[i == 5]);
        }
        while(next_permutation(test, test + 6));*/
        init();
        for(int i = 0; i < len; ++ i)
            cnt[a[i]] ++;
        char now;
        for(int i = 0; i < len; ++ i){
            for(now = '0'; now <= '9'; ++ now)
                if(cnt[now])break;
            char prev;
            for(char j = now; j <= '9'; ++ j){
                if(!cnt[j])continue;
                prev = ans[i];
                ans[i] = j;
                if(!check(ans, b, i+1)){
                    if(prev)ans[i] = prev;
                    else{
                        for(int l = 2; l < i+1; ++ l){
                            while(!check(ans, b, i+1))
                                if(!prev_permutation(ans+i+1-l,))
                        }
                    }
                    break;
                }

            }
        }
    }
    return 0;
}