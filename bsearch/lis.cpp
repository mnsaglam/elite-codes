/**
 * An example: Given a sequence, find the longest increasing subsequence.
 */
/**
 * Let h[l] be the smallest head of a length l increasing sequence.
 * Note that h[l] is non-decreasing in l. Now given a new element x,
 * find the largest l so that h[l] < x. We must have l+1 == j or h[l+1] >= x.
 * Now we have construct a l+1 sequence ending with x. So we set h[l+1] = x.
 *
 * This gives an O(n log n) solution with easy, in-place implementation.
 * Technically we're solving a predecessor problem, which can be done in
 * O(log log U) time.
 */

#include <vector>
#include <cassert>

using std::vector;

int lis(vector<int> &v) {
  int j = 0;
  for (int x : v) {
    int l = 0;
    for (int r = j; l < r;)
      if (const int m = l + (r - l) / 2; v[m] >= x) r = m;
      else l = m + 1;
    v[l] = x;
    if (l == j) ++j;
  }
  return j;
}

void test() {
  vector<int> v = {1, 3, 3, 2, 3, 5, 4};
  assert(lis(v) == 4);
}

int main() {
  test();
  return 0;
}
