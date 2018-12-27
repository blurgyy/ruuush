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
/* Author                Pavel Kunyavskiy                         */
/******************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

int cnt[8];

int main() {
  freopen("integral.in", "r", stdin);
  freopen("integral.out", "w", stdout);

  int n;
  scanf("%d", &n);
  vector<int> x(n);
  vector<int> y(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d",&x[i], &y[i]);
  }

  x.push_back(x[0]);
  y.push_back(y[0]);

  int odd = 0;
  for (int i = 0; i < n; i++) {
    //printf("x = %d, y = %d, odd = %d\n", x[i], y[i], odd);
    cnt[(x[i] & 1) + (y[i] & 1) * 2 + odd * 4]++;
    if ((x[i] - x[i + 1]) % 2 == 0 && (y[i] - y[i + 1]) % 2 == 0) {
      odd ^= 1;
    }
    odd ^= 1;
  }

  //printf("res, odd = %d\n", odd);

  if (odd == 1) {
    printf("0\n");
    return 0;
  }

  long long ans = 0;

  for (int i = 0; i < 8; i++) {
    for (int j = i; j < 8; j++) {
      int a = i ^ j;
      int res = (a >> 2);
      if ((a & 3) == 0) {
        res ^= 1;
      }
      if (res) {
        if (i == j) {
          ans += cnt[i] * 1LL * (cnt[i] - 1) / 2;
        } else {
          ans += cnt[i] * 1LL * cnt[j];
        }
        //printf("i = %d, j = %d, ans = %lld\n", i, j, ans);
      }
    }
  }

  printf("%lld\n", ans - n);
  return 0;
}

