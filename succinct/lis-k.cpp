/**
 * We're given an array a, and an integer k.
 * Find the longest subsequence so that
 *  - the subsequence is strictly increasing
 *  - the difference between adjacent elements is at most k.
 *
 * This is 2407 on LeetCode (https://leetcode.com/problems/longest-increasing-subsequence-ii/).
 */

#include <algorithm>
#include <cassert>
#include <vector>

using std::vector;
using std::max;

int lis_k(const vector<int> &a, int k) {
  const int m = *max_element(a.begin(), a.end()) + 1;
  int lis = 0;
  for (vector<int> s(2 * m); int x : a) {
    int l = m + max(x - k, 0);
    int r = m + x;
    int M = 0; // range maximum that we'll compute
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) M = max(M, s[l++]);
      if (r & 1) M = max(M, s[--r]);
    }
    int u = m + x;
    if (++M <= s[u]) continue;
    lis = max(lis, M);
    for (s[u] = M; u > 1; u >>= 1)
      if (const int pv = max(s[u], s[u ^ 1]); pv == s[u >> 1]) break;
      else s[u >> 1] = pv;
  }
  return lis;
}

void test() {
  assert(lis_k({5, 4, 3, 3, 2, 3}, 1) == 2);
  assert(lis_k(
    {7,4,5,1,8,12,4,7,2,3,4,5,6,7,8,9,8,13,15,14,17,14,12}, 5) == 12);
  assert(lis_k({1}, 1) == 1);
  assert(lis_k({5,4,3,3,2,3}, 1) == 2);
}

int main() {
  test();
  return 0;
}
