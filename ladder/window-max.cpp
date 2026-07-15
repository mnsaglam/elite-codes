/**
 * Suppose we're given an array a, and an integer k and we're asked to output
 * the maximum of each window of size k.
 *
 * Given a window, consider its max cartesian tree. In particular consider the
 * right-right traversal: max element, max element to the right of max etc.
 *
 * We can keep these values with multiplicities (instead of indices)
 */

#include <cassert>
#include <vector>

using std::vector;

/**
 * A k-window_max implementation using k-1 extra space and two pointers with
 * empty vs full encoding.
 */
vector<int> window_max(vector<int> &a, int k) {
  const int n = a.size(), K = k - 1;
  if (K == 0) return a;
  vector<int> w(K);
  int s = 0, t = 0; // 0 <= s <= t < 2K
                    // deq is empty iff s==t

  const auto mod = [K](int v) { return v >= K ? v - K : v; };

  for (int i = 0; i < n; ++i) {
    while (s != t and w[mod(t - 1)] < a[i]) --t;
    if (i >= K) {
      if (s == t) a[i - K] = a[i];
      else if (a[i - K] == w[mod(s)]) ++s; // tail evicted
      else a[i - K] = w[mod(s)]; // maximum updated
    }
    w[mod(t)] = a[i];
    if (++t == 2 * K) { t -= K; s -= K; }
  }
  a.resize(n - K);
  return a;
}

void test_basics() {
  vector<int> u = {1, 3, -1, -3, 5, 3, 6, 7};
  vector<int> v = {3, 3, 5, 5, 6, 7};
  assert(window_max(u, 3) == v);

  u = {4, -2, 7, 1};
  v = {4, -2, 7, 1};
  assert(window_max(u, 1) == v);

  u = {4, -2, 7, 1};
  v = {7};
  assert(window_max(u, 4) == v);

  u = {-5, -2, -3, -4};
  v = {-2, -2, -3};
  assert(window_max(u, 2) == v);

  u = {2, 2, 2, 2};
  v = {2, 2, 2};
  assert(window_max(u, 2) == v);
}

int main() {
  test_basics();
  return 0;
}
