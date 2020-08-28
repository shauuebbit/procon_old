#include<bits/stdc++.h>

template<typename T>
struct Edge{
  T capacity;
  int from;
  int to;
};

template<typename T>
T ford_fulkerson(int src, int dst, std::vector<std::vector<Edge<T>>> graph){
  int t = 0;

  std::vector<int> used(graph.size(), -1);
  auto dfs = [&](auto this_function, int node, T current_flow){
    if(node == dst) return current_flow;

    used[node] = t;

    for(Edge<T>& e : graph[node]){
      if(used[e.to] == t || e.capacity <= 0) continue;

      T ret = this_function(this_function, e.to, std::min(current_flow, e.capacity));

      if(ret){
        e.capacity -= ret;
        graph[e.to][e.from].capacity += ret;
        return ret;
      }
    }

    return T(0);
  };

  T flow(0);

  for(T f; f = dfs(dfs, src, std::numeric_limits<T>::max()); ++t){
    flow += f;
  }

  return flow;
}

int main(){
  int n = 100;
  std::vector<std::vector<Edge<int>>> graph(n);
  ford_fulkerson<int>(0, 0, graph);

  return 0;
}
