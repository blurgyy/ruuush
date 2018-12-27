#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;

struct Node{
    int x, y;
}node;
int n, d, m;

bool check(Node node){
    int x = node.x;
    int y = node.y;
    return (x + y >= d) && (x + y <= n + n - d) && (y - x <= d) && (x - y <= d);
}

int main(){
    while(~scanf("%d%d%d", &n, &d, &m)){
        for(int i = 0; i < m; ++ i){
            scanf("%d%d", &node.x, &node.y);
            if(check(node)){
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }
        }
    }
    return 0;
}