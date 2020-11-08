#include <bits/stdc++.h>
using namespace std;
int const maxn   = 30;
int const dirx[] = {-1, 0, 1, 0};
int const diry[] = {0, 1, 0, -1};

int  n, m;
char s[maxn][maxn];
bool v[4][maxn][maxn];
int  ans;

bool inrange(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= m; }

void outputv() {
    for (int d = 0; d < 4; ++d) {
        printf("dir %d:\n", d);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                printf("%d", v[d][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void rotdfs(int x, int y, int dir, int spd = 0, int px = -1, int py = -1) {
    if (!inrange(x, y) || s[x][y] == '#' || v[dir][x][y]) {
        return;
    }
    v[dir][x][y] = true;
    if (s[x][y] == 'D') {
        ans = min(ans, spd);
        return;
    }
    int ndir1 = (dir + 1) % 4;
    int nx1   = x + dirx[ndir1];
    int ny1   = y + diry[ndir1];
    rotdfs(nx1, ny1, ndir1, spd, x, y);

    int ndir2 = (dir + 3) % 4;
    int nx2   = x + dirx[ndir2];
    int ny2   = y + diry[ndir2];
    rotdfs(nx2, ny2, ndir2, spd, x, y);
}

void alldfs(int x, int y, int dir, int spd = 0, int px = -1, int py = -1) {
    if (!inrange(x, y) || s[x][y] == '#' || v[dir][x][y]) {
        return;
    }
    v[dir][x][y] = true;
    if (s[x][y] == 'D') {
        ans = min(ans, spd);
        return;
    }
    int ndir1 = (dir + 1) % 4;
    int nx1   = x + dirx[ndir1];
    int ny1   = y + diry[ndir1];
    alldfs(nx1, ny1, ndir1, spd, x, y);

    int ndir2 = (dir + 3) % 4;
    int nx2   = x + dirx[ndir2];
    int ny2   = y + diry[ndir2];
    alldfs(nx2, ny2, ndir2, spd, x, y);

    int nx = x + dirx[dir];
    int ny = y + diry[dir];
    alldfs(nx, ny, dir, spd + 1, x, y);
}

void init() {
    ans = 0x7fffffff;
}

int main() {
    // freopen("in.in", "r", stdin);
    while (~scanf("%d%d", &n, &m)) {
        init();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s[i] + 1);
        }
        int sx, sy;
        // int ex, ey;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s[i][j] == 'S') {
                    sx = i, sy = j;
                }
            }
        }
        for (int dir = 0; dir < 4; ++dir) {
            memset(v, false, sizeof(v));
            rotdfs(sx, sy, dir, 0);
        }
        for (int dir = 0; dir < 4; ++dir) {
            memset(v, false, sizeof(v));
            alldfs(sx, sy, dir, 0);
        }
        if (ans == 0x7fffffff) {
            ans = -1;
        }
        printf("%d\n", ans);
    }
    return 0;
}

// Author: Blurgy <gy@blurgy.xyz>
// Date:   Nov 08 2020, 16:57 [CST]
