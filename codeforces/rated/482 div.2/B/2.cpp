#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;

int n;
char ku[maxn], sh[maxn], ka[maxn];
int cnt[3][52];

int idx(char ch){
    if(ch >= 'a' && ch <= 'z')
        return ch - 'a';
    return ch - 'A' + 26;
}

int main(){
    while(~scanf("%d", &n)){
        scanf("%s%s%s", ku, sh, ka);
        int len = strlen(ku);
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < len; ++ i){
            cnt[0][idx(ku[i])] ++;
            cnt[1][idx(sh[i])] ++;
            cnt[2][idx(ka[i])] ++;
        }
        sort(cnt[0], cnt[0] + 52);
        sort(cnt[1], cnt[1] + 52);
        sort(cnt[2], cnt[2] + 52);
        int mx1 = -1, mx2 = -1, mx3 = -1;
        for(int i = 0; i < 52; ++ i){
            if(cnt[0][i] + n <= len)
                mx1 = max(mx1, cnt[0][i] + n);
            else {
                mx1 = max(mx1, (cnt[0][i] + n % len) % 2 == 1 ? len - 1 : len);
            }
            if(cnt[1][i] + n <= len)
                mx2 = max(mx2, cnt[1][i] + n);
            else {
                mx2 = max(mx2, (cnt[1][i] + n % len) % 2 == 1 ? len - 1 : len);
            }
            if(cnt[2][i] + n <= len)
                mx3 = max(mx3, cnt[2][i] + n);
            else {
                mx3 = max(mx3, (cnt[2][i] + n % len) % 2 == 1 ? len - 1 : len);
            }
        }
        if(mx1 > mx2 && mx1 > mx3){
            printf("Kuro\n");
            continue;
        }
        if(mx2 > mx1 && mx2 > mx3){
            printf("Shiro\n");
            continue;
        }
        if(mx3 > mx1 && mx3 > mx2){
            printf("Katie\n");
            continue;
        }
        printf("Draw\n");
    }
    return 0;
}