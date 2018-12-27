/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem K. King's Heir                                         */
/*                                                                */
/* Original idea         Andrew Stankevich                        */
/* Problem statement     Andrew Stankevich                        */
/* Test set              Pavel Kunyavskiy                         */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Niyaz Nigmatullin                        */
/******************************************************************/

#include <cstdio>
#include <cassert>

int main() {
  assert(freopen("king.in", "r", stdin));
  assert(freopen("king.out", "w", stdout));
  int d, m, y;
  assert(3 == scanf("%d%d%d", &d, &m, &y));
  int n;
  assert(1 == scanf("%d", &n));
  int ans = -1;
  int ansy = -10000;
  int ansm = -10000;
  int ansd = -10000;
  for (int i = 0; i < n; i++) {
    int cd, cm, cy;
    assert(3 == scanf("%d%d%d", &cd, &cm, &cy));
    int age = y - cy;
    if (cm > m || (cm == m && cd > d)) {
      --age;
    }
    if (age < 18) continue;    
    if (ansy < cy || (ansy == cy && (ansm < cm || (ansm == cm && ansd < cd)))) {
      ans = i + 1;
      ansy = cy;
      ansm = cm;
      ansd = cd;
    }
  }
  printf("%d\n", ans);
}

