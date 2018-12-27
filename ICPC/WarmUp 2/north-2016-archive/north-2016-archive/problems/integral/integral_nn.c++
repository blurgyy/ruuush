/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem I. Integral Polygons                                   */
/*                                                                */
/* Original idea         Niyaz Nigmatullin                        */
/* Problem statement     Dmitry Shtukenberg                       */
/* Test set              Niyaz Nigmatullin                        */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Niyaz Nigmatullin                        */
/******************************************************************/

#include <cstdio>
#include <cassert>

struct point {
  int x, y;
};

int const N = 1234567;

point p[N];
int d[42][42];

int main() {
  assert(freopen("integral.in", "r", stdin));
  assert(freopen("integral.out", "w", stdout));
  int n;
  assert(1 == scanf("%d", &n));
  for (int i = 0; i < n; i++) {
    int x, y;
    assert(2 == scanf("%d%d", &x, &y));
    p[i] = {x, y};
  }
  long long area = 0;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    area += (long long) p[i].x * p[j].y - (long long) p[i].y * p[j].x;
  }
  if ((area & 1) != 0) {
    puts("0");
    return 0;
  }
  for (int i = 0; i < n; i++) {
    p[i].x &= 1;
    p[i].y &= 1;
  }
  int ca = 0;
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    ca ^= (p[i].x & p[j].y) ^ (p[i].y & p[j].x);
    for (int m = 0; m < 4; m++) {
      for (int a = 0; a < 2; a++) {
        int all = ca ^ a ^ (m & 1 & p[j].y) ^ ((m >> 1) & 1 & p[j].x);
        if (all == 0) {
          ans += d[m][a];
        }
      }
    }
    d[p[j].x | (p[j].y << 1)][ca]++;
  }
  printf("%lld\n", ans - n);
}

