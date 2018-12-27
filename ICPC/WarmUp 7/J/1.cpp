#include<bits/stdc++.h>
using namespace std;
const int maxn = 30;

char trib[maxn][maxn];
int n;
set<char> all, tmp;

int main(){
    while(~scanf("%d", &n)){
        tmp.clear();
        all.clear();
        memset(trib, 0, sizeof(trib));
        for(int i = 1; i <= n; ++ i)
            scanf("%s", trib[i] + 1);
        set<char> t1, t2, t3;
        for(int i = 1; i <= n; ++ i){
            t1.insert(trib[1][i]);
            t2.insert(trib[2][i]);
            t3.insert(trib[3][i]);
        }
        all = t1 == t2 ? t1 : t3;
        int row = 0, col = 0;
        char c = 0;
        for(int i = 1; i <= n; ++ i){
            for(int j = 1; j <= n; ++ j){
                tmp.insert(trib[i][j]);
            }
            if(tmp == all){
                tmp.clear();
                continue;
            }
            row = i;
            for(set<char>::iterator i = all.begin(); i != all.end(); ++ i){
                if(tmp.find(*i) == tmp.end()){
                    c = *i;
                    break;
                }
            }
            break;
        }
        if(tmp.size() < all.size()){
            tmp.clear();
            char arr[maxn], ch;
            for(int i = 1; i <= n; ++ i)
                arr[i] = trib[row][i];
            sort(arr + 1, arr + n + 1);
            for(int i = 2; i <= n; ++ i)
                if(arr[i] == arr[i-1]){
                    ch = arr[i];
                    break;
                }
            //printf("ch = %c\n", ch);
            for(int j = 1; j <= n; ++ j){
                if(trib[row][j] == ch){
                    //printf("j = %d\n", j);
                    for(int i = 1; i <= n; ++ i){
                        tmp.insert(trib[i][j]);
                    }
                    if(tmp == all){
                        tmp.clear();
                        continue;
                    }
                    //printf("in\n");
                    col = j;
                    break;
                }
            }
            //printf("out\n");
            printf("%d %d %c\n", row, col, c);
            continue;
        }
        else{
            char ch;
            for(int i = 1; i <= n; ++ i)
                if(all.find(trib[row][i]) == all.end()){
                    col = i;
                    break;
                }
            for(set<char>::iterator i = tmp.begin(); i != tmp.end(); ++ i)
                if(all.find(*i) != all.end())
                    all.erase(*i);
            printf("%d %d %c\n", row, col, *(all.begin()));
        }
    }
    return 0;
}

/**

6
OEYCDK
EYOKCD
KDCEOY
CKCOYE
YOEDKC
DCKYEO

*/