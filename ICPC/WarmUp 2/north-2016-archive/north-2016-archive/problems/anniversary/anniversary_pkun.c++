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
/* Author                Pavel Kunyavskiy                         */
/******************************************************************/

#include <cstdio>

int main() {
  freopen("anniversary.in", "r", stdin);
  freopen("anniversary.out", "w", stdout);
  int x, y, ax, ay, bx, by;
  scanf("%d%d%d%d%d%d",&x, &y, &ax, &ay, &bx, &by);

  if (ax != bx) {
    printf("%d %d %d %d\n", ax, 0, bx, y);
  } else {
    printf("%d %d %d %d\n", 0, ay, x, by);
  }
}

