#include <algorithm>
#include <map>
#include <vector>

template <typename T>
class Compressor {
private:
  std::map<T, int> zip;
  std::vector<T> unzip;

public:
  Compressor(std::vector<T>& org) : unzip(org) {
    std::sort(unzip.begin(), unzip.end());
    unzip.erase(std::unique(unzip.begin(), unzip.end()), unzip.end());

    for (int i = 0; i < (int)unzip.size(); i++) {
      zip[unzip[i]] = i;
    }
  }

  T compress(const T& x) {
    return zip[x];
  }

  int uncompress(int ord) {
    return unzip[ord];
  }
};

#include <iostream>

using namespace std;

int main() {
  vector<int> v = {1, 5, 3, 2, 8};
  Compressor<int> cmp(v);

  cout << cmp.compress(2) << ' ' << cmp.uncompress(2) << endl;
  for (int d : v) {
    cout << d << ' ';
  }
  cout << endl;

  return 0;
}
