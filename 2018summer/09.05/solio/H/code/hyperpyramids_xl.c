#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

//#define PRIME_NUMBER_LARGE 1000003
//#define PRIME_NUMBER_LARGE 10000019
#define PRIME_NUMBER_SMALL 99371
#define PRIME_NUMBER_LARGE 99371

int int_get(void)
{
  int result;
  scanf("%d", &result);
  return result;
}

int min(int x, int y)
{
  return x <= y ? x : y;
}

int max(int x, int y)
{
  return x <= y ? y : x;
}

int max3(int x, int y, int z)
{
  return max(x, max(y, z));
}

int ints_get(int *a)
{
  int result = 0;
  int x;
  while (scanf("%d", &x) != EOF)
    a[result++] = x;
  return result;
}

int ints_min(const int *a, int n)
{
  int result = INT_MAX;
  for (int i = 0; i < n; i++)
    if (result > a[i])
      result = a[i];
  return result;
}

void ints_print(const int *a, int n, char *separator)
{
  if (n > 0)
  {
    printf("%d", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      printf("%s%d", separator, a[i]);
  }
}

void ints_println(const int *a, int n, char *separator)
{
  ints_print(a, n, separator);
  printf("\n");
}

void ints_printf(const int *a, int n, const char *fmt)
{
  for (int i = 0; i < n; i++)
    printf(fmt, a[i]);
}

void ints_printfln(const int *a, int n, const char *fmt)
{
  ints_printf(a, n, fmt);
  printf("\n");
}

void lls_print(const long long *a, int n, char *separator)
{
  if (n > 0)
  {
    printf("%lld", a[0]);
    for (int i = 1; i < n; i++)  // i = 1
      printf("%s%lld", separator, a[i]);
  }
}

void lls_println(const long long *a, int n, char *separator)
{
  lls_print(a, n, separator);
  printf("\n");
}

void lls_printf(const long long *a, int n, const char *fmt)
{
  for (int i = 0; i < n; i++)
    printf(fmt, a[i]);
}

void lls_printfln(const long long *a, int n, const char *fmt)
{
  lls_printf(a, n, fmt);
  printf("\n");
}

int ints_sum(const int *a, int n)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    result += a[i];
  return result;
}

long long lls_sum(const long long *a, int n)
{
  long long result = 0;
  for (int i = 0; i < n; i++)
    result += a[i];
  return result;
}

char *str_dup(const char *s)
{
  char *result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

int ints_equal_arrays(const int *a, const int n, const int *b, int m)
{
  int result = n == m;
  int i = 0;
  while (result && i < n)
    if (a[i] != b[i])
      result = 0;
    else
      i++;
  return result;
}

int lls_equal_arrays(const long long *a, const int n, const long long *b, int m)
{
  int result = n == m;
  int i = 0;
  while (result && i < n)
    if (a[i] != b[i])
      result = 0;
    else
      i++;
  return result;
}

int ints_copy(const int *a, int n, int *b)
{
  if (n < 0)
    n = 0;
  memmove(b, a, n * sizeof(int));  // Note: 3rd arg is unsigned.
  return n;
}

int lls_copy(const long long *a, int n, long long *b)
{
  if (n < 0)
    n = 0;
  memmove(b, a, n * sizeof(long long));  // Note: 3rd arg is unsigned.
  return n;
}

int ints_cmp(const int *a, int n, const int *b, int m)
{
  int result;
  if (n == 0 || m == 0)
    result = n - m;
  else
  { result = a[0] - b[0];
    if (result == 0)
      result = ints_cmp(a+1, n-1, b+1, m-1);
  }
  return result;
}

int ints_cmp_i(const int *a, int n, const int *b, int m)
{
  int result = 0;
  int i = 0;
  int limit = min(n, m);
  while (result == 0 && i < limit)
  {
    result = a[i] - b[i];
    i++;
  }
  if (result == 0)
    result = n - m;
  return result;
}

long long lls_cmp_i(const long long *a, int n, const long long *b, int m)
{
  long long result = 0;
  int i = 0;
  int limit = min(n, m);
  while (result == 0 && i < limit)
  {
    result = a[i] - b[i];
    i++;
  }
  if (result == 0)
    result = n - m;
  return result;
}

int int_cmp_v1(const void *p, const void *q)
{
  return *(int *) p - *(int *) q;
}

void ints_qsort(int *a, int n)
{
  qsort(a, n, sizeof(int), int_cmp_v1);
}

int ll_cmp_v1(const void *p, const void *q)
{
  long long z = *(long long *) p - *(long long *) q;
  int result = (z >= 0) - (z <= 0);
  return result;
}

void lls_qsort(long long *a, int n)
{
  qsort(a, n, sizeof(long long), ll_cmp_v1);
}

int ints_count_while(const int *a, int n, int x)
{
  int result = 0;
  while (result < n && a[result] == x)
    result++;
  return result;
}

int lls_count_while(const long long *a, int n, long long x)
{
  int result = 0;
  while (result < n && a[result] == x)
    result++;
  return result;
}

int ints_unique(const int *a, int n, int *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = ints_count_while(a+i, n-i, a[i]);
    b[result++] = a[i];
    i += z;
  }
  return result;
}

int lls_unique(const long long *a, int n, long long *b)
{
  int result = 0;
  int i = 0;
  while (i < n)
  {
    int z = lls_count_while(a+i, n-i, a[i]);
    b[result++] = a[i];
    i += z;
  }
  return result;
}

// --------------

int *ints_new (int n)
{
  return (int *) malloc (n * sizeof(int));
}

long long *lls_new (int n)
{
  return (long long *) malloc (n * sizeof(long long));
}

int *ints_dup(const int *a, int n)
{
  int *result = ints_new(n);
  ints_copy(a, n, result);
  return result;
}

long long *lls_dup(const long long *a, int n)
{
  long long *result = lls_new(n);
  lls_copy(a, n, result);
  return result;
}

void ints_clear(int *a, int n)
{
  memset(a, 0, n * sizeof(int));
}

void lls_clear(long long *a, int n)
{
  memset(a, 0, n * sizeof(long long));
}

int ints_get_some(int *a, int n)
{
  int result = 0;
  int x;
  while (result < n && scanf("%d", &x) != EOF)
    a[result++] = x;
  return result;
}

int ints_id(int n, int *a)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = i;
  return result;
}

int ints_id_d(int n, int d, int *a)
{
  int result = 0;
  for (int i = 0; i < n; i++)
    a[result++] = i + d;
  return result;
}

int ints_hash(int *a, int n)
{
  unsigned int r = 0;
  for (int i = 0; i < n; i++)
  {
    r += a[i];
    r += r << 10;
    r ^= r >> 6;
  }
  r += r << 3;
  r ^= r >> 11;
  r += r << 15;
  return (int) r & ~(1 << 31);
}

void test_hash(void)
{
  int a[1000];
  int n = ints_get(a);
  int z = ints_hash(a, n);
  printf("%d\n", z);
}

//-----------

int rand_to(int n)  /* random numbers from 0 to n, inclusive */
// most recent version working on Mac. Not tested on Windows
{
  unsigned int m = (unsigned int) RAND_MAX + 1;
  // implicitly divide range [0..m] into n+1 ranges of w numbers:
  // [0..w-1], [w..2*w-1], [2*w..3*w-1], ... [n*w, (n+1)*w-1]
  unsigned int u_n = (unsigned int) n;
  unsigned int w = m / (u_n+1);
  // random numbers greater or equal to limit are ignored:
  unsigned int limit = (u_n+1) * w;
  int r;
  do
    // generate a random number:
    r = rand();
  // if greater than limit, ignore and repeat:
  while ((unsigned int)r >= limit);
  // compute the number of the range to which r belongs
  // this is a number in the range [0..n]
  // it's the random number we wanted:
  return r / w;
}

void ints_exchange(int *a, int x, int y)
{
  int m = a[x];
  a[x] = a[y];
  a[y] = m;
}

void ints_shuffle(int *a, int n)
{
  int i;
  for (i = 0; i < n-1; i++)
    ints_exchange(a, i, i+rand_to(n-1-i));
}

void ints_isort(int *a, int n)
{
  for (int i = 1; i < n; i++)
  {
    int j = i;
    while (j > 0 && a[j-1]> a[j])
    {
      ints_exchange(a, j-1, j);
      j--;
    }
  }
}

//-------------------

// First ascending list in lexicographical order summing sum, with the same number of elements as a,
// starting with x0, result in b.
// This is a list with all elements equal to x0, except the last, which will be chosen so that the sum is sum.
// Returns -1, if no such list can exist, else returns the number of elements of b, which should be
// the same as n

int first_list_up(const int *a, int n, int x0, int sum, int *b)
{
//  ints_println(a, n, ":");
//  printf("***%d %d\n", x0, sum);
  int result = -1;
  if (x0 <= sum)
  {
    if (n >= 2)
    {
      result = first_list_up(a+1, n-1, x0, sum-x0, b+1);
      if (result != -1)
      {
        *b = x0;
        result++;
      }
    }
    else if (n == 1)
    {
      *b = sum;
      result = 1;
    }
    else
      assert(0);
  }
  return result;
}

// Next ascending list in lexicographical order summing sum, from a, with n elements,
// result in in b, returning the number of elements, which should be n, or -1
// if there is no next list, i.e., if a is the last ascending list in
// lexicographical order, summing sum.
int next_list_up(const int *a, int n, int sum, int *b)
{
  int result = -1;
  if (n > 1)
  {
    if (*a < sum)
      result = next_list_up(a+1, n-1, sum-*a, b+1);
      if (result == -1)
        result = first_list_up(a, n, *a+1, sum, b);
      else
      {
        *b = *a;
        result++;
      }
  }
  return result;
}

void test_first_list_up(void)
{
  int a[1000];
  int n = ints_get(a);
  int b[1000];
  int m = first_list_up(a, n, *a+1, ints_sum(a, n), b);
  if (m == -1)
    printf("Impossible.\n");
  else
    ints_println(b, m, ",");
}

void test_next_list_up(void)
{
  int a[1000];
  int n = ints_get(a);
  int b[1000];
  int m = next_list_up(a, n, ints_sum(a, n), b);
  if (m == -1)
    printf("Impossible.\n");
  else
    ints_println(b, m, ",");
}

// List of all ascending lists of length n, summing sum
int all_ascending_lists_summing(int **a, int n, int sum)
{
  int result = 0;
  a[result] = ints_new(n);
  ints_clear(a[result], n);
  a[0][n-1] = sum;
  result++;
  int done = 0;
  do {
    a[result] = ints_new(n);
    int c = next_list_up(a[result-1], n, sum, a[result]);
    if (c == -1)
      done = 1;
    else
      result++;
  } while (!done);
  return result;
}

void test_all_ascending_lists_summing(void)
{
  int *a[10000];
  int length = int_get();
  int sum = int_get();
  int n = all_ascending_lists_summing(a, length, sum);
  printf("%d\n", n);
  for (int i = 0; i < n; i++)
    ints_println(a[i], length, " ");
}

int ints_all_zero(int *a, int n)
{
  for (int i = 0; i < n; i++)
    if (a[i] != 0)
      return 0;
  return 1;
}

int listnomial(int *a, int n)
{
  //  printf("*** ");
  //  ints_println(a, n, " ");
  int result = 1;
  if (!ints_all_zero(a, n))
  {
    result = 0;
    for (int i = 0; i < n; i++)
      if (a[i] > 0)
      {
        a[i]--;
        result += listnomial(a, n);
        a[i]++;
      }
  }
  return result;
}

void test_listnomial(void)
{
  int a[1000];
  int n = ints_get(a);
  int z = listnomial(a, n);
  printf("%d\n", z);
}

int trinomial(int x, int y, int z)
{
  int a[] = {x, y, z};
  return listnomial(a, 3);
}

typedef struct {
  int **keys;
  int key_length;
  int *values;
  int capacity;
  int count;
} Hashtable;

void hashtable_make(int capacity, int key_length, Hashtable *ht)
{
  ht->keys = (int **) calloc (capacity, sizeof(int*));  // clears memory.
  ht->key_length = key_length;
  ht->values = ints_new(capacity);
  ht->capacity = capacity;
  ht->count = 0;
}

int hash_find(Hashtable *ht, int *key)
{
  int result = ints_hash(key, ht->key_length) % ht->capacity;
  while (ht->keys[result] && ints_cmp_i(ht->keys[result], ht->key_length, key, ht->key_length))
    result = (result+1) % ht->capacity;
  return result;
}

int hash_get(Hashtable *ht, int *key)
{
  int z = hash_find(ht, key);
  return ht->keys[z] ? ht->values [z] : -1;
}

int hash_put(Hashtable *ht, int *key, int value)
{
  assert(ht->count < ht->capacity);
  int result = 0;
  int k = hash_find(ht, key);
  result = !ht->keys[k];
  if (result)
  {
    ht->keys[k] = ints_dup(key, ht->key_length);
    ht->values[k] = value;
    ht->count++;
  }
  return result;
}

typedef struct {
  int **keys;
  int key_length;
  long long *values;
  int capacity;
  int count;
} Hashtable_XL;

void hashtable_XL_make(int capacity, int key_length, Hashtable_XL *ht)
{
  ht->keys = (int **) calloc (capacity, sizeof(int*));  // clears memory.
  ht->key_length = key_length;
  ht->values = lls_new(capacity);
  ht->capacity = capacity;
  ht->count = 0;
}

int hash_XL_find(Hashtable_XL *ht, int *key)
{
  int result = ints_hash(key, ht->key_length) % ht->capacity;
  while (ht->keys[result] && ints_cmp_i(ht->keys[result], ht->key_length, key, ht->key_length))
    result = (result+1) % ht->capacity;
  return result;
}

long long hash_XL_get(Hashtable_XL *ht, int *key)
{
  int z = hash_XL_find(ht, key);
  return ht->keys[z] ? ht->values [z] : -1;
}

int hash_XL_put(Hashtable_XL *ht, int *key, long long value)
{
  assert(ht->count < ht->capacity);
  int result = 0;
  int k = hash_XL_find(ht, key);
  result = !ht->keys[k];
  if (result)
  {
    ht->keys[k] = ints_dup(key, ht->key_length);
    ht->values[k] = value;
    ht->count++;
  }
  return result;
}

int listnomial_memo(int *a, int n, Hashtable *memo)
{
//  printf("*** ");
//  ints_println(a, n, " ");
  int result = 1;
  if (!ints_all_zero(a, n))
  {
    result = hash_get(memo, a);
    if (result == -1)
    {
      result = 0;
      for (int i = 0; i < n; i++)
        if (a[i] > 0)
        {
          a[i]--;
          result += listnomial_memo(a, n, memo);
          a[i]++;
        }
      hash_put(memo, a, result);
    }
  }
  return result;
}

// This is required to bootstrap the memo, so to speak...
void memo_init(Hashtable *memo)
{
  int a[memo->capacity];
  ints_clear(a, memo->capacity);
  hash_put(memo, a, 1);
}

void test_listnomial_memo(void)
{
  int a[1000];
  int n = ints_get(a);
  Hashtable memo;
  hashtable_make(PRIME_NUMBER_SMALL, n, &memo);
  memo_init(&memo);
  int z1 = listnomial(a, n);
  printf("%d\n", z1);
  int z2 = listnomial_memo(a, n, &memo);
  printf("%d\n", z1);
  printf("%d\n", z2);
  printf("-->%d\n", memo.count);
}

long long listnomial_XL_memo(int *a, int n, Hashtable_XL *memo)
{
  //  printf("*** ");
  //  ints_println(a, n, " ");
  long long result = 1;
  if (!ints_all_zero(a, n))
  {
    result = hash_XL_get(memo, a);
    if (result == -1)
    {
      result = 0;
      for (int i = 0; i < n; i++)
        if (a[i] > 0)
        {
          a[i]--;
          result += listnomial_XL_memo(a, n, memo);
          a[i]++;
        }
      hash_XL_put(memo, a, result);
    }
  }
  return result;
}

long long listnomial_XXL_memo(int *a, int n, Hashtable_XL *memo)
{
  //  printf("*** ");
  //  ints_println(a, n, " ");
  long long result = 1;
  int b[n];
  if (!ints_all_zero(a, n))
  {
    result = hash_XL_get(memo, a);
    if (result == -1)
    {
      result = 0;
      for (int i = 0; i < n; i++)
        if (a[i] > 0)
        {
          a[i]--;
          ints_copy(a, n, b);
          ints_isort(b, n);
          result += listnomial_XL_memo(b, n, memo);
          a[i]++;
        }
      hash_XL_put(memo, a, result);
    }
  }
  return result;
}

void memo_XL_init(Hashtable_XL *memo)
{
  int a[memo->capacity];
  ints_clear(a, memo->capacity);
  hash_XL_put(memo, a, 1);
}

void test_listnomial_XL_memo(void)
{
  int a[1000];
  int n = ints_get(a);
  Hashtable_XL memo;
  hashtable_XL_make(PRIME_NUMBER_LARGE, n, &memo);
  memo_XL_init(&memo);
  long long z2 = listnomial_XL_memo(a, n, &memo);
  printf("%lld\n", z2);
  printf("-->%d\n", memo.count);
}

// Solve the problem for a hyperpyramid with given dimension and height.
// The result is the unique numbers at the bottom of the hyperpyramid.
// The strategy here is to create first all the ascending lists of powers
// for the coefficients, and then compute from top to bottom, so to speak.
// As such, we are filling the memo in "natural order".

int task(int dimension, int height, int *p)
{
  Hashtable memo;
  hashtable_make(PRIME_NUMBER_SMALL, dimension, &memo);
  memo_init(&memo);
  for (int i = 0; i < height; i++)
  {
    int *a = ints_new(dimension);
    ints_clear(a, dimension);
    a[dimension-1] = i;
    int done = 0;
    do {
      listnomial_memo(a, dimension, &memo);  // return value is discarded.
      int *b = ints_new(dimension);
      int c = next_list_up(a, dimension, i, b);
      if (c == -1)
        done = 1;
      else
        ints_copy(b, dimension, a);
    } while (!done);
  }

//  printf("memo count %d\n", memo.count);

  int result = 0;
  for (int i = 0; i < memo.capacity; i++)
  {
    if (memo.keys[i] && ints_sum(memo.keys[i], dimension) == height - 1)
      p[result++] = memo.values[i];
  }
  ints_qsort(p, result);
  result = ints_unique(p, result, p);
  return result;
}

void test_task(int dimension, int height)
{
  printf("!!!!%d %d\n", dimension, height);
  int a[10000];
  int n = task(dimension, height, a);
  printf("-->%d\n", n);
  ints_println(a, n, " ");
}

int task_XL(int dimension, int height, long long *p)
{
  Hashtable_XL memo;
  hashtable_XL_make(PRIME_NUMBER_LARGE, dimension, &memo);
  memo_XL_init(&memo);
  for (int i = 0; i < height; i++)
  {
    int *a = ints_new(dimension);
    ints_clear(a, dimension);
    a[dimension-1] = i;
    int done = 0;
    do {
      listnomial_XL_memo(a, dimension, &memo);  // return value is discarded.
      int *b = ints_new(dimension);
      int c = next_list_up(a, dimension, i, b);
      if (c == -1)
        done = 1;
      else
        ints_copy(b, dimension, a);
    } while (!done);
  }

//  printf("memo count %d\n", memo.count);

  int result = 0;
  for (int i = 0; i < memo.capacity; i++)
  {
    if (memo.keys[i] && ints_sum(memo.keys[i], dimension) == height - 1)
      p[result++] = memo.values[i];
  }
  lls_qsort(p, result);
  result = lls_unique(p, result, p);
  return result;
}

void test_task_XL(int dimension, int height)
{
  printf("!!!!%d %d\n", dimension, height);
  long long a[10000];
  int n = task_XL(dimension, height, a);
  printf("-->%d\n", n);
  lls_println(a, n, " ");
  if (a[n-1] > INT_MAX)
    return;
  int b[10000];
  int m = task(dimension, height, b);
  printf("-->%d\n", m);
  ints_println(b, m, " ");
}

int task_XXL(int dimension, int height, long long *p)
{
  Hashtable_XL memo;
  hashtable_XL_make(PRIME_NUMBER_LARGE, dimension, &memo);
  memo_XL_init(&memo);
  for (int i = 0; i < height; i++)
  {
    int *a = ints_new(dimension);
    ints_clear(a, dimension);
    a[dimension-1] = i;
    int done = 0;
    do {
      listnomial_XXL_memo(a, dimension, &memo);  // return value is discarded.
      int *b = ints_new(dimension);
      int c = next_list_up(a, dimension, i, b);
      if (c == -1)
        done = 1;
      else
        ints_copy(b, dimension, a);
    } while (!done);
  }

//  printf("memo count %d\n", memo.count);

  int result = 0;
  for (int i = 0; i < memo.capacity; i++)
  {
    if (memo.keys[i] && ints_sum(memo.keys[i], dimension) == height - 1)
      p[result++] = memo.values[i];
  }
  lls_qsort(p, result);
  result = lls_unique(p, result, p);
  return result;
}

void test_task_XXL(int dimension, int height)
{
  printf("!!!!%d %d\n", dimension, height);
  long long a[10000];
  int n = task_XXL(dimension, height, a);
  printf("-->%d\n", n);
  lls_println(a, n, " ");
  if (a[n-1] > INT_MAX)
    return;
  int b[10000];
  int m = task(dimension, height, b);
  printf("-->%d\n", m);
  ints_println(b, m, " ");
}

void test_all_XXL(void)
{
  long long a[10000];
  for (int d = 2; d < 32; d++)
  {
    printf("-------> %d\n", d);
    int h = 1;
    do {
      printf("h = %d ---", h);
      int n = task_XXL(d, h, a);
      printf("n = %d\n", n);
      //      printf("a[0] = %lld\n", a[0]);
      h++;
    } while (a[0] >= 0); // if a[0] < 0 then there has been overflow;
  }
}

void test_all_limits(void)
{
  long long a[10000];
  for (int d = 2; d < 32; d++)
  {
    int h = 1;
    do {
      task_XXL(d, h, a);
      if (a[0] < 0) break;
      h++;
    } while (1);
    h -= 1;
    int n = task_XXL(d, h, a);
    printf("%2d %5d %6d %20lld\n", d, h, n, a[n-1]);
  }
}

void the_task(void)
{
  int dimension = int_get();
  int height = int_get();
  long long a[10000];
  int n = task_XXL(dimension, height, a);
  lls_println(a, n, "\n");
}

// display 3D pyramids up to height t
void show_pyramids(int t)
{
  for (int h = 1; h <= t; h++)
  {
    for (int ij = 0; ij < h; ij++){
      for (int j = 0; j <= ij; j++)
        printf(" %d", trinomial(j, ij-j, h-1-ij));
      printf("\n");
    }
    printf("\n");
  }
}


//-------------------

int main(int argc, char **argv)
{

#ifndef pguerr_original
  the_task(); 
#else
//  srand(111111111UL);
//  rand(); rand();
  int x = 'H';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    test_first_list_up();
  else if (x == 'B')
    test_next_list_up();
  else if (x == 'C')
    test_all_ascending_lists_summing();
  else if (x == 'D')
    test_listnomial();
  else if (x == 'E')
    test_hash();
  else if (x == 'F')
    test_listnomial_memo();
  else if (x == 'G')
    test_task(atoi(argv[2]), atoi(argv[3]));
  else if (x == 'H')
    test_task_XL(atoi(argv[2]), atoi(argv[3]));
  else if (x == 'I')
    test_all_XXL();
  else if (x == 'J')
    test_all_limits();
  else if (x == 'K')
    show_pyramids(atoi(argv[2]));
  else if (x == 'Z')
    the_task();
  else
    printf("Invalid option: %s.\n", argv[1]);
#endif
  return 0;

}

