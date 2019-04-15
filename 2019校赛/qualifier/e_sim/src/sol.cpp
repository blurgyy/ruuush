#include <bits/stdc++.h>
#define div qwertyuikjhgfdfghjk
using namespace std;
typedef long long ll;
const int maxn = 200010;

int T;
vector<int> ans;
char inp[maxn], div[5];

bool isdigit(char ch){return ch >= '0' && ch <= '9';}
bool isdiv(char ch){return ch == div[0];}

char *strip(char *x){
    while(isdiv(*x)){
        x ++;
    }
    int len = strlen(x)-1;
    while(isdiv(x[len])) {
        x[len--] = 0;
    }
    return x;
}

int readN(char *x){
    ll ret = 0;
    for(int i = 0; i < 11 && x[i]; ++ i){
        if(!isdigit(x[i])){
            if(!isdiv(x[i])){
                return -1;
            }
            else {
                if(ret < 2147483648){
                    if(ret != 0 && *x == '0' || ret == 0 && *x == '0' && *(x+1) == '0') return -1;
                    return (int)ret;
                }
                else return -1;
            }
        }
        else {
            ret *= 10;
            ret += x[i] - '0';
            // printf("x[%d] = %c\n", i, x[i]);
        }
    }
    if(ret < 2147483648){
        if(ret != 0 && *x == '0' || ret == 0 && *x == '0' && *(x+1) == '0') return -1;
        return (int)ret;
    }
    else return -1;
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%s%s", inp, div);
        char *s = strip(inp);
        int len = strlen(s);
        if(len == 0){
            printf("0\n");
            continue;
        }
        else {
            ans.clear();
            bool flag = true;
            for(int i = 0; i < len; ++ i){
                if(!isdiv(s[i])){
                    if(!isdigit(s[i])){
                        flag = false;
                        break;
                    }
                    else {
                        int tmp = readN(s + i);
                        // printf("tmp = %d\n", tmp);
                        if(tmp == -1){
                            flag = false;
                            break;
                        }
                        else {
                            ans.push_back(tmp);
                            while(isdigit(s[i])){
                                i ++;
                            }
                        }
                    }
                }
            }
            if(flag){
                printf("%lu\n", ans.size());
                for(int i = 0; i < ans.size(); ++ i){
                    printf("%d\n", ans[i]);
                }
            }
            else {
                printf("bad dongdongqiang\n");
            }
        }
    }
    return 0;
}
