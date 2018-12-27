// Within Arms Reach, SWERC 2016
// Problem author: André Susano Pinto
// This solution by Pedro Guerreiro.
// Use at your own risk.

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define MY_PI 3.14159265358979323846  /* pi */

int int_get(void)
{
  int result;
  scanf("%d", &result);
  return result;
}

int doubles_get(double *a)
{
  int result = 0;
  double x;
  while (scanf("%lf", &x) != EOF)
    a[result++] = x;
  return result;
}

void doubles_println_basic(const double *a, int n)
{
  if (n > 0)
  {
    printf("%g", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      printf(" %g", a[i]);
  }
  printf("\n");
}

void doubles_print(const double *a, int n, char *separator)
{
  if (n > 0)
  {
    printf("%g", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      printf("%s%g", separator, a[i]);
  }
}

void doubles_println(const double *a, int n, char *separator)
{
  doubles_print(a, n, separator);
  printf("\n");
}

void doubles_printf(const double *a, int n, char *fmt)
{
  for (int i = 0; i < n; i++)
    printf(fmt, a[i]);
}

void doubles_printfln(const double *a, int n, char *fmt)
{
  doubles_printf(a, n, fmt);
  printf("\n");
}

int doubles_get_some(double *a, int n)
{
  int result = 0;
  double x;
  while (result < n && scanf("%lf", &x) != EOF)
    a[result++] = x;
  return result;
}

double doubles_sum(const double *a, int n)
{
  double result = 0;
  for (int i = 0; i < n; i++)
    result += a[i];
  return result;
}

double doubles_max(const double *a, int n)
{
  double result = -INFINITY;
  for (int i = 0; i < n; i++)
    if (result < a[i])
      result = a[i];
  return result;
}

double doubles_min(const double *a, int n)
{
  double result = +INFINITY;
  for (int i = 0; i < n; i++)
    if (result > a[i])
      result = a[i];
  return result;
}

int doubles_argmax(const double *a, int n)
{
  assert(n > 0);
  int result = 0;
  double m = a[0];
  for (int i = 1; i < n; i++)   // i = 1
    if (m < a[i])
      m = a[result = i];
  return result;
}

int doubles_accumulate(const double *a, int n, double *b)
{
  b[0] = 0;
  for (int i = 0; i < n; i++)
    b[i+1] = b[i] + a[i];
  return n+1;
}

//------------------

double first_circle(double x)
{
  double result = x;
  if (x < 0)
    result = first_circle(x + 2*MY_PI);
  else if (x >= 2*MY_PI)
    result = first_circle(x - 2*MY_PI);
  return result;
}

void doubles_first_circle(double *a, int n)
{
  for (int i = 0; i < n; i++)
    a[i] = first_circle(a[i]);
}

//------------------

typedef struct {
  double vx;
  double vy;
} Vector;

typedef struct {
  double x;
  double y;
} Point;

Vector vector(double vx, double vy)
{
  Vector result;
  result.vx = vx;
  result.vy = vy;
  return result;
}

Vector from_polar(double r, double a)
{
  return vector(r * cos(a), r * sin(a));
}

double vector_angle(Vector v)
{
  return atan2(v.vy, v.vx);
}

Point point(double x, double y)
{
  Point result;
  result.x = x;
  result.y = y;
  return result;
}

Point point_get()
{
  double x, y;
  scanf("%lf%lf", &x, &y);
  return point(x, y);
}

double distance(Point p1, Point p2)
{
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  return sqrt(dx * dx + dy * dy);
}

double point_angle(Point p)
{
  return atan2(p.y, p.x);
}

int points_from_angles(const double *a, int n, Point center, double r, Point *p)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    p[result++] = point(center.x + r * cos(a[i]), center.y + r * sin(a[i]));
  return result;
}

void point_print(Point p)
{
  printf("[%g %g]", p.x, p.y);
}

void point_printf(const char *fmt, Point p)
{
  printf(fmt, p.x, p.y);
}

void point_println(Point p)
{
  point_print(p);
  printf("\n");
}

void points_print(const Point *a, int n)
{
  for (int i = 0; i < n; i++)
    point_print(a[i]);
}

void points_printf(const char *fmt, const Point *a, int n)
{
  for (int i = 0; i < n; i++)
    point_printf(fmt, a[i]);
}

void points_println(const Point *a, int n)
{
  points_print(a, n);
  printf("\n");
}

Vector from_points(Point p1, Point p2)
{
  return vector(p2.x - p1.x, p2.y - p1.y);
}

Point rotate(Point p, double a)
{
  return point(p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a));
}

int points_rotate(const Point *a, int n, double angle, Point *b)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    b[result++] = rotate(a[i], angle);
  return result;
}

Point plus(Point p, Vector v)
{
  return point(p.x + v.vx, p.y + v.vy);
}

int vectors_from_points(const Point *p, int n, Vector *v)
{
  int result = 0;
  for (int i = 1; i < n; i++)
    v[result++] = from_points(p[i-1], p[i]);
  return result;
}

int vectors_angles(const Vector *v, int n, double *a)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = vector_angle(v[i]);
  return result;
}

// -------------------

// Polygon

int is_possible(const double *a, int n)
{
  double sum = doubles_sum(a, n);
  for (int i = 0; i < n; i++)
    if (a[i] > sum/2)
      return 0;
  return 1;
}

double chord_angle(double x, double r)
{
  assert (x <= 2 * r);
  return 2 * asin((x / 2) / r);
}

double sum_chord_angles(const double *a, int n, double r)
{
  double result = 0;
  for (int i = 0; i < n; i++)
    result += chord_angle(a[i], r);
  return result;
}

int angles(const double *s, int n, double r, double *a)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = 2 * asin((s[i] / 2)/r);
  return result;
}

double equation(const double *a, int n, double x)
{
  return sum_chord_angles(a, n, x) - 2 * MY_PI;
}

double equation_other(const double *a, int n, double x)
{
  return sum_chord_angles(a, n, x) - 2 * chord_angle(doubles_max(a, n), x);
}

// -------------------

typedef double Function(const double *, int, double);

double bisection_simple(Function f, const double *s, int n, double a, double b)
{
  double result;
  if (f(s, n, a) == 0)
    result = a;
  else if (f(s, n, b) == 0)
    result = b;
  else if (fabs(b-a) < 1e-6)
    result = (b+a)/2;
  else
  {
    double c = (b+a)/2;
    if (f(s, n, c) <= 0)
      result = bisection_simple(f, s, n, c, b);
    else
      result = bisection_simple(f, s, n, a, c);
  }
  return result;
}

double bisection(Function f, const double *s, int n, double a, double b)
{
  assert(f(s, n, a) <= 0 && f(s, n, b) >= 0 || f(s, n, a) >= 0 && f(s, n, b) <= 0);
  double result;
  if (f(s, n, a) <= 0)
    result = bisection_simple(f, s, n, a, b);
  else
    result = bisection_simple(f, s, n, b, a);
  return result;
}

double while_negative_value_duplicate(Function f, const double *s, int n, double x)
{
  double result;
  if (f(s, n, x) >= 0)
    result = x;
  else
    result = while_negative_value_duplicate(f, s, n, 2*x);
  return result;
}

double circumference(const double *s, int n) // computes radius of circumference with the given sides inscribed
{
  double result;
  double sum = doubles_sum(s, n);
  double max2 = doubles_max(s, n) / 2;
  double a = equation(s, n, sum);
  double b = equation(s, n, max2);
  assert(a <= 0);
  if (b >= 0)
    result = bisection(equation, s, n, sum, max2);
  else
  {
    double c = equation_other(s, n, max2);
    assert(c <= 0);
    double z = while_negative_value_duplicate(equation_other, s, n, max2);
    assert (equation_other(s, n, z) >= 0);
    result = bisection(equation_other, s, n, doubles_max(s, n) / 2, z);
  }
  return result;
}

// -------------------

int solve_for_vertices(const double *sides, int n, Point target, Point *p)
{
  assert(is_possible(sides, n));
  double a0 = point_angle(target);
  double r = circumference(sides, n);
//  printf("radius = %g\n", r);
  double a[n];  // angles
  angles(sides, n, r, a);
//  printf("angles:\n");
//  doubles_println_basic(a, n);
  assert(fabs(doubles_sum(a, n) - 2*MY_PI) < 0.0001 || fabs(doubles_sum(a, n) - 2 * doubles_max(a, n)) < 0.0001);
  // Handle the case where the angles do not add 2*PI
  if (fabs(doubles_sum(a, n) - 2 * doubles_max(a, n)) < 0.0001)
  {
    int iMax = doubles_argmax(a, n);
    a[iMax] = 2 * MY_PI - a[iMax];
  }
  assert(fabs(doubles_sum(a, n) - 2*MY_PI) < 0.0001);

//  printf("accumulated angles:\n");
  double accs[n+1];
  doubles_accumulate(a, n, accs);

//  doubles_println_basic(accs, n+1);
  Point vs[n];

  points_from_angles(accs, n, point(-r, 0), r, vs);
//  printf("points just computed:\n");
//  points_println(vs, n);
  double a1 = point_angle(vs[n-1]);
  int result = points_rotate(vs, n, a0-a1, p);
  return result;
}

int build_vectors(const double *sides, const double *angles, int n, Vector *vectors)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    vectors[result++]=from_polar(sides[i], angles[i]);
  return result;
}

int build_points(const Vector* vectors, int n, Point start, Point* z)
{
  int result = 0;
  z[result++] = start;
  for (int i = 0; i < n; i++)
  {
    z[result] = plus(z[result-1], vectors[i]);
    result++;
  }
  return result;
}

int solve_impossible(const double *sides, int n, Point target, double *a)
{
  double a0 = point_angle(target);
  double m = doubles_max(sides, n);
  if (m == sides[n-1])
    for (int i = 0; i < n-1; i++)  // n-1
      a[i] = a0;
  else
    for (int i = 0; i < n-1; i++)  // n-1
      if (m == sides[i])
        a[i] = a0;
      else
        a[i] = a0 + MY_PI;
  return n-1;
}

int solve(const double *sides, int n, Point target, Point *a)
{
  int b = is_possible(sides, n);
  if (b == 0)
  {
    double imp[n-1];  // Note, we only consider the segments, for this case.
    solve_impossible(sides, n, target, imp);
//    printf("Angles in impossible case:\n");
//    doubles_println_basic(imp, n-1);
    Vector vs[n-1];
    build_vectors(sides, imp, n-1, vs);
    build_points(vs, n-1, point(0, 0), a);
//    printf("Points in impossible case:\n");
//    points_println(a, n-1);

  }
  else
  {
    solve_for_vertices(sides, n, target, a);
  }
  return n-1;
}

Point computeTarget(const double *sides, const double *a, int n)
{
  Point result = point(0, 0);
  for (int i = 0; i < n; i++)
    result = plus(result, from_polar(sides[i], a[i]));
  return result;
}


// -------------------

#define MAX_SEGMENTS 30

void task_detailed(void)
{
  double sides[MAX_SEGMENTS];
  int n = doubles_get_some(sides, int_get());
  printf("Given segments\n");
  doubles_println_basic(sides, n);
  Point target = point_get();
  printf("Given target\n");
  point_println(target);
  sides[n++] = distance(target, point(0, 0));

  Point a[n];
  solve(sides, n, target, a);
  printf("List of points\n");
  points_println(a, n);  // Including the origin, for control...

  printf("Is there a solution? %s\n", (is_possible(sides, n) ? "YES" : "NO"));

  Point z = a[n-1];
  printf("Last point and target point:\n");
  point_println(z);
  point_println(target);
  printf("Distance (should be very close to zero, when there is a solution):\n");
  printf("%g\n", distance(target, z));
  assert(!is_possible(sides, n) || distance(target, z) < 0.0001);
}

// This works, by "miracle", even in the case where the target point is the origin,
// thanks to atan2(0, 0) being 0.0.

void task(void)
{
  double sides[MAX_SEGMENTS];
  int n = doubles_get_some(sides, int_get());
  Point target = point_get();
  sides[n++] = distance(target, point(0, 0));
  Point a[n];
  solve(sides, n, target, a);
  points_printf("%.3f %.3f\n", a+1, n-1);
}

// Note to myself:
// In order to run from the console, first cd as follows:
// cd ~/Dropbox/TAES_1617/projects/armsreach/work/
// Then use a command such as:
// ../../../../PI_1617/sources/armsreach.out B < ar_07_in.txt

int main(int argc, char **argv)
{
  char x = 'B';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    task_detailed();
  else if (x == 'B')
    task();
  else
    printf("Invalid option: %c.\n", x);
  return 0;
}
