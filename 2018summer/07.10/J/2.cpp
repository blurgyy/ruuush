#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int T;
char s[maxn];
struct cord{
    int x, y;
    void init(int _x = 0, int _y = 0){x = _x, y = _y;}
    cord(int _x = 0, int _y = 0){init(_x, _y);}
    void move(int direction){
        x += dx[direction];
        y += dy[direction];
    }
}now;
map<cord, bool> rec;

bool operator<(cord b, cord a){
    return b.x == a.x ? b.y < a.y : b.x < a.x;
}

void ini(){
    now.init();
    rec.clear();
}

int main(){
    freopen("J.in", "r", stdin);
    scanf("%d", &T);
    printf("%d\n", T);
    while(T --){
        ini();
        scanf("%s", s);
        int len = strlen(s);
        int dir = 0;
        for(int i = 0; i < len; ++ i){
            if(s[i] == 'R'){
                dir = (dir + 3) % 4;
            }
            else if(s[i] == 'F'){}
            else if(s[i] == 'L'){
                dir = (dir + 1) % 4;
            }
            else if(s[i] == 'B'){
                dir = (dir + 2) % 4;
            }
            rec[now] = true;
            now.move(dir);
        }
        int minx = 0, maxx = 0, miny = inf, maxy = -inf;
        for(auto i = rec.begin(); i != rec.end(); ++ i){
            maxx = max(maxx, i->first.x);
            maxy = max(maxy, i->first.y);
            miny = min(miny, i->first.y);
        }
        maxy ++, maxx ++;
        miny --;
        printf("%d %d\n", maxy - miny + 1, maxx - minx + 1);
        for(int y = maxy; y >= miny; -- y){
            for(int x = minx; x <= maxx; ++ x){
                now.init(x, y);
                if(rec[now]){
                    printf(".");
                }
                else {
                    printf("#");
                }
            }
            printf("\n");
        }
    }
    return 0;
}