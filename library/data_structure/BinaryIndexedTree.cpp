template<typename T>
struct BinaryIndexedTree{
private:
  int n;
  T *data;

public:
  BinaryIndexedTree(int n = 0) : n(n){
    data = new T[n + 1];
    for(int i = 0; i <= n; i++) data[i] = 0;
  }

  bool add(int index, T x = 1){
    if(index < 0 || n < index) return false;
    for(;index <= n; index += index & -index){
      data[index] += x;
    }
    return true;
  }

  T sum(int index){
    if(index < 0) index = 0;
    else if(index > n) index = n;

    T x = 0;
    for(;index; index -= index & -index){
      x += data[index];
    }
    return x;
  }
  
  int lower_bound(T x){
    if(x <= 0) return 0;
    
    int index = 0, b = 1;
    while((b << 1) <= N) b <<= 1;
    
    while(b){
      if(index + b <= N && data[index + b] < x){
        x -= data[index + b];
        index += b;
      }
      b >>= 1;
    }
    return index + 1;
  }

  ~BinaryIndexedTree(){
    delete [] data;
  }
};

int main(){}

