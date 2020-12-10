template <typename T, typename U>
constexpr T gcd(T a, U b) {
  if (a < b) {
    a ^= b; b ^= a; a ^= b;
  }
  
  T r;
  while (b) {
    a %= b;
    b ^= a; a ^= b; b ^= a;
  }

  return a;
}

#include <iostream>
int main() {
  std::cout << gcd(12, 18) << std::endl;
  std::cout << gcd(2, 0) << std::endl;
  long long a;
  std::cin >> a;
  int b;
  std::cin >> b;
  std::cout << gcd(a, b) << std::endl;
}
