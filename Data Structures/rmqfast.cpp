template<typename T> struct RMQ {
  vector<T> v;
  T n, b;
  vector<T> mask, t;
  
  T op(T a, T b) {return v[a] < v[b] ? a : b;}  // can be modified 
  T msb(T x) { return __builtin_clz(1)-__builtin_clz(x); }
  T small(T r, T sz) { return r-msb(mask[r]&((1<<sz)-1)); }
  T small(T r) { return r-msb(mask[r]&((1<<b)-1)); }
  RMQ(const vector<T>& v_, const T &maximum) : v(v_), n(v.size()), mask(n), t(n), b(ceil(log2(maximum))) {
    for (T i = 0, at = 0; i < n; mask[i++] = at |= 1) {
      at = (at<<1)&((1<<b)-1);
      while (at and op(i, i-msb(at&-at)) == i) at ^= at&-at;
    }
    for (T i = 0; i < n/b; i++) t[i] = small(b*i+b-1);
    for (T j = 1; (1<<j) <= n/b; j++) for (T i = 0; i+(1<<j) <= n/b; i++)
      t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
  }
  RMQ() {}
  T get(T l, T r) {
    if (r-l+1 <= b) return v[small(r, r-l+1)];
    T ans = op(small(l+b-1), small(r));
    T x = l/b+1, y = r/b-1;
    if (x <= y) {
      T j = msb(y-x+1);
      ans = op(ans, op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
    }
    return v[ans];
  }
};
