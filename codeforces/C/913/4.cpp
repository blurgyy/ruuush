#include<bits/stdc++.h>
using namespace std;
const int maxn = 150;

char a[maxn], b[maxn];
char ans[maxn];
map<char, int> cnt;
bool esc = false;

bool cmp(char x, char y){
    return x > y;
}

bool check(char* a, char* b, int len){
    for(int i = 0; i < len; ++ i){
        if(a[i] > b[i])return false;
        if(a[i] < b[i])return true;
    }
    return true;
}

void dfs(int pos = 0){
    for(char i = '9'; i >= '0'; -- i){
        //printf("%c:%d\n", i->first, i->second);
        printf("cnt[%c] = %d\n", i, cnt[i]);
        if(cnt[i]){
            cnt[i] --;
            //cnt[ans[pos]] ++;
            //ans[pos] = 0;
            ans[pos] = i;
            printf("check(%s, %s, %d) = %d\n", ans, b, pos+1, check(ans, b, pos + 1));
            if(check(ans, b, pos+1)){
                //printf("if\n");
                dfs(pos + 1);
                //printf("%d: %s\n    %s\n", pos, ans, b);
            }
            else{
                //printf("else\n");
                cnt[i] ++;
                ans[pos] = 0;
                //esc = true;
            }
        }
        //if(esc)return;
    }
}

int main(){
    while(~scanf("%s%s", a, b)){
        cnt.clear();
        esc = false;
        memset(ans, 0, sizeof(ans));
        int len = strlen(a);
        if(len < strlen(b)){
            sort(a, a + len, cmp);
            printf("%s\n", a);
            continue;
        }
        for(int i = 0; i < len; ++ i)
            cnt[a[i]] ++;
        dfs();
        if(esc){
            printf("%s", ans);
            for(int i = '9'; i >= '0'; -- i)
                for(int j = 0; j < cnt[i]; ++ j)
                    printf("%c", i);
            printf("\n");
        }
        else printf("%s\n", ans);
    }
    return 0;
}

/**

123456789123456789
276193619183618162

15778899
98715689

*/