#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef map<ll, vector<int> > mv;
const int maxn = 150010;

int n, p;
ll in[maxn], ans[maxn];
mv a;

int main(){
    //freopen("in.in", "r", stdin);
    while(~scanf("%d", &n)){
        a.clear();
        p = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%I64d", in + i);
            a[in[i]].push_back(i);
        }
        for(mv::iterator it = a.begin(); it != a.end(); ++ it){
            sort(it->second.begin(), it->second.end());
            int len = it->second.size();
            ll now = it->first;
            if(len < 2)continue;
            for(int i = 0; i < len - 1; i += 2){
                in[it->second[i]] = 0;
                in[it->second[i+1]] += now;
                a[now<<1].push_back(it->second[i+1]);
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