#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int T;
int cnts, cntn;
int ans;
char s[maxn];

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%s", s);
        int len = strlen(s);
        ans = cnts = cntn = 0;
        for(int i = 0; i < len; ++ i){
            if(s[i] == '*'){
                cnts ++;
            }
            else {
                cntn ++;
            }
        }
        //printf("cnts = %d, cntn = %d\n", cnts, cntn);
        if(cnts == 0){
            printf("0\n");
            continue;
        }

        int num = 0, id = 1;
        if(cntn <= cnts){
            ans = cnts + 1 - cntn;
            num = ans;
            //printf("ans = %d\n", ans);
            cntn = cnts + 1;
        }
        if(s[len-1] != '*'){    ///is a number
            //printf("s = %s\n", s);
            ans += 1;
            for(int i = 0; i < len; ++ i){
                if(s[i] == '*'){
                    swap(s[i], s[len-1]);
                    break;
                }
            }
        }
        for(int i = 0; i < len; ++ i){
            if(s[i] == '*'){
                if(num <= id){
                    //printf("num = %d, id = %d\n", num, id);
                    s[i] = '1';
                    num ++;
                    ans ++;
                }
                id ++;
            }
            else {
                num ++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}