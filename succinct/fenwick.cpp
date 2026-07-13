/**
 * From repo root
 *   g++ succinct/fenwick.cpp -std=c++23 -Wall -O3 && ./a.out
 *
 *    0  0000
 * 0000  0001
 * 0001  0010
 * 0010  0011
 * 0011  0100
 * 0100  0101
 * 0101  0110
 * 0110  0111
 * 0111  1000
 * 1000  1001
 * 1001  1010
 * 1010  1011
 * 1011  1100
 * 1100  1101
 * 1101  1110
 * 1110  1111
 * 1111 10000
 *
 * It's easier to reason about the 1 based fenwick, tho it's easier to implement
 * 0 based fenwick. So we'll reason on 1 based and translate by 1 when
 * implementing, when easier.
 *
 * In 1-based fenwick, we consider the binary decomposition of the prefix length
 * f[i] := a[i - low(i) + 1 .. i]
 *
 * We'll use an interface somewhat like make_heap(), pop_heap() and push_heap()
 * though with vector<int> references, not iterators, for clarity.
 * Implemented functions
 * - void make_fenwick(vector<int> &a)
 * - int prefix_sum_fenwick(const vector<int> &f, int i)
 * - int range_sum_fenwick(const vector<int> &f, int i, int j)
 * - void update_fenwick(vector<int> &f, int i, int delta)
 * - int upper_bound_fenwick(const vector<int> &f, int S)
 * - int lower_bound_fenwick(const vector<int> &f, int S)
 */

#include <cassert>
#include <iostream>
#include <vector>

using std::vector;

/**
 * Given an array a, converts it to the fenwick array in place, assuming no
 * overflow.
 */
void make_fenwick(vector<int> &a) {
  const int n = a.size();
  for (int i = 0; i < n; ++i)
    if (const int j = i | (i + 1); j < n)
      a[j] += a[i];
}

int prefix_sum_fenwick(const vector<int> &f, int i) {
  int sum = 0;
  for (; i >= 0; i = (i & (i + 1)) - 1)
    sum += f[i];
  return sum;
}

/**
 * Given a fenwick array f and [i, j], compute the inclusive sum[i..j].
 *
 * Lets think 1 based indices. Move --i so i is exclusive now.
 * i = w0x
 * j = w1y
 * First observe that the fenwick indices can meet at w00000.
 * We should move j side until w00000 which is the first moment j <= i. So move
 * j while j > i.
 *
 * Now if i==j, we're done--they've met at w00000. Otherwise, j = w0000
 * but i = w.nonzero. In this case we move i while i>j so eventually i=j=w0000.
 */
int range_sum_fenwick(const vector<int> &f, int i, int j) {
  --i;
  int sum = 0;
  for (; j > i; j = (j & (j + 1)) - 1)
    sum += f[j];
  for (; i > j; i = (i & (i + 1)) - 1)
    sum -= f[i];
  return sum;
}

void update_fenwick(vector<int> &f, int i, int delta) {
  assert(i >= 0 && "Ensure i >= 0");
  const int n = f.size();
  for (; i < n; i |= i + 1)
    f[i] += delta;
}

/**
 * Given a fenwick array f for a nonnegative array `a` and a prefix sum value S,
 * finds the smallest index i such that sum(a[0..i]) > S.
 */
int upper_bound_fenwick(const vector<int> &f, int S) {
  const int n = f.size();
  int i = 0, s = 1;
  while ((s << 1) <= n) s <<= 1;
  for (; s; s >>= 1)
    if (const int j = s + i; j <= n and f[j - 1] <= S) {
      S -= f[j - 1];
      i = j;
    }
  return i;
}

/**
 * Given a fenwick array f for a nonnegative array `a` and a prefix sum value S,
 * finds the smallest index i such that sum(a[0..i]) >= S.
 */
int lower_bound_fenwick(const vector<int> &f, int S) {
  const int n = f.size();
  int i = 0, s = 1;
  while ((s << 1) <= n) s <<= 1;
  for (; s; s >>= 1)
    if (const int j = s + i; j <= n and f[j - 1] < S) {
      S -= f[j - 1];
      i = j;
    }
  return i;
}

void print(const vector<int> &v) {
  for (const int i : v)
    std::cout << i << ", ";
  std::cout << "\n";
}

void test_basics(const vector<int> &v) {
  vector<int> f(v);
  vector<int> u(v);
  const int n = v.size();
  for (int i = 1; i < n; ++i)
    u[i] += u[i - 1];
  make_fenwick(f);
  for (int i = 0; i < n; ++i)
    assert(prefix_sum_fenwick(f, i) == u[i]);

  for (int i = 0; i < n; ++i)
    for (int j = i; j < n; ++j)
      assert(range_sum_fenwick(f, i, j) == (i == 0 ? u[j] : u[j] - u[i - 1]));
}

void test_update() {
  vector<int> f = {2, 3, 4, 5, 4, 3, 2, 1};
  make_fenwick(f);
  assert(range_sum_fenwick(f, 0, 3) == 14);
  update_fenwick(f, 0, -1);
  assert(range_sum_fenwick(f, 0, 3) == 13);
  update_fenwick(f, 1, 2);
  assert(range_sum_fenwick(f, 0, 3) == 15);
}

void test_lower_upper_bound() {
  vector<int> f = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1};
  make_fenwick(f);
  const int l = lower_bound_fenwick(f, 8);
  const int r = upper_bound_fenwick(f, 8);
  assert(l == 7 and r == 13);
  assert(lower_bound_fenwick(f, 9) == 13);
  assert(lower_bound_fenwick(f, 12) == f.size() - 1);
  assert(upper_bound_fenwick(f, 12) == f.size());
}

int main() {
  test_basics({1, 2, 3, 4, 5, 6});
  test_update();
  test_lower_upper_bound();
  return 0;
}
