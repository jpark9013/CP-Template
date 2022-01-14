template<typename T>
class Prefix {
  
  private:
  
  using ftype = function<T(T, T)>;
  ftype func, inverse;
  vector<T> pre;
  T val;
  int n;
  
  void build(const vector<T> &vec) {
    pre.resize(n);
    pre[0] = vec[0];
    for (int i = 1; i < n; i++) {
      pre[i] = func(pre[i - 1], vec[i]);
    }
  }
  
  void valid(int x) {assert(x >= 0 && x < n);}
  void valid(int a, int b) {valid(a); valid(b);}
  
  public:
  
  Prefix() {}
  Prefix(const vector<T> &vec) : n(sz(vec)) {
    func = [](T a, T b){return a + b;};
    inverse = [](T a, T b){return a - b;};
    val = 0;
    build(vec);
  }
  
  // ex: for multiplication, val is 1
  // for addition, val is 0
  Prefix(const vector<T> &vec, const ftype &_func, const ftype &_inverse, 
  T _val) : n(sz(vec)), func(_func), inverse(_inverse), val(_val) {
    build(vec);
  }
  
  T get(int a, int b) {
    valid(a, b);
    assert(b >= a);
    return inverse(pre[b], a == 0 ? val : pre[a - 1]);
  }
  
  T& operator [] (int ind) {
    valid(ind);
    return pre[ind];
  }
  
  vector<T> data() {return pre;}
};
