#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;

int n;
char c = 0;
set<char> lst[maxn];
set<set<char> > rec;

int main(){
    while(scanf("%d", &n) == 1){
        getchar();
        for(int i = 0; i < n; ++ i){
            while(true){
                c = getchar();
                if(c < '0' || c > '9')break;
                lst[i].insert(c);
            }
            rec.insert(lst[i]);
        }
        printf("%d\n", rec.size());
        rec.clear();
        for(int i = 0; i < n; ++ i)
            lst[i].clear();
    }
    return 0;
}

/**

5
132
42
3312
43
24424

3
222
22
2

*/