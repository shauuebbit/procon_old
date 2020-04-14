template<typename T, typename U>
T gcd(T a, U b){
  if(a < b){
    a ^= b;
    b ^= a;
    a ^= b;
  }

  T r;
  while(b){
    r = a % b;
    a = b;
    b = r;
  }

  return a;
}

#include<iostream>
int main(){
  long long a;
  std::cin >> a;
  int b;
  std::cin >> b;
  std::cout << gcd(a, b) << std::endl;
}
