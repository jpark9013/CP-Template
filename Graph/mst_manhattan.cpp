struct ManMST {
  
  private:
  
  class disjoint_set {
    
    const int n;
    vector<int> par;
  
    public:
    
    disjoint_set(int _n) : n(_n), par(n, -1) {}
  
    int find(int u) {
      return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool unite(int u, int v) {
      u = find(u), v = find(v);
      if (u == v) return false;
  
      if (par[u] > par[v]) swap(u, v);
      par[u] += par[v];
      par[v] = u;
      return true;
    }
    int size_of(int u) { return -par[find(u)]; }
    bool is_same(int u, int v) { return find(u) == find(v); }
  };
  
  int n, mst;
  vector<int> id;
  vector<tuple<int, int, int>> edges;
  vector<pii> joined;
  
  public:
  
  ManMST() {}
  ManMST(vector<pii> a) {
    n = sz(a);
    id = vector<int>(n);
    iota(all(id), 0);
    edges.reserve(n * 4);
    
    for (int t = 0; t < 4; t++) {
      sort(id.begin(), id.end(), [&](auto& lhs, auto& rhs) {
        return a[lhs].first - a[rhs].first < a[rhs].second - a[lhs].second;
      });

      map<int, int, greater<int>> sweep;
      for (const auto& i : id) {
        for (auto it = sweep.lower_bound(a[i].second); it != sweep.end(); it = sweep.erase(it)) {
          int j = it->second;
          int dx = a[i].first - a[j].first, dy = a[i].second - a[j].second;
          if (dy > dx) break;
          edges.emplace_back(dx + dy, i, j);
        }
        sweep[a[i].second] = i;
      }
  
      for (auto& [x, y] : a) {
        if (t & 1) x = -x;
        else swap(x, y);
      }
    }
    
    sort(all(edges), [&](auto &lhs, auto &rhs){
      return get<0>(lhs) < get<0>(rhs);
    });
    
    mst = 0;
    disjoint_set dsu(n);
    for (auto& [w, i, j] : edges) {
      if (dsu.unite(i, j)) {
        mst += w;
        w = -1;
      }
    }
    
    for (const auto& [w, i, j] : edges) {
      if (w == -1) {
        joined.pb({i, j});
      }
    }
  }
  
  int get_cost() {return mst;}
  vector<pii> get_edges() {return joined;}
};
