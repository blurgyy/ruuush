#include <bits/stdc++.h>
using namespace std;

int y, b, r;

int main(){
    while(~scanf("%d%d%d", &y, &b, &r)){
        int ory = 1, orb = 2, orr = 3;
        int diff = min(y - ory, min(b - orb, r - orr));
        printf("%d\n", ory + diff + orb + diff + orr + diff);
    }
    return 0;
}