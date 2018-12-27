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
/* Checker                                                        */
/*                                                                */
/* Author                Niyaz Nigmatullin                        */
/******************************************************************/

#include "testlib.h"

int main(int argc, char **argv) {
  registerTestlibCmd(argc, argv);
  int n = inf.readInt();
  int m = inf.readInt();
  int x1 = inf.readInt();
  int y1 = inf.readInt();
  int x2 = inf.readInt();
  int y2 = inf.readInt();
  int ax = ouf.readInt(0, n);
  int ay = ouf.readInt(0, m);
  int bx = ouf.readInt(0, n);
  int by = ouf.readInt(0, m);
  if (ax == bx && ay == by) {
    quitf(_wa, "Can't draw line through two equal points");
  }
  if (ax != 0 && ax != n && ay != 0 && ay != m) {
    quitf(_wa, "Point #1 (%d, %d) is not located on the border of rectangle", ax, ay);
  }
  if (bx != 0 && bx != n && by != 0 && by != m) {
    quitf(_wa, "Point #2 (%d, %d) is not located on the border of rectangle", bx, by);
  }
  long long la = by - ay;
  long long lb = ax - bx;
  long long lc = (long long) -la * ax - (long long) lb * ay;
  long long side1 = x1 * la + y1 * lb + lc;
  if (side1 == 0) {
    quitf(_wa, "Input point #1 (%d, %d) lies on the line", x1, y1);
  }
  long long side2 = x2 * la + y2 * lb + lc;
  if (side2 == 0) {
    quitf(_wa, "Input point #2 (%d, %d) lies on the line", x2, y2);
  }
  side1 = side1 < 0 ? -1 : 1;
  side2 = side2 < 0 ? -1 : 1;
  if (side1 == side2) {
    quitf(_wa, "Input points are located on the same halfplane");
  }
  quitf(_ok, "Line = (%d, %d) -- (%d, %d)", ax, ay, bx, by);
}

