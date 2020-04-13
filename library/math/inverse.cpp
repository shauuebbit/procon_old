#include<utility>

const int mod = 1'000'000'007;

template<typename T>
T inverse(T a, T m){
  T u = 0, v = 1;

  while(a){
    T t = m / a;
    m -= t * a; std::swap(a, m);
    u -= t * v; std::swap(u, v);
  }
  
  u %= mod;
  if(u < 0) u += mod;

  return u;
}

template<typename T>
T inverse(T a){
  return inverse(a, mod);
}

#include<iostream>
int main(){std::cout<<5*inverse(5)%mod<<std::endl;}

