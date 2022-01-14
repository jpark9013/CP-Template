#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename K, typename V> struct omap {
  
  private:
  
  typedef tree<K, null_type, less<K>, rb_tree_tag, tree_order_statistics_node_update> tree_t;
  tree_t s;
  
  using cK = const K&;
  using cV = const V&;
  
  map<K, V> m;
  
  void check(int x) {
    assert(x >= 0 && x < size());
  }
  
  public:
  
  template<typename U> friend U& operator << (U& out, const omap &x) {
    return out << x.m;
  }
  
  // member functions
  omap() {}
  
  // element access
  V& operator [] (cK x) {
    if (count(x)) return m[x];
    s.insert(x);
    return m[x];
  } 
  
  // capacity
  #define super(x) auto x() {return m.x();}
  #define csuper(x) auto x() const {return m.x();}
  #define arg(x) auto x(cK y) {return m.x(y);}
  
  super(begin)
  csuper(cbegin)
  super(end)
  csuper(cend)
  super(rbegin)
  csuper(crbegin)
  super(rend)
  csuper(crend)
  
  // capacity
  super(empty)
  super(size)
  
  // modifiers
  void clear() {
    m.clear();
    s.clear();
  }
  void erase(cK x) {
    m.erase(x);
    s.erase(x);
  }
  
  // lookup
  arg(count)
  arg(find)
  arg(equal_range)
  arg(lower_bound)
  arg(upper_bound)
  
  #undef super
  #undef csuper
  #undef arg  
  
  pair<cK, V&> get(int x) {
    check(x);
    K a = *s.find_by_order(x);
    return {a, m[a]};
  }
  int index(cK x) {return s.order_by_key(x);}
  
};
