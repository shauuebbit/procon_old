#include<functional>

template<class M, class F = std::function<M(M, M)>>
class SegmentTree{
private:
  M* data;
  F op;
  M e;
  int length;

public:
  SegmentTree(int n, const F op, const M& e) : op(op), e(e){
    length = 1;
    while(length < n) length <<= 1;
    data = new M[length << 1];
    for(int i = 0; i < (length << 1); i++) data[i] = e;
  }

  void update(int index, const M& x){
    index += length;
    data[index] = x;

    while(index >>= 1){
      data[index] = op(data[index << 1], data[(index << 1) | 1]);
    }
  }

  M query(int left, int right){
    M l = e, r = e;

    for(left += length, right += length; left < right; left >>= 1, right >>= 1){
      if(left & 1) l = op(data[left++], l);
      if(right & 1) r = op(data[--right], r);
    }

    return op(l, r);
  }

  ~SegmentTree(){
    delete[] data;
  }
};


#include<algorithm>
#include<iostream>

using namespace std;

const int INF = 1e9 + 7;

int main(){
  int n;
  cin >> n;

//  SegmentTree<int> segTree(n, [](int a, int b){return min(a, b);}, INF);
//  SegmentTree<int, std::function<int(int, int)>> segTree(n, [](int a, int b){return min(a, b);}, INF);
  auto f = [](int a, int b){
    return min(a, b);
  };
  SegmentTree<int, decltype(f)> segTree(n, f, INF);

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

