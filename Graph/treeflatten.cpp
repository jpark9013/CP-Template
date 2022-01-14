template<typename T> struct TreeFlatten {
  private:
  
  int n;
  vector<bool> seen;
  vector<T> arr, indexes, sn;
  vector<vector<T>> adj;
  
  void dfs(T cur) {
    if (seen[cur]) return;
    seen[cur] = true;
    arr.pb(cur);
    sn[cur]++;
    for (T i : adj[cur]) {
      if (!seen[i]) {
        dfs(i);
        sn[cur] += sn[i];
      }
    }
  }
  
  public:
  
  TreeFlatten(const vector<vector<T>> &_adj, T root = 0) : adj(_adj), n(sz(adj)) {
    seen.resize(n);
    indexes.resize(n);
    sn.resize(n);
    dfs(root);
    for (int i = 0; i < n; i++) indexes[arr[i]] = i;
  }
  
  const vector<T>& get() {
    return arr;
  }
  
  pair<typename vector<T>::iterator, typename vector<T>::iterator> get(T node) {
    int ind = indexes[node];
    return {arr.begin() + ind, arr.begin() + ind + sn[node] - 1};
  }
};
