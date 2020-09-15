#include <queue>
#include <vector>

template <typename T>
std::vector<T> dijkstra(int src, const std::vector<std::vector<std::pair<T, int>>>& graph) {
  const T INF = std::numeric_limits<T>::max();
  std::vector<T> distance(graph.size(), INF);
  std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq;

  distance[src] = 0;
  pq.push({0, src});

  while (pq.size()) {
    auto [cost, node] = pq.top();
    pq.pop();

    if (distance[node] < cost) continue;

    for (auto& [edge_cost, next] : graph[node]) {
      if (distance[next] <= cost + edge_cost) continue;

      distance[next] = cost + edge_cost;
      pq.push({distance[next], next});
    }
  }

  return distance;
}

int main() {
  return 0;
}

