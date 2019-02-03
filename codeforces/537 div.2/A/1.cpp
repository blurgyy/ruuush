#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;
const char *out[2] = {"No", "Yes"};

char s[maxn], t[maxn];

bool vowel(char ch){return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';}

int main(){
    while(~scanf("%s%s", s, t)){
        int slen = strlen(s);
        int tlen = strlen(t);
        if(slen != tlen){
            printf("No\n");
            continue;
        }
        bool ans = true;
        for(int i = 0; i < slen; ++ i){
            if(vowel(s[i]) && vowel(t[i]) || !vowel(s[i]) && !vowel(t[i])) continue;
            ans = false;
            break;
        }
        printf("%s\n", out[ans]);
    }
    return 0;
}