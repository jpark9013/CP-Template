template<typename T> struct TreeQuery {
  
  using ftype = function<T(T, T)>;
  
  private:
  
  struct _SegTree {
    vector<T> vec;
    int n;
    ftype f;
    _SegTree(const vector<T> &v, const ftype &func) : n(sz(v)), f(func) {
        assert(n >= 1);
        vec = vector<int>(n*2);
        for (int i = n; i < n * 2; i++) vec[i] = v[i-n];
        for (int i = n-1; i >= 0; i--) {
          vec[i] = f(vec[2*i], vec[2*i+1]);
        }
      }
    _SegTree() : n(0) {}
    void valid(int x) {assert(x >= 0 && x < n);}
    T get(int a, int b) {
      valid(a); valid(b); assert(b >= a);
      a += n; b += n;
      int s = vec[a];
      a++;
      while (a <= b) {
        if (a % 2 == 1) {
          s = f(s, vec[a]);
          a++;
        }
        if (b % 2 == 0) {
          s = f(s, vec[b]);
          b--;
        }
        a /= 2; b /= 2;
      }
      return s;
    }
    void add(int x, const T &c) {
      valid(x);
      x += n;
      vec[x] += c;
      for (x /= 2; x >= 1; x /= 2) {
        vec[x] = f(vec[2*x], vec[2*x+1]);
      }
    }
    void update(int x, const T &c) {add(x, c-vec[x+n]);}
    const T& operator[](int x) {valid(x); return vec[x+n];}
  };
  
  int n;
  vector<vector<int>> adj;
  vector<T> arr, indexes, sn;
  vector<bool> seen;
  _SegTree st;
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
    st = _SegTree(v, f);
  }
  
  TreeQuery() {}
  
  T get(int node) {
    check(node);
    return st.get(indexes[node], indexes[node] + sn[node] - 1);
  }
  
  void add(int node, T val) {
    check(node);
    st.add(indexes[node], val);
  }
  
  void update(int node, T val) {
    check(node);
    st.update(indexes[node], val);
  }
};
