// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
using namespace std;
const size_t maxn = 210;
const int inf = 0x3f3f3f3f;

char s[maxn];
int k;

template<class T> 
T min(T &a, T &b){return a < b ? a : b;}

int main(){
    while(~scanf("%s%d", s, &k)){
        int ub, lb;
        int len = strlen(s);
        lb = ub = len;
        for(int i = 0; i < len; ++ i){
            if(s[i] == '?' || s[i] == '*'){
                lb -= 2;
                ub --;
            }
        }
        for(int i = 0; i < len; ++ i){
            if(s[i] == '*'){
                ub = inf;
                break;
            }
        }
        // printf("[%d, %d]\n", lb, ub);
        if(lb <= k && k <= ub){
            if(ub < inf){
                int cnt = min(ub, k) - lb;
                for(int i = 0; i < len; ++ i){
                    if(s[i] == '?' || s[i] == '*') continue;
                    if(s[i+1] == '?'){
                        if(cnt) {
                            printf("%c", s[i]);
                            cnt --;
                        }
                        else {
                            continue;
                        }
                    }
                    else {
                        printf("%c", s[i]);
                    }
                }
                printf("\n");
            }
            else {
                bool o = false;
                int cnt = k - lb;
                for(int i = 0; i < len; ++ i){
                    if(s[i] == '?' || s[i] == '*') continue;
                    if(s[i+1] == '*' && o == false){
                        o = true;
                        while(cnt --){
                            printf("%c", s[i]);
                        }
                    }
                    else {
                        if(s[i+1] == '?' || s[i+1] == '*') continue;
                        else printf("%c", s[i]);
                    }
                }
                printf("\n");
            }
        }
        else {
            printf("Impossible\n");
        }
    }
    return 0;
}