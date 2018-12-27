#include<bits/stdc++.h>
using namespace std;
const int maxn = 400010;
typedef long long ll;

int n, m;
ll possess[maxn];
vector<int> out;

bool bs(int left, int right, ll e){
    if(left >= right)
        return possess[right] == e;
    int mid = (left + right)>>1;
    if(possess[mid] >= e)return bs(left, mid, e);
    return bs(mid+1, right, e);
}

int main(){
    while(~scanf("%d%d", &n, &m)){
        out.clear();
        for(int i = 0; i < n; ++ i)
            scanf("%d", possess + i);
        sort(possess, possess + n);
        int ans = 0;
        for(int i = 1; i < maxn && ans + i <= m; ++ i){
            if(bs(0, n, (ll)i))continue;
            ans += i;
            out.push_back(i);
        }
        //sort(out.begin(), out.end());
        int Size = out.size();
        printf("%d\n", Size);
        if(Size){
            printf("%d", out[0]);
            for(int i = 1; i < Size; ++ i)
                printf(" %d", out[i]);
            printf("\n");
        }
    }
    return 0;
}

/**

3 7
1 3 4

4 14
4 6 12 8

6 3
1 2 3 4 5 6

*/