#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef map<ll, priority_queue<int> > mv;
const int maxn = 150010;

int n, p;
ll in[maxn], ans[maxn];
mv a;

int main(){
    while(~scanf("%d", &n)){
        a.clear();
        p = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%I64d", in + i);
            a[in[i]].push(-i);
        }
        for(mv::iterator it = a.begin(); it != a.end(); ++ it){
            int len = it->second.size();
            ll now = it->first;
            if(len < 2)continue;
            while(it->second.size() > 2){
                
            }
        }
        for(int i = 0; i < n; ++ i)
            if(in[i])
                ans[p++] = in[i];
        printf("%d\n", p);
        for(int i = 0; i < p; ++ i)
            printf("%I64d ", ans[i]);
        printf("\n");
    }
    return 0;
}

/**

7
3 4 1 2 2 1 1

5
1 1 3 1 1

5
10 40 20 50 30

*/