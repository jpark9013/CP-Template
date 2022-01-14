template <class T, int ...Ns> 
class Fenwick {
  T val = 0;
  void upd(T v) { val += v; }
  T query() { return val; }
};

template <class T, int N, int... Ns> 
class Fenwick<T, N, Ns...> {
  
  private:
  
  Fenwick<T,Ns...> bit[N + 1];
  template<typename... Args> T sum(int r, Args... args) {
    T res = 0; for (; r; r -= (r&-r)) res += bit[r].query(args...);
    return res;
  }
  
  public:
  
  template<typename... Args> void update(int pos, Args... args) {
    for (; pos <= N; pos += (pos&-pos)) bit[pos].upd(args...);
  }
  
  template<typename... Args> T query(int l, int r, Args... args) {
    return sum(r - 1,args...)-sum(l,args...);
  }
}; // BIT<int,10,10> gives a 2D BIT
