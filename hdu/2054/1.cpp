#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

char a[maxn], b[maxn];

void Front(char* s, int pos){
    int len = strlen(s);
    for(int i = pos, j = 0; i <= len; ++ i, ++ j){
        s[j] = s[i];
    }
}

int main(){
    while(~scanf("%s%s", a, b)){
        int len1 = strlen(a);
        int len2 = strlen(b);
        bool una = false, unb = false;
        if(a[0] == '-'){
            Front(a, 1);
            una = true;
        }
        if(b[0] == '-'){
            Front(b, 1);
            unb = true;
        }
        for(int i = 0; i < len1; ++ i){
            if(a[i] != '0'){
                Front(a, i);
                break;
            }
        }
        for(int i = 0; i < len2; ++ i){
            if(b[i] != '0'){
                Front(b, i);
                break;
            }
        }
        len1 = strlen(a);
        len2 = strlen(b);
        bool fa = false, fb = false;
        for(int i = 0; i < len1; ++ i)
            if(a[i] == '.'){
                fa = true;
                break;
            }
        for(int i = 0; i < len2; ++ i)
            if(b[i] == '.'){
                fb = true;
                break;
            }
        if(fa == fb){
            if(fa){
                for(int i = len1-1; i >= 0; -- i)
                    if(a[i] == '0')a[i] = 0;
                    else break;
                for(int i = len2-1; i >= 0; -- i)
                    if(b[i] == '0')b[i] = 0;
                    else break;
                //printf("a:%s, b:%s\n", a, b);
            }
            if(!strcmp(a, b) && una == unb)printf("YES\n");
            else printf("NO\n");
        }
        else{
            if(fa){
                for(int i = len1-1; i >= 0; -- i)
                    if(a[i] == '0')a[i] = 0;
                    else break;
                len1 = strlen(a);
                if(a[len1-1] == '.')a[len1-1] = 0;
                if(!strcmp(a, b) && una == unb)printf("YES\n");
                else printf("NO\n");
            }
            else{
                for(int i = len2-1; i >= 0; -- i)
                    if(b[i] == '0')b[i] = 0;
                    else break;
                len1 = strlen(b);
                if(b[len1-1] == '.')b[len1-1] = 0;
                if(!strcmp(a, b) && una == unb)printf("YES\n");
                else printf("NO\n");
            }
            //printf("a:%s, b:%s\n", a, b);
        }
    }
    return 0;
}