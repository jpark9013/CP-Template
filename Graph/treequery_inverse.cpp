template<typename T> struct TreeQuery {
  
  using ftype = function<T(T, T)>;
  
  private:
  
  int n;
  vector<vector<int>> adj;
  vector<T> arr, indexes, sn;
  vector<bool> seen;
  LSegTree<T> st;
  ftype f;
  
  void dfs(int cur) {
    if (seen[cur]) return;
    seen[cur] = true;
    arr.pb(cur);
    sn[cur]++;
    for (int i : adj[cur]) {
      if (!seen[i]) {
        dfs(i);
        sn[cur] += sn[i];
      }
    }
  }
  
  void check(int a) {assert(a >= 0 && a < n);}
  
  public:
  
  TreeQuery(const vector<vector<int>> &_adj, const vector<T> &vals, const ftype &_f, int root = 0): adj(_adj), n(sz(_adj)), f(_f) {
    assert(sz(vals) == n);
    seen.resize(n);
    indexes.resize(n);
    sn.resize(n);
    dfs(root);
    for (int i = 0; i < n; i++) indexes[arr[i]] = i;
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[indexes[i]] = vals[i];
    st = LSegTree<T>(v, 0, f);
  }
  
  TreeQuery() {}
  
  T get(int node) {
    check(node);
    return st.get(indexes[node], indexes[node]);
  }
  
  void add(int node, T val) {
    check(node);
    st.add(indexes[node], indexes[node] + sn[node] - 1, val);
  }
};
