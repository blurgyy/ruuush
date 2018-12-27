#include <bits/stdc++.h>
using namespace std;
const int maxn = 130;

char s[maxn];
int spos[maxn], epos[maxn];
int sp, ep, tot;
bool abbr[maxn];

bool inrange(char ch){
    return ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z';
}

bool cap(char ch){
    return ch >= 'A' && ch <= 'Z';
}

bool available_check(int pos){
    if(s[pos] < 'A' || s[pos] > 'Z')return false;
    int len = 0;
    for(int i = pos; inrange(s[i]); ++ i){
        len ++;
    }
    if(len == 1)return false;
    for(int i = 1; i < len; ++ i){
        if(cap(s[pos+i]))return false;
    }
    return true;
}

bool prior_space_check(int i){
    if(i == 0)return true;
    int prevend = epos[i-1] + 1;
    int curstart = spos[i];
    if(curstart - prevend > 1)return false;
    for(int j = prevend; j < curstart; ++ j){
        if(s[j] != ' ')return false;
    }
    return true;
}

bool post_space_check(int i){
    if(i + 1 == tot)return true;
    int curend = epos[i] + 1;
    int nstart = spos[i+1];
    if(nstart - curend > 1)return false;
    for(int j = curend; j < nstart; ++ j){
        if(s[j] != ' ')return false;
    }
    return true;
}

int main(){
    //freopen("in.in", "r", stdin);
    //freopen("out.out", "w", stdout);
    //freopen("abbreviation.in", "r", stdin);
    //freopen("abbreviation.out", "w", stdout);
    while(gets(s)){
        memset(abbr, false, sizeof(abbr));
        sp = ep = 0;
        int len = strlen(s);
        for(int i = 0; i < len; ++ i){
            if((i == 0 && inrange(s[i])) || !inrange(s[i-1]) && inrange(s[i])){
                spos[sp++] = i;
            }
            if(inrange(s[i]) && !inrange(s[i+1])){
                epos[ep++] = i;
            }
        }
        tot = 0;
        for(int i = 0; i < sp; ++ i){
            if(available_check(spos[i])){
                spos[tot] = spos[i];
                epos[tot++] = epos[i];
            }
        }
        spos[tot] = epos[tot] = 125;
        //printf("tot = %d\n", tot);
        for(int i = 0; i < tot; ++ i){
            int cnt = 0;
            if(i == 0 || !prior_space_check(i)){
                //printf("position = %d\n", i);
                while(true){
                    cnt ++;
                    if(i == tot - 1 || post_space_check(i) == false)break;
                    abbr[spos[i]] = true;
                    i ++;
                }
                //printf("cngt = %d, i = %d\n", cnt, i);
                if(cnt > 1){
                    abbr[spos[i]] = true;
                    //printf("abbr[%d] = true\n", spos[i]);
                }
            }
        }
        //for(int i = 0; i < tot; ++ i){
        //    printf("%c(%d, %d), abbr[%d] = %d\n", s[spos[i]], spos[i], epos[i], spos[i], abbr[spos[i]]);
        //}
        for(int i = 0; i < len; ++ i){
            if(abbr[i]){
                int now = i;
                int endpos = -1;
                for(int j = 0; j < tot; ++ j){
                    if(spos[j] == now){
                        while(abbr[spos[j]]){
                            //if(spos[j] != now && spos[j] - epos[j-1] > 2){
                            //    printf("diff = %d\n", spos[j] - epos[j-1]);
                            //    break;
                            //}
                            printf("%c", s[spos[j]]);
                            if(prior_space_check(j) && !post_space_check(j)){
                                j ++;
                                break;
                            }
                            j ++;
                        }
                        -- j;
                        endpos = epos[j];
                        break;
                    }
                }
                printf(" (");
                for(int j = now; j <= endpos; ++ j){
                    printf("%c", s[j]);
                }
                printf(")");
                i = endpos;
            }
            else {
                printf("%c", s[i]);
            }
        }
        printf("\n");
    }
    return 0;
}

/**

Po Op.Op Pp

*/