#include<bits/stdc++.h>
using namespace std;
const int maxn = 200010;

int n, p;
vector<int> out[maxn];

int bs(int e, int left = 0, int right = p){
    if(left >= right)return right;
    int mid = (left + right) >> 1;
    if(!out[mid].size())return mid;
    if(out[mid].back() >= e)return bs(e, mid + 1, right);
    return bs(e, left, mid);
}

int main(){
    while(~scanf("%d", &n)){
        for(int i = 0; i < n; ++ i)
            out[i].clear();
        p = 1;
        int in;
        scanf("%d", &in);
        out[0].push_back(in);
        n--;
        while(n--){
            scanf("%d", &in);
            int pos = bs(in);
            p = max(p, pos + 1);
            out[pos].push_back(in);
        }
        for(int i = 0; i < maxn; ++ i){
            if(!out[i].size())break;
            for(int j = 0; j < out[i].size(); ++ j)
                printf("%d ", out[i][j]);
            printf("\n");
        }
    }
    return 0;
}