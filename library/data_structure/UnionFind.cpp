#include <vector>

class UnionFind {
private:
  int* data;

public:
  UnionFind(int n = 0) {
    data = new int[n];
    for (int i = 0; i < n; i++) data[i] = -1;
  }

  int find(int x) {
    return data[x] < 0 ? x : data[x] = find(data[x]);
  }

  bool unite(int x, int y) {
    x = find(x); y = find(y);

    if (x == y) return false;
    else {
      if(data[x] > data[y]) std::swap(x, y);
      data[x] += data[y];
      data[y] = x;
      return true;
    }
  }

  bool is_same(int x, int y) {
    return find(x) == find(y);
  }

  int size(int x) {
    return -data[find(x)];
  }

  ~UnionFind() {
    delete[] data;
  }
};

int main() {
  UnionFind uf(10);
}
