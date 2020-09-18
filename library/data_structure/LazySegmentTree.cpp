#include <functional>

template <class M, class E, class F = std::function<M(M, M)>, class A = std::function<M(M, E)>, class G = std::function<E(E, E)>>
class LazySegmentTree {
private:
  M* data;
  E* lazy;
  F op;
  G cp;
  A act;
  M e;
  E id;
  int sz;

  void propagate(int index) {
    if (lazy[index] == id) return;
    lazy[index << 1] = cp(lazy[index << 1], lazy[index]);
    lazy[(index << 1) | 1] = cp(lazy[(index << 1) | 1], lazy[index]);
    data[index] = act(data[index], lazy[index]);
    lazy[index] = id;
  }

  void propagate_topdown(int index) {
    int h = 0;
    for (int i = 1; i < index; i <<= 1) ++h;
    for (int i = h; i; i--) propagate(index >> i); 
  }

  void recalc(int index) { while (index >>= 1) data[index] = op(act(data[index << 1], lazy[index << 1]), act(data[(index << 1) | 1], lazy[(index << 1) | 1])); }

public:
  LazySegmentTree(int sz, const F& op, const A& act, const G& cp, const M& e, const E& id) : op(op), act(act), cp(cp), e(e), id(id), sz(sz) {
    data = new M[sz << 1];
    lazy = new E[sz << 1];
    for (int i = 0; i < (sz << 1); i++) data[i] = e;
    for (int i = 0; i < (sz << 1); i++) lazy[i] = id;
  }

  void update(int left, int right, const E& x) {
    if (left < 0) left = 0;
    if (right > sz) right = sz;
    left += sz; right += sz;

    propagate_topdown(left);
    propagate_topdown(right - 1);

    for (int l = left, r = right; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        lazy[l] = cp(lazy[l], x);
        ++l;
      }
      if (r & 1) {
        --r;
        lazy[r] = cp(lazy[r], x);
      }
    }

    recalc(left);
    recalc(right);
  }

  M query(int left, int right) {
    if (left < 0) left = 0;
    if (right > sz) right = sz;
    left += sz; right += sz;

    propagate_topdown(left);
    propagate_topdown(right - 1);

    M l = e, r = e;

    for (; left < right; left >>= 1, right >>= 1) {
      if (left & 1) {
        l = op(l, act(data[left], lazy[left]));
        ++left;
      }
      if (right & 1) {
        --right;
        r = op(act(data[right], lazy[right]), r);
      }
    }

    return op(l, r);
  }

  ~LazySegmentTree() {
    delete[] data;
    delete[] lazy;
  }
};


#include <algorithm>
#include <iostream>

using namespace std;

const int INF = 1e9 + 7;

int main() {
  int n;
  cin >> n;

  auto f = [](int a, int b) {
    return min(a, b);
  };

  auto g = [](int a, int b) {
    if (b == INF) return a;
    else return b;
  };

  LazySegmentTree<int, int, decltype(f), decltype(g), decltype(g)> segTree(n, f, g, g, INF, INF);

  while (true) {
    int q;
    cin >> q;

    if (q == 0) break;
    else if (q == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      segTree.update(l, r, x);
    } else if (q == 2) {
      int l, r;
      cin >> l >> r;
      cout << segTree.query(l, r) << endl;
    }
  }

  return 0;
}

