#include <array>
#include <cassert>
#include <climits>
#include <queue>
#include <vector>

using std::array;
using std::pair;
using std::priority_queue;
using std::vector;

/**
 * Assume we're given a list of buildings (s, h, e). We're asked to output the
 * skyline in the form (s, h).
 *
 * Assume the buildings are sorted in start order. We'll process buildings
 * left to right.
 *
 * Suppose we keep a ladder of building end points (e, h). This has
 * e0 < e1 < ... < em
 * h0 > h1 > ... > hm
 *
 */
vector<pair<int, int>> skyline(vector<array<int, 3>> &B) {
  priority_queue<pair<int, int>> Q;
  Q.emplace(0, INT_MAX);
  vector<pair<int, int>> sl;
  sl.reserve(2 * B.size());

  for (const auto [bs, bh, be] : B) {
    while (Q.top().second < bs) {
      const auto t = Q.top();
      while (Q.size() > 1 and Q.top().second <= t.second) Q.pop();
      sl.push_back({t.second, Q.top().first});
    }
    Q.emplace(bh, be);
    if (!sl.empty() and sl.back().first == bs and sl.back().second < bh)
      sl.back().second = bh;
    else if (sl.empty() or Q.top().first != sl.back().second)
      sl.push_back({bs, bh});
  }
  while (Q.size() > 1) {
    const auto t= Q.top();
    while (Q.size() > 1 and Q.top().second <= t.second) Q.pop();
    sl.push_back({t.second, Q.top().first});
  }
  return sl;
}

int main() {
  vector<array<int, 3>> B = {
      {2, 10, 9}, {3, 15, 7}, {5, 12, 12},
      {15, 10, 20}, {19, 8, 24},
  };
  assert((skyline(B) == vector<pair<int, int>>{
      {2, 10}, {3, 15}, {7, 12}, {12, 0},
      {15, 10}, {20, 8}, {24, 0},
  }));

  B = {{0, 3, 2}, {2, 3, 5}};
  assert((skyline(B) == vector<pair<int, int>>{{0, 3}, {5, 0}}));

  B = {{0, INT_MAX, INT_MAX}};
  assert((skyline(B) == vector<pair<int, int>>{{0, INT_MAX}, {INT_MAX, 0}}));
  return 0;
}
