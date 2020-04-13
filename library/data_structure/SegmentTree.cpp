#include<algorithm>

struct SegmentTree{
private:
  const int MAX = 1'000'000'000;

  int n;
  int* data;

public:
  SegmentTree(int n) : n(n){
    int d = 0;
    while(n >>= 1) d++;
    n = 1 << d;
    data = new int[n];
    for(int i = 0; i < n; i++) data[i] = MAX;
  }

  void update(int index, int x){
    index += n - 1;
    data[index] = x;
    while(index){
      index = (index - 1) >> 1;
      data[index] = std::min(data[(index << 1) + 1], data[(index << 1) + 2]);
    }
  }

  int query(int a, int b, int k, int l, int r){
    if(r <= a || b <= l) return MAX;
    if(a <= l && r <= b) return data[k];
    int vl = query(a, b, (k << 1) + 1, l, (l + r) >> 1);
    int vr = query(a, b, (k << 1) + 2, (l + r) >> 1, r);
    return std::min(vl, vr);
  }
};

int main(){
}

