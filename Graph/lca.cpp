struct LCA {
  
  public:
  
  template<typename T> LCA(vector<vector<T>> &_adj, T root = 0) : adj(_adj), n(sz(_adj)), lg(ceil(log2(sz(_adj)))) {
    seen.resize(n);
    tin.resize(n);
    tout.resize(n);
    _dis.resize(n);
    dd(root);
    fill(all(seen), false);
    up = vector<vector<int>>(n, vector<int>(lg+1));
    dfs(root);
  }
  
  LCA() {}
  
  // a ancestor of b 
  bool ancestor(int a, int b) {
    check(a); check(b);
    return tin[a] <= tin[b] && tout[a] >= tout[b];
  }
  
  int lca(int a, int b) {
    check(a); check(b);
    if (ancestor(a, b)) return a;
    for (int i = lg; i >= 0; i--) if (!ancestor(up[a][i], b)) a = up[a][i];
    return up[a][0];
  }

  // returns node with distance d up from a 
  // beware, will return -1 if invalid 
  int get(int a, int d) {
    check(a);
    if (_dis[a] < d) return -1;
    for (int i = lg; i >= 0; i--) {
      int b = 1 << i;
      if (b <= d) {
        a = up[a][i];
        d -= b;
      }
    }
    return a;
  }
  
  // returns distance between nodes a and b
  int dis(int a, int b) {
    check(a); check(b);
    return _dis[a] + _dis[b] - 2 * _dis[lca(a, b)];
  }
  
  // checks if c is in the path of a and b
  // (order of a and b doesn't matter)
  bool in_path(int a, int b, int c) {
    check(a, b, c);
    int top = lca(a, b);
    return (ancestor(c, a) || ancestor(c, b)) && ancestor(top, c);
  }
  
  private:
  
  int n, t = 0, lg;
  vector<bool> seen;
  vector<int> tin, tout, _dis;
  vector<vector<int>> up, adj;
  
  void dd(int cur) {
    check(cur);
    if (seen[cur]) return;
    seen[cur] = true;
    for (int i : adj[cur]) {
      if (!seen[i]) {
        _dis[i] = _dis[cur] + 1;
        dd(i);
      }
    }
  }
  
  void dfs(int cur) {
    check(cur);
    if (seen[cur]) return;
    seen[cur] = true;
    tin[cur] = ++t;
    for (int i = 1; i <= lg; i++) up[cur][i] = up[up[cur][i-1]][i-1];
    for (int i : adj[cur]) {
      if (!seen[i]) {
        up[i][0] = cur;
        dfs(i);
      }
    }
    tout[cur] = ++t;
  }
  
  void check(int a) {assert(a >= 0 && a <= n-1);}
};
