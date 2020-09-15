#include <algorithm>
#include <vector>

#include "point.cpp"

template <typename T>
std::vector<Point<T>> convex_hull(std::vector<Point<T>> points) {
  std::sort(points.begin(), points.end());
  points.erase(std::unique(points.begin(), points.end()), points.end());

  int n = points.size(), k = 0;
  if (n < 3) {
    return points;
  } else {
    std::vector<Point<T>> ret(n << 1);
    for (int i = 0; i < n; ret[k++] = points[i++]) {
      while (k >= 2 && cross(ret[k - 1] - ret[k - 2], points[i] - ret[k - 1]) <= 0) --k;
    }
    for (int i = n - 2, t = k + 1; i >= 0; ret[k++] = points[i--]) {
      while (k >= t && cross(ret[k - 1] - ret[k - 2], points[i] - ret[k - 1]) <= 0) --k;
    }
    ret.resize(k - 1);
    return ret;
  }
}


#include <iostream>

int main() {
  std::vector<Point<int>> points(5);
  points[0] = Point<int>(0, 0), points[1] = Point<int>(1, 1), points[2] = Point<int>(1, 0), points[3] = Point<int>(-2, 2), points[4] = Point<int>(0, 1);

  std::vector<Point<int>> ch = convex_hull(points);

  for (auto& p : ch) {
    std::cout << '(' << p.x << ", " << p.y << ')' << std::endl;
  }

  return 0;
}
