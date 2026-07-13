#include <cassert>

/**
 * Setup: Assume a monotone predicate p: {0,1,...,n-1} -> {true, false} is
 * given. By monotone, I mean for i < j, p(i) => p(j).
 * Output the first index i such that p(i) = true. By convention, we define
 * p(n) = true so if the original predicate is false, we output n.
 *
 * With the convention p(n) = true, there is always a true, therefore a leftmost
 * true--denote that by i*.
 */

/**
 * Invariant: l <= i* <= r
 * Note: this middle point selection is delicate. m = (r+l+1)/2 would infinite
 * loop, for instance.
 */
int bisect(int n, auto &&p) {
  int l = 0, r = n;
  while (l < r)
    if (const int m = l + (r - l) / 2; p(m)) r = m;
    else l = m + 1;
  return l;
}

/**
 * Invariant: After the if line, we have i <= i* < i+s.
 * After the last iteration, i <= i* < i + 1.
 */
int lift(int n, auto &&p) {
  int i = 0, s = 1;
  while (s << 1 <= n) s <<= 1;
  for (; s; s >>= 1)
    if (const int j = i + s; j <= n and !p(j - 1)) i = j;
  return i;
}

void test_equivalence() {
  for (int i = 0, n = 100; i <= n; ++i) {
    const auto p = [i](int x) { return x >= i; };
    assert(bisect(n, p) == i and i == lift(n, p));
  }
}

int main() {
  test_equivalence();
  return 0;
}
