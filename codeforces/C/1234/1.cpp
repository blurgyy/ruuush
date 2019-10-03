#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 200010;

int T, n;
char s[2][maxn];

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%s%s", &n, s[0]+1, s[1]+1);
        bool ans = true;
        int pos = 1;
        for(int i = n; i; -- i){
            if(s[pos][i] - '0' > 2){
                pos = 1 - pos;
                if(s[pos][i] - '0' <= 2){
                    ans = false;
                    break;
                }
            }
        }
        ans = ans && pos==0;
        if(ans){
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    return 0;
}
