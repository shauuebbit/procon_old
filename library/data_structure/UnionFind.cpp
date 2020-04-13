#include<vector>

struct UnionFind{
private:
  std::vector<int> data;

public:
  UnionFind(int n = 0) : data(n, -1){}

  int find(int x){
    return data[x] < 0 ? x : data[x] = find(data[x]);
  }

  bool unite(int x, int y){
    x = find(x); y = find(y);

    if(x == y) return false;
    else{
      if(data[x] > data[y]) std::swap(x, y);
      data[x] += data[y];
      data[y] = x;
      return true;
    }
  }

  bool is_same(int x, int y){
    return find(x) == find(y);
  }

  int size(int x){
    return -data[find(x)];
  }
};

int main(){}
