/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem F. Folding                                             */
/*                                                                */
/* Original idea         Georgiy Korneev                          */
/* Problem statement     Georgiy Korneev                          */
/* Test set              Georgiy Korneev                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Pavel Kunyavskiy                         */
/******************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int get(int a, int b) {
  if (a < b) return INF;
  int ans = 0;
  while (a > b) {
    ans++;
    a = (a + 1) / 2;
  }
  return ans;
}

int main() {
  freopen("folding.in", "r", stdin);
  freopen("folding.out", "w", stdout);

  int W, H, w, h;
  scanf("%d%d%d%d",&W, &H, &w, &h);

  int ans = min(get(W, w) + get(H, h), get(W, h) + get(H, w));
  if (ans >= INF) {
    printf("-1\n");
  } else {
    printf("%d\n", ans);
  }
}

