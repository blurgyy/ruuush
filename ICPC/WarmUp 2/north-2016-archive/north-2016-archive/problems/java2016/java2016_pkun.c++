/******************************************************************/
/* ACM ICPC 2016-2017, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, October 22, 2016                                */
/******************************************************************/
/* Problem J. Java2016                                            */
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

int main() {
  freopen("java2016.in", "r", stdin);
  freopen("java2016.out", "w", stdout);

  const int N = 2;
  char prev = '?';
  char last = 'k';
  for (char c = 'a'; c <= last; c++) {
    printf("%c = %c", c, prev);
    for (int i = 1; i < N; i++) {
      printf(" max %c", prev);
    }
    printf("\n");
    prev = c;
  }
  for (char c = last + 1; c <= last + 8; c++) {
    printf("%c = %c + %c\n", c, c - 1, c - 1);
  }
  int x = 0;
  scanf("%d", &x);
  int count = 256 - x;
  int any = 0;
  for (int i = 0; i <= 8; i++) {
    if (count & (1 << i)) {
      if (any) {
        printf(" + ");
      }
      printf("%c", last + i);
      any = 1;
    }
  }
  printf("\n");
}

