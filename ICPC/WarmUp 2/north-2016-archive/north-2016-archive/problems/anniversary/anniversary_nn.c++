/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem A. Anniversary Cake                                    */
/*                                                                */
/* Original idea         Niyaz Nigmatullin                        */
/* Problem statement     Dmitry Shtukenberg                       */
/* Test set              Niyaz Nigmatullin                        */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Niyaz Nigmatullin                        */
/******************************************************************/

#include <cassert>
#include <cstdio>

int main() {
  assert(freopen("anniversary.in", "r", stdin));
  assert(freopen("anniversary.out", "w", stdout));
  int n, m;
  assert(2 == scanf("%d%d", &n, &m));
  int x1, y1, x2, y2;
  assert(4 == scanf("%d%d%d%d", &x1, &y1, &x2, &y2));
  if (x1 == x2) {
    printf("%d %d\n%d %d\n", 0, y1, n, y2);
  } else {
    printf("%d %d\n%d %d\n", x1, 0, x2, m);
  }
}

