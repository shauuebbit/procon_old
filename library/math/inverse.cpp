constexpr int MOD = 1000000007;

template <typename T, typename U>
constexpr T inverse(T a, U m) {
  if (a >= m) a %= m;
  T b = (T)m, u = 0, v = 1;

  while (a) {
    T t = b / a;
    b -= t * a;
    a += b; b = a - b; a -= b;
    u -= t * v;
    u += v; v = u - v; u -= v;
  }
  
  u %= m;
  if (u < 0) u += m;

  return u;
}

template <typename T>
constexpr T inverse(T a) {
  return inverse(a, MOD);
}

#include <iostream>
int main() {
  constexpr long long a = inverse(5ll);
  std::cout << 5 * a % MOD << std::endl;
}

