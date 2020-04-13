class BinomialCoefficients{
  int max;
  int mod;
  long long *factorial;
  long long *factorial_inverse;
  long long *inverse;

public:
  int get(int n, int k){
    if(n < 0 || k < 0 || k > n) return 0;
    else return factorial[n] * (factorial_inverse[k] * factorial_inverse[n - k] % mod) % mod;
  }

  BinomialCoefficients(int max = 1'000'000, int mod = 1'000'000'007) : max(max), mod(mod){
    factorial = new long long[max + 1];
    factorial_inverse = new long long[max + 1];
    inverse = new long long[max + 1];

    factorial[0] = factorial[1] = 1;
    factorial_inverse[0] = factorial_inverse[1] = 1;
    inverse[1] = 1;

    for(int k = 2; k <= max; k++){
      factorial[k] = factorial[k - 1] * k % mod;
      inverse[k] = mod - inverse[mod % k] * (mod / k) % mod;
      factorial_inverse[k] = factorial_inverse[k - 1] * inverse[k] % mod;
    }
  }

  ~BinomialCoefficients(){
    delete [] factorial;
    delete [] factorial_inverse;
    delete [] inverse;
  }
};

#include<iostream>
int main(){
  BinomialCoefficients bc(10);
  bc.get(6, 3);
  std::cout << bc.get(2, 1) << std::endl;
}

