#include<bits/stdc++.h>
using namespace std;
const int maxn = 150;

char a[maxn], b[maxn], ans[maxn];
int len;
map<char, int> cnt;

void init(){
    cnt.clear();
    memset(ans, 0, sizeof(ans));
}

bool check(char* a, char* b, int len){
    for(int i = 0; i < len; ++ i){
        if(a[i] > b[i])return false;
        if(a[i] < b[i])return true;
    }
    return true;
}

bool cmp(char x, char y){
    return x > y;
}

bool dfs(int pos = 0){
    if(pos == len)return true;
    for(char i = '9'; i >= '0'; -- i){
        if(cnt[i] > 0){
            //printf("cnt[%c] = %d\n", i, cnt[i]);
            ans[pos] = i;
            if(check(ans, b, pos + 1)){
                cnt[i] --;
                if(dfs(pos + 1))return true;
                else cnt[i] ++;
            }
        }
    }
    return false;
}

int main(){
    while(~scanf("%s%s", a, b)){
        init();
        len = strlen(a);
        if(len < strlen(b)){
            sort(a, a + len, cmp);
            printf("%s\n", a);
            continue;
        }
        for(int i = 0; i < len; ++ i)
            cnt[a[i]] ++;
        dfs();
        printf("%s\n", ans);
    }
    return 0;
}