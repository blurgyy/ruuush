#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 200010;

int len;
char l_s[maxn], r_s[maxn];
vector<pii> ans;
struct NODE{
    char ch;
    int pos;
    bool invalid;
    bool operator< (NODE &rhs){
        if(invalid == rhs.invalid)
            return ch > rhs.ch;
        return invalid < rhs.invalid;
    }
}l[maxn], r[maxn];

void out(NODE s[]){
    for(int i = 0; ; ++ i){
        if(s[i].ch == '\0'){
            printf("\n");
            return;
        }
        printf("%c", s[i].ch);
    }
}

int main(){
    while(~scanf("%d%s%s", &len, l_s, r_s)){
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        ans.clear();
        for(int i = 0; i < len; ++ i){
            l[i].ch = l_s[i];
            l[i].pos = i + 1;
        }
        for(int i = 0; i < len; ++ i){
            r[i].ch = r_s[i];
            r[i].pos = i + 1;
        }
        sort(l, l + len);
        sort(r, r + len);
        // out(l), out(r);
        int pl = 0, pr = 0;
        while(pl < len && pr < len){
            // printf("<%d, %d>\n", pl, pr);
            if(l[pl].ch == '?' || r[pr].ch == '?'){
                break;
            }
            if(l[pl].ch == r[pr].ch){
                ans.push_back(make_pair(l[pl].pos, r[pr].pos));
                // ans.push_back(make_pair(pl, pr));
                l[pl].invalid = true;
                r[pr].invalid = true;
                pl ++;
                pr ++;
            }
            else if(l[pl].ch > r[pr].ch){
                pl ++;
            }
            else {
                pr ++;
            }
        }
        sort(l, l + len);
        sort(r, r + len);
        // out(l), out(r);
        int tot = ans.size();
        pl = len - tot - 1;
        pr = 0;
        while(pl >= 0 && pr < len - tot){
            // if(l[pl].ch != '?' && r[pr].ch != '?'){
            //     break;
            // }
            if(l[pl].ch == '?' || r[pr].ch == '?'){
                ans.push_back(make_pair(l[pl].pos, r[pr].pos));
                pl --;
                pr ++;
            }
            else {
                while(pr < len - tot && r[pr].ch != '?'){
                    pr ++;
                }
                if(pr == len - tot){
                    break;
                }
            }
        }
        tot = ans.size();
        printf("%d\n", tot);
        for(int i = 0; i < tot; ++ i){
            printf("%d %d\n", ans[i].first, ans[i].second);
        }
    }
    return 0;
}
