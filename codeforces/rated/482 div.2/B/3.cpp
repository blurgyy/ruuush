#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;

int n;
char a[maxn], b[maxn], c[maxn];
int cnt[3][52];

int idx(char ch){
    if(ch >= 'a' && ch <= 'z')
        return ch - 'a';
    return ch - 'A' + 26;
}

int main(){
    while(~scanf("%d", &n)){
        scanf("%s%s%s", a, b, c);
        int len = strlen(a);
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < len; ++ i){
            cnt[0][idx(a[i])] ++;
            cnt[1][idx(b[i])] ++;
            cnt[2][idx(c[i])] ++;
        }
        sort(cnt[0], cnt[0] + 52);
        sort(cnt[1], cnt[1] + 52);
        sort(cnt[2], cnt[2] + 52);
        int ans1 = -1, ans2 = -1, ans3 = -1;
        ans1 = min(cnt[0][51] + n, len);
        ans2 = min(cnt[1][51] + n, len);
        ans3 = min(cnt[2][51] + n, len);
        if(n == 1){
            if(cnt[0][51] == len)
                ans1 = len - 1;
            if(cnt[1][51] == len)
                ans2 = len - 1;
            if(cnt[2][51] == len)
                ans3 = len - 1;
        }
        if(ans1 > ans2 && ans1 > ans3){
            printf("Kuro\n");
            continue;
        }
        if(ans2 > ans1 && ans2 > ans3){
            printf("Shiro\n");
            continue;
        }
        if(ans3 > ans1 && ans3 > ans2){
            printf("Katie\n");
            continue;
        }
        printf("Draw\n");
    }
    return 0;
}