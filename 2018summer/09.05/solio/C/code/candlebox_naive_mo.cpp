// SWERC 2016 - Candle Box
// Approach: Naive solution checking possible age values for Rita.
// Author: Miguel Oliveira
#include <cassert>
#include <cstdio>

int main() {
  int D, R, T;
  scanf("%d %d %d", &D, &R, &T);
  assert(D >= 1 && D <= 20);
  assert(R >= 4 && R < 1000);
  assert(T >= 0 && T < 1000);
  for (int rita_age = 4; rita_age <= 100; ++rita_age) {
    int rita_should_have = rita_age * (rita_age+1) / 2 - 6;
    if (rita_should_have > R)
      continue;
    int theo_age = rita_age - D;
    if (theo_age < 3)
      continue;
    int theo_had = theo_age * (theo_age+1) / 2 - 3;
    if (theo_had < T)
      continue;
    int added = theo_had - T;
    if (rita_should_have + added == R)
      printf("%d\n", added);
  }
  return 0;
}
