#include <bits/stdc++.h>
using namespace std;
typedef pair<int, pair<int, int> > pipii;
const int maxn = 10010;
const int maxm = 110;
const char *start_time = "08:00:00";

struct TIME{
    char str[10];
    int h, m, s;
    pipii id; // = make_pair(h, make_pair(m, s));
    TIME(const char *s = start_time){init(s); }
    void init(const char *s = start_time){strcpy(str, s); parse(); }
    void input(){scanf("%s", str); }
    void parse(){
        h = (str[0] - '0')*10 + (str[1] - '0');
        m = (str[3] - '0')*10 + (str[4] - '0');
        s = (str[6] - '0')*10 + (str[7] - '0');
        id = make_pair(h, make_pair(m, s));
    }
    void read(){input(); parse(); }
    void format(){
        if(s > 59){
            m += s / 60;
            s %= 60;
        }
        if(m > 59){
            h += m / 60;
            m %= 60;
        }
        id = make_pair(h, make_pair(m, s));
    }
    bool operator< (TIME &rhs){return id < rhs.id;}
    TIME operator+ (TIME &rhs){
        TIME ret;
        ret.h = this->h + rhs.h;
        ret.m = this->m + rhs.m;
        ret.s = this->s + rhs.s;
        ret.format();
        return ret;
    }
    TIME operator+ (int &rhs){
        TIME ret;
        ret.h = this->h;
        ret.m = this->m + rhs;
        ret.s = this->s;
        ret.format();
        return ret;
    }
};

struct TABLE{
    bool vip;
    int served_cnt;
    bool occupied;
    TABLE(){init(); }
    void init(){
        vip = false;
        served_cnt = 0;
        occupied = false;
    }
};

struct PLAYER{
    TIME *arrive;
    TIME *wait_time;
    int playtime;
    int isvip;
    PLAYER(){init(); }
    void init(){
        if(NULL == arrive) delete arrive;
        if(NULL == wait_time) delete wait_time;
        arrive = new TIME;
        wait_time = new TIME("00:00:00");
        playtime = 0;
        isvip = false;
    }
    void read(){
        arrive->read();
        scanf("%d%d", &playtime, &isvip);
    }
    void print(){
        printf("%s %s %d\n", arrive->str, wait_time->str, playtime);
    }
    bool operator< (PLAYER &rhs){
        return *arrive < *rhs.arrive;
    }
};

struct NODE{
    TABLE *table;
    PLAYER *player;
    TIME *leav_time;
    NODE(TABLE *t, PLAYER *p){init(t, p); }
    void init(TABLE *t, PLAYER *p){
        table = t, player = p;
        leav_time = new TIME(*player->arrive + *player->wait_time + player->playtime);
    }
};

struct cmp{
    bool operator() (NODE &a, NODE &b){
        return b.player->arrive < a.player->arrive; // a > b
    }
    bool operator() (PLAYER &a, PLAYER &b){
        return a.isvip < b.isvip;
    }
};

TABLE tables[maxm];
PLAYER p[maxn];
int n, m, k;

int get_table_id(bool pri = false){
    if(pri){
        for(int i = 1; i <= m; ++ i){
            if(tables[i].vip == true && tables[i].occupied == false){
                return i;
            }
        }
    }
    for(int i = 1; i <= m; ++ i){
        if(tables[i].occupied == false){
            return i;
        }
    }
    return 0;
}

void ini(){
    for(int i = 0; i < maxm; ++ i){
        tables[i].init();
    }
    for(int i = 0; i < maxn; ++ i){
        p[i].init();
    }
}

int main(){
    while(~scanf("%d", &n)){
        ini();
        for(int i = 1; i <= n; ++ i){
            p[i].read();
        }
        sort(p+1, p+1 + n);
        scanf("%d%d", &m, &k);
        for(int i = 0, x; i < k; ++ i){
            scanf("%d", &x);
            tables[x].vip = true;
        }
        // for(int i = 1; i <= n; ++ i){
        //     p[i].print();
        // }
        priority_queue<NODE, vector<NODE>, cmp> leav;
        priority_queue<PLAYER&, vector<PLAYER>, cmp> que;
        for(int i = 1; i <= n; ++ i){
            PLAYER *now = p + i;
            while(leav.size()){
                NODE nxtleave = leav.top();
                if(*now < *nxtleave.leav_time){
                    break;
                }
                leav.pop();
                assert(nxtleave.table->occupied == true);
                nxtleave.table->occupied = false;
            }
            int id = get_table_id(now->isvip);
            if(id){
                tables[id].occupied = true;
                tables[id].served_cnt ++;
                leav.push(NODE(&tables[id], now));
            }
            else {
                que.push(*now);
            }
        }

        // queue<TIME> arrv, leav;
        // arrv.push(TIME(p[1].arrive->str));
        // while(arrv.size()){
        //     TIME now = arrv.front();
        //     arrv.pop();
        //     int id = get_table_id(now);
        //     if(id){
        //         tables[id].occupied = true;
        //     }
        //     else {

        //     }
        // }
    }
    return 0;
}
