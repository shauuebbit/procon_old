#include <iostream>

template <long long mod>
class ModInt {
private:
  long long number;

public:
  constexpr ModInt(const ModInt& x) : number(x.number) {}

  constexpr ModInt(const long long number = 0) : number((mod + number) % mod) {}

  constexpr long long get() const { return number; }

  constexpr ModInt& operator=(const ModInt& rhs) & {
    number = rhs.number;
    return *this;
  }

  constexpr ModInt operator+() const { return ModInt(*this); }

  constexpr ModInt operator-() const { return ModInt(mod - number); }

  constexpr ModInt& operator+=(const ModInt& rhs) {
    number += rhs.number;
    if (number >= mod) number -= mod;
    return *this;
  }

  constexpr ModInt& operator-=(const ModInt& rhs) {
    number -= rhs.number;
    if (number < 0) number += mod;
    return *this;
  }

  constexpr ModInt& operator*=(const ModInt& rhs) {
    number *= rhs.number;
    if (number >= mod) number %= mod;
    return *this;
  }

  constexpr ModInt& operator/=(const ModInt& rhs) {
    (*this) *= rhs.inverse();
    return *this;
  }

  constexpr ModInt inverse() const {
    long long a = number, m = mod, u = 1, v = 0;

    while (m) {
      long long t = a / m;
      a -= t * m;
      u -= t * v;

      a ^= m; m ^= a; a ^= m;
      u ^= v; v ^= u; u ^= v;
    }

    return ModInt(u);
  }

  constexpr ModInt& operator++() { return *this += 1; }

  constexpr ModInt& operator--() { return *this -= 1; }

  constexpr ModInt operator++(int) {
    ModInt ret = *this;
    ++(*this);
    return ret;
  }

  constexpr ModInt operator--(int) {
    ModInt ret = *this;
    --(*this);
    return ret;
  }

  constexpr ModInt operator+(const ModInt& rhs) const { return ModInt(*this) += rhs; }

  constexpr ModInt operator-(const ModInt& rhs) const { return ModInt(*this) -= rhs; }

  constexpr ModInt operator*(const ModInt& rhs) const { return ModInt(*this) *= rhs; }

  constexpr ModInt operator/(const ModInt& rhs) const { return ModInt(*this) /= rhs; }

  constexpr ModInt operator^(const long long& rhs) const {
    long long b = number, e = rhs, y = 1, m = mod;
    bool inv = e < 0;
    if (inv) e = -e;

    while (e) {
      if(e & 1) (y *= b) %= m;

      (b *= b) %= m;
      e >>= 1;
    }

    return (inv ? ModInt(y).inverse() : ModInt(y));
  }
};

template <long long mod>
std::istream& operator>>(std::istream& is, ModInt<mod>& x) {
  long long in;
  is >> in;
  x = in;
  return is;
}

template <long long mod>
std::ostream& operator<<(std::ostream& os, const ModInt<mod>& x) {
  os << x.get();
  return os;
}


using namespace std;

int main() {
  ModInt<1000000007> a(6);
  ModInt<1000000007> b;
  cin >> b;
  cout << "a + 5 = " << a + 5 << endl;
  cout << "a = " << a << ", -a = " << -a << endl;
  cout << "b = " << b << ", b^(-1) = " << b.inverse() << endl;
  cout << "a + b = " << (a + b) << endl;
  cout << "a - b = " << (a - b) << endl;
  cout << "a * b = " << (a * b) << endl;
  cout << "a / b = " << (a / b) << endl;
  cout << "a ^ b = " << (a ^ 3) << endl;
  cout << "a++: " << a++ << ", ++a: " << ++a << endl;
  cout << "--b: " << --b << endl;
  cout << "a = b: " << (a = b) << ", a = 876567: " << (a = 876567) << endl;
}
