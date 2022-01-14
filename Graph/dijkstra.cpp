struct Dijkstra {
  
  private:
  
  int n, root;
  vector<vector<pii>> adj;
  vector<int> bef, cost;
  
  vector<int> dijkstra() {
    vector<bool> seen(n);
    vector<int> dis(n, INF);
    bef = vector<int>(n, -1);
    dis[root] = 0;
    minpq<pii> heap;
    heap.push({0, root});
    while (!heap.empty()) {
      int a = heap.top().second;
      heap.pop();
      if (seen[a]) continue;
      seen[a] = true;
      for (auto &pair : adj[a]) {
        auto [b, w] = pair;
        if (dis[a] + w < dis[b]) {
          dis[b] = dis[a] + w;
          bef[b] = a;
          heap.push({dis[b], b});
        }
      }
    }
    return dis;
  }
  
  void valid(int x) {assert(x >= 0 && x < n);}
  
  public:
  
  const int INF = 1e18;
  
  Dijkstra() {}
  Dijkstra(const vector<vector<pii>> &_adj, int _root) : adj(_adj), n(sz(_adj)) {
    root = _root;
    cost = dijkstra();
  }
  template<typename Edge> Dijkstra(const vector<Edge> &vec, int _n, bool directed, int _root) {
    n = _n;
    adj = vector<vector<pii>>(n);
    for (const Edge &edge : vec) {
      adj[edge.first].pb({edge.second, edge.third});
      if (!directed) adj[edge.second].pb({edge.first, edge.third});
    }
    root = _root;
    cost = dijkstra();
  }
  
  // constructs a path from root -> to, including both nodes
  vector<int> path(int to) {
    valid(to);
    int cur = to;
    vector<int> ret = {cur};
    while (cur != root) {
      cur = bef[cur];
      if (cur == -1) return {-1};
      ret.pb(cur);
    }
    reverse(all(ret));
    return ret;
  }
  
  int get(int to) {
    valid(to);
    return cost[to];
  }
  
  vector<int> get_all() {return cost;}
};
