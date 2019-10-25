#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int T;
char s[maxn];
int cnt[3];

int main(){
    scanf("%d", &T);
    while(T --){
        memset(cnt, 0, sizeof(cnt));
        scanf("%s", s);
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            if(s[i] >= 'a' && s[i] <= 'z')cnt[0] ++;
            else if(s[i] >= '0' && s[i] <= '9')cnt[1] ++;
            else if(s[i] >= 'A' && s[i] <= 'Z')cnt[2] ++;
        }
        //printf("%d %d %d\n", cnt[0], cnt[1], cnt[2]);
        if(cnt[0]){
            if(cnt[1]){
                if(cnt[2]){
                    printf("%s\n", s);
                    continue;
                }
                else {
                    if(cnt[0] > 1){
                        for(int i = 0; i < len; ++ i){
                            if(s[i] >= 'a' && s[i] <= 'z'){
                                s[i] = 'F';
                                break;
                            }
                        }
                        printf("%s\n", s);
                        continue;
                    }
                    else {
                        for(int i = 0; i < len; ++ i){
                            if(s[i] >= '0' && s[i] <= '9'){
                                s[i] = 'G';
                                break;
                            }
                        }
                        printf("%s\n", s);
                        continue;
                    }
                }
            }
            else {
                if(cnt[2]){
                    if(cnt[0] > 1){
                        for(int i = 0; i < len; ++ i){
                            if(s[i] >= 'a' && s[i] <= 'z'){
                                s[i] = '5';
                                break;
                            }
                        }
                        printf("%s\n", s);
                        continue;
                    }
                    else {
                        for(int i = 0; i < len; ++ i){
                            if(s[i] >= 'A' && s[i] <= 'Z'){
                                s[i] = '6';
                                break;
                            }
                        }
                        printf("%s\n", s);
                        continue;
                    }
                }
                else {
                    s[0] = '0';
                    s[1] = 'A';
                    printf("%s\n", s);
                    continue;
                }
            }
        }
        else {
            if(cnt[1]){
                if(cnt[2]){
                    if(cnt[1] > 1){
                        for(int i = 0; i < len; ++ i){
                            if(s[i] >= '0' && s[i] <= '9'){
                                s[i] = 'a';
                                break;
                            }
                        }
                        printf("%s\n", s);
                        continue;
                    }
                    else {
                        for(int i = 0; i < len; ++ i){
                            if(s[i] >= 'A' && s[i] <= 'Z'){
                                s[i] = 'd';
                                break;
                            }
                        }
                        printf("%s\n", s);
                        continue;
                    }
                }
                else {
                    s[0] = 'a';
                    s[1] = 'A';
                    printf("%s\n", s);
                    continue;
                }
            }
            else {
                if(cnt[2]){
                    s[0] = 'a';
                    s[1] = '9';
                    printf("%s\n", s);
                    continue;
                }
                else {
                    while(1);
                }
            }
        }
    }
    return 0;
}