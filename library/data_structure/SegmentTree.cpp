#include<functional>
#include<vector>

template<class M, class F = std::function<M(M, M)>>
class SegmentTree{
private:
  std::vector<M> data;
  F op;
  M e;
  int length;

public:
  SegmentTree(int n, const F op, const M& e) : op(op), e(e){
    length = 1;
    while(length < n) length <<= 1;
    data = std::vector<M>((length << 1) - 1, e);
  }

  void set(int index, const M& x){
    index += length - 1;
    data[index] = x;

    while(index){
      (--index) >>= 1;
      data[index] = op(data[(index << 1) + 1], data[(index << 1) + 2]);
    }
  }

  M get(int left, int right){
    M l = e, r = e;

    for(left += length - 1, right += length - 1; left < right; (--left) >>= 1, (--right) >>= 1){
      if(!(left & 1)) l = op(data[left++], l);
      if(!(right & 1)) r = op(data[--right], r);
    }

    return op(l, r);
  }
};


#include<algorithm>
#include<functional>
#include<iostream>
#include<vector>

using namespace std;

const int INF = 1e9 + 7;

int main(){
  int n;
  cin >> n;
  SegmentTree<int, std::function<int(int, int)>> segTree(n, [](int a, int b){return min(a, b);}, INF);

  while(true){
    int q;
    cin >> q;

    if(q == 0) break;
    else if(q == 1){
      int i, x;
      cin >> i >> x;
      segTree.update(i, x);
    }else if(q == 2){
      int l, r;
      cin >> l >> r;
      cout << segTree.query(l, r) << endl;
    }
  }

  return 0;
}
