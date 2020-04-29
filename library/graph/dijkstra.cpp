#include<queue>
#include<vector>

template<typename T>
std::vector<T> dijkstra(int src, const std::vector<T>& graph){
  std::vector<T> distance(graph.size(), -1);
  std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq;

  distance[src] = 0;
  pq.push(std::make_pair(0, src));

  while(!pq.size()){
    auto [cost, node] = pq.top();
    pq.pop();

    if(distance[node] >= 0 && distance[node] < cost) continue;

    for(auto& [edge_cost, next] : graph[node]){
      if(distance[next] >= 0 && distance[node] <= cost + edge_cost) continue;

      distance[next] = cost + edge_cost;
      pq.push(std::make_pair(distance[next], next));
    }
  }

  return distance;
}

int main(){}

