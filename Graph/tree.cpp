struct Tree {
  public:
  
  Tree() {}
  Tree(const vector<vector<int>> &_adj, int _root = 0) : adj(_adj), n(sz(_adj)), seen(n), _sn(n), root(_root), dis(n) {
    sn(root);
    seen.assign(n, 0);
    dd(root);
  }
  
  vector<int> subnodes() {return _sn;} 
  vector<int> distances() {return dis;}
  
  void dfs() {
    seen.assign(n, 0);
    _dfs(root);
  }
  
  private:
  
  vector<vector<int>> adj;
  int n, root;
  vector<bool> seen;
  vector<int> _sn, dis;
  
  void sn(int cur) {
    seen[cur] = true;
    _sn[cur]++;
    for (int i : adj[cur]) {
      if (!seen[i]) {
        sn(i);
        _sn[cur] += _sn[i];
      }
    }
  }
  
  void _dfs(int cur) {
    seen[cur] = true;
    for (int i : adj[cur]) {
      if (!seen[i]) {
        _dfs(i);
        // do thing here 
      }
    }
  }
  
  void dd(int cur) {
    seen[cur] = true;
    for (int i : adj[cur]) {
      if (!seen[i]) {
        dis[i] = dis[cur] + 1;
        dd(i);
      }
    }
  }
};
