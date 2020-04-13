constexpr long long mod = 1'000'000'007;

constexpr long long power(long long b, long long e, long long mod){
  long long ret = 1;
  while(e){
    if(e & 1){
      ret *= b;
      ret %= mod;
      e--;
    }

    b *= b;
    b %= mod;
    e >>= 1;
  }

  return ret;
}

constexpr long long power(long long b, long long e){
  return power(b, e, mod);
}


#include<iostream>
int main(){
  std::cout<<power(3,4)<<' '<<power(3,5)<<std::endl;
}
