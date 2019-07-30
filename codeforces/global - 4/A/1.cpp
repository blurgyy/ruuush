#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

int n;
struct PARTY{
    int cnt;
    int idx;
    bool operator< (PARTY &rhs){
        return cnt > rhs.cnt;
    }
}a[maxn];

int main(){
    while(~scanf("%d", &n)){
        int sum = 0;
        for(int i = 0; i < n; ++ i){
            scanf("%d", &a[i].cnt);
            a[i].idx = i + 1;
            sum += a[i].cnt;
        }
        sort(a+1, a+n);
        vector<int> ans;
        bool yes = true;
        for(int i = 0, acc = 0; i < n; ++ i){
            if(i == 0 || a[0].cnt >= a[i].cnt * 2){
                acc += a[i].cnt;
                ans.push_back(a[i].idx);
            }
            if(acc > sum / 2){
                break;
            }
            else if(i == n-1){
                yes = false;
            }
        }
        if(yes){
            printf("%d\n", ans.size());
            for(int i = 0; i < ans.size(); ++ i){
                printf("%d%c", ans[i], " \n"[i==ans.size()-1]);
            }
        }
        else {
            printf("0\n");
        }
    }
    return 0;
}
