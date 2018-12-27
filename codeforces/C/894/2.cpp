#include<bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int a[maxn], m;

int bs(int e, int left = 0; int right = m-1){
    if(left >= right)return right;
    int mid((left + right) >> 1);
    if(e <= a[mid])return bs(e, left, mid);
    return bs(e, mid + 1, right);
}

bool check(int e){
    return a[bs(e)] == e;
}

int main(){
    while(~scanf("%d", &m)){
        for(int i = 0; i < m; ++ i)
            scanf("%d", a + i);
        for(int i = m-1; i >= 0; -- i){
            
        }
    }
    return 0;
}