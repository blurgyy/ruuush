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
/* Author                Pavel Kunyavskiy                         */
/******************************************************************/

#include <cstdio>
#include <string>

using namespace std;


string indate(int shift) {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  c -= shift;
  char buf[200];
  sprintf(buf, "%04d%02d%02d", c, b, a);
  return buf;
}

int main() {
  freopen("king.in", "r", stdin);
  freopen("king.out", "w", stdout);

  string d = indate(18);
  int n;
  scanf("%d", &n);

  string best = "";
  int bestid = -1;
  for (int i = 0; i < n; i++) {
    string cd = indate(0);
    if (cd > d) continue;
    if (best == "" || cd > best) {
      best = cd;
      bestid = i + 1;
    }
  }
  printf("%d\n", bestid);
  return 0;
}

