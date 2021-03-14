constexpr int MOD = 998244343;

template <typename T, typename U, typename V>
constexpr T power(T b, U e, V mod) {
  T ret = 1;
  while (e) {
    if (e & 1) {
      ret *= b;
      ret %= mod;
    }

    b *= b;
    b %= mod;
    e >>= 1;
  }

  return ret;
}

template <typename T, typename U>
constexpr T power(T b, U e) {
  return power(b, e, MOD);
}


#include <iostream>
int main() {
  std::cout << power(3, 4) << ' ' << power(3, 5) << std::endl;
}
