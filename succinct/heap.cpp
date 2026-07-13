#include <cassert>
#include <utility>
#include <vector>

using std::vector;

template <typename T>
void percolate_down(vector<T> &h, int i, int n) {
  T el = std::move(h[i]);
  while (true) {
    int j = 2 * i + 1;
    if (j >= n) break;
    if (j + 1 < n and h[j] < h[j + 1]) ++j;
    if (!(el < h[j])) break;
    h[i] = std::move(h[j]);
    i = j;
  }
  h[i] = std::move(el);
}

template <typename T>
void percolate_up(vector<T> &h, int i) {
  if (i == 0 or !(h[(i - 1) / 2] < h[i])) return;

  T el = std::move(h[i]);
  do {
    const int p = (i - 1) / 2;
    h[i] = std::move(h[p]);
    i = p;
  } while (i > 0 and h[(i - 1) / 2] < el);
  h[i] = std::move(el);
}

template <typename T>
bool is_heap(const vector<T> &h) {
  const int n = h.size();
  for (int i = 1; i < n; ++i)
    if (h[(i - 1) / 2] < h[i]) return false;
  return true;
}

template <typename T>
void make_heap(vector<T> &a) {
  const int n = a.size();
  for (int i = n / 2; i-- > 0;)
    percolate_down(a, i, n);
}

template <typename T>
void pop_heap(vector<T> &h) {
  const int n = h.size();
  if (n < 2) return;

  T top = std::move(h.front());
  int i = 0;

  // Move the hole to a leaf; the tail stays intact unless it is that leaf.
  for (int j; (j = 2 * i + 1) < n; i = j) {
    if (j + 1 < n and h[j] < h[j + 1]) ++j;
    h[i] = std::move(h[j]);
  }

  if (i != n - 1) {
    while (i > 0 and h[(i - 1) / 2] < h.back()) {
      const int p = (i - 1) / 2;
      h[i] = std::move(h[p]);
      i = p;
    }
    h[i] = std::move(h.back());
  }
  h.back() = std::move(top);
}

template <typename T>
void push_heap(vector<T> &h) {
  const int n = h.size();
  if (n > 1)
    percolate_up(h, n - 1);
}

void test_make_heap() {
  vector<int> h = {0, 3, 2, 1, 6, 4, 5};
  make_heap(h);
  assert(is_heap(h));
  assert(h.front() == 6);
}

void test_push_heap() {
  vector<int> h = {8, 6, 7, 1, 4, 3, 5};
  assert(is_heap(h));
  h.push_back(9);
  push_heap(h);
  assert(is_heap(h));
  assert(h.front() == 9);
}

void test_pop_heap() {
  vector<int> h = {9, 6, 8, 1, 4, 7, 3};
  assert(is_heap(h));
  pop_heap(h);
  assert(h.back() == 9);
  h.pop_back();
  assert(is_heap(h));
}

void test_heap_sort() {
  vector<int> h = {0, 3, 2, 1, 6, 4, 5};
  vector<int> popped;
  make_heap(h);
  while (!h.empty()) {
    pop_heap(h);
    popped.push_back(h.back());
    h.pop_back();
    assert(is_heap(h));
  }
  for (int i = 1; i < static_cast<int>(popped.size()); ++i)
    assert(popped[i - 1] >= popped[i]);
}

int main() {
  test_make_heap();
  test_push_heap();
  test_pop_heap();
  test_heap_sort();
  return 0;
}
