// https://github.com/emorgan00/notebook/blob/master/ds/sparse_table.cpp
template<typename it, typename bin_op>
struct RMQ {

  using T = typename iterator_traits<it>::value_type;
  vector<vector<T>> t; bin_op f;

  RMQ(it first, it last, const bin_op &op) : f(op) {
    int n = distance(first, last);
    t.assign(32-__builtin_clz(n), vector<T>(n));
    t[0].assign(first, last);
    for (int i = 1; i < t.size(); i++) {
      for (int j = 0; j < n - (1 << i) + 1; j++) {
        t[i][j] = f(t[i-1][j], t[i-1][j + (1 << (i-1))]);
      }
    }
  }

  void check(int a) {assert(a >= 0 && a <= sz(t[0]));}

  // returns f(a[l..r]) in O(1) time
  T get(int l, int r) {
    check(l); check(r); assert(r >= l);
    int h = floor(log2(r-l+1));
    return f(t[h][l], t[h][r-(1<<h)+1]);
  }
};
