#include <algorithm>
#include <map>
#include <vector>

template <typename T>
class Compressor {
private:
  std::map<T, int> zip;
  std::vector<T> unzip;

public:
  Compressor(std::vector<T> v) {
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());

    unzip = std::vector<int>(v.size());
    for (int i = 0; i < (int)v.size(); i++) {
      zip[v[i]] = i;
      unzip[i] = v[i];
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

  return 0;
}
