#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;

int n; char a[maxn][maxn];

bool check(int x, int y){return a[x][y] == 'X' && a[x][y] == a[x-1][y-1] && a[x-1][y-1] == a[x+1][y+1] && a[x-1][y+1] == a[x+1][y-1] && a[x-1][y-1] == a[x-1][y+1]; }

int main(){memset(a, 0, sizeof(a)); while(~scanf("%d", &n)){for(int i = 1; i <= n; ++ i){scanf("%s", a[i] + 1); } int ans = 0; for(int i = 1; i <= n; ++ i){for(int j = 1; j <= n; ++ j){ans += check(i, j); } } printf("%d\n", ans); } return 0; }