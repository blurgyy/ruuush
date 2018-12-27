#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 100;
const double pi = acos(-1.0);

struct Node{
    double x, y;
}pt[maxn], q;
int T, n, Case = 0;

double sq(double a){
    return a * a;
}

double dist(Node a, Node b){
    return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
}

int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        for(int i = 0; i < n; ++ i){
            cin >> pt[i].x >> pt[i].y;
        }
        cin >> q.x >> q.y;
        double ans = 0;
        for(int i = 0; i < n; ++ i){
            int f = i, s = (i + 1) % n, t = (i + 2) % n;
            double d1 = dist(pt[f], pt[s]);
            double d2 = dist(pt[s], pt[t]);
            double d3 = dist(pt[t], pt[f]);
            double theta = acos(-(sq(d1) + sq(d2) - sq(d3)) / (2 * d1 * d2));
            ans += theta * dist(q, pt[s]);
        }
        printf("Case #%d: %.3f\n", ++ Case, ans);
    }
    return 0;
}