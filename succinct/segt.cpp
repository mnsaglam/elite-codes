/**
 * Here is a segment tree implementation for querying the maximum of any range
 * with dynamic updates in O(log n) query and update time.
 *
 * For min, max, with monotone updates (increase in max case and decrease in
 * min case) there is also a double fenwick tree solution which is slightly
 * faster.
 */

#include <cassert>
#include <vector>
#include <iostream>

using std::vector;
using std::max;

vector<int> make_segt(const vector<int> &a) {
  const int n = a.size();
  vector<int> s(2 * n);
  for (int i = 0; i < n; ++i) s[i + n] = a[i];
  for (int i = n - 1; i > 0; --i)
    s[i] = max(s[2*i], s[2*i + 1]);
  return s;
}

void update_segt(vector<int> &s, int i, int val) {
  const int n = s.size();
  for (s[i += n] = val; i > 1; i >>= 1)
    s[i >> 1] = max(s[i], s[i ^ 1]);
}

int range_max_segt(const vector<int> &s, int l, int r) {
  const int n = s.size() >> 1;
  int res = INT_MIN;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) res = max(res, s[l++]);
    if (r & 1) res = max(res, s[--r]);
  }
  return res;
}

void print(const vector<int> &v) {
  for (const int i : v)
    std::cout << i << ", ";
  std::cout << "\n";
}

void test_basics() {
  vector<int> s = make_segt({0, 0, 1, 2});
  assert(range_max_segt(s, 0, 2) == 0);
  assert(range_max_segt(s, 0, 3) == 1);
  assert(range_max_segt(s, 0, 4) == 2);

  update_segt(s, 0, 3);
  assert(range_max_segt(s, 0, 2) == 3);
  assert(range_max_segt(s, 0, 3) == 3);
  assert(range_max_segt(s, 0, 4) == 3);
}

int main() {
  test_basics();
  return 0;
}
