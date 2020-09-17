#include <limits>
#include <queue>
#include <vector>

template <typename T>
struct Edge {
  T capacity;
  int from;
  int to;
};

template <typename T>
T dinic(int src, int dst, std::vector<std::vector<Edge<T>>> graph) {
  std::vector<int> dist, idx;

  auto bfs = [&]() {
    dist.assign(graph.size(), -1);
    std::queue<int> q;
    dist[src] = 0; q.push(src);

    while (q.size()) {
      int node = q.front();
      q.pop();

      for (Edge<T>& e : graph[node]) {
        if (e.capacity <= 0 || dist[e.to] >= 0) continue;

        dist[e.to] = dist[node] + 1; q.push(e.to);
      }
    }

    return dist[dst] >= 0;
  };

  auto dfs = [&](auto this_function, int node, T current_flow) {
    if(node == dst) return current_flow;

    for (int &next = idx[node]; next < (int)graph.size(); ++next) {
      Edge<T>& e = graph[node][next];
      if (e.capacity <= 0 || dist[next] <= dist[node]) continue;

      T ret = this_function(this_function, e.to, std::min(current_flow, e.capacity));

      if (ret) {
        e.capacity -= ret;
        graph[e.to][e.from].capacity += ret;
        return ret;
      }
    }

    return T(0);
  };

  T flow(0);

  while (idx.assign(graph.size(), 0), bfs()) {
    for (T f; f = dfs(dfs, src, std::numeric_limits<T>::max());) {
      flow += f;
    }
  }

  return flow;
}

int main() {
  int n = 100;
  std::vector<std::vector<Edge<int>>> graph(n, std::vector<Edge<int>>(n));
  dinic<int>(0, 0, graph);

  return 0;
}
