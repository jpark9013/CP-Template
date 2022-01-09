// ordered 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class T> struct omultiset {
  tree<pair<int, T>, null_type, less<pair<int, T>>, rb_tree_tag, tree_order_statistics_node_update> s;
  const T& operator [] (int ind) {check(ind); return (*s.find_by_order(ind)).second;}
  umap<T, set<int>> m;  // replace with map if hashing doesn't work
  int cur = 0;
  void insert(const T &v) {s.insert(mp(++cur, v)); m[v].emplace(cur);}
  void emplace(T v) {insert(v);}
  void erase(const T &v) {  // erases first occurence
  	if (m[v].empty()) return; 
  	int a = m[v].begin();
  	m[v].erase(m[v].begin());
  	s.erase(mp(a, v));
  }
  void erase_at(int ind) {
  	check(ind);
  	auto it = s.find_by_order(ind);
  	auto &p = *it;
  	m[p.second].erase(p.first);
  	s.erase(it);
  }
  int index(const T &v) {
  	assert(!m[v].empty());
  	return s.order_of_key(mp(m[v].front(), v));
  }
  int size() {return s.size();}
  void clear() {s.clear(); m.clear(); cur = 0;}
  friend T& operator<<(T &out, const omultiset<T> &s) {
		out << "["; int c = 0;
		for (const auto &i : s.s) {if (c) out << ", "; out << i.second; c++;}
		return out << "]";
  }
	int count(const T &v) {return sz(m[v]);}
  // if you need them just iterate over the indexes
  private:
	  auto begin() {return s.begin();}
	  auto end() {return s.end();}
	  void check(int x) {assert(x >= 0 && x < size());}
};
//template<class K, class V> using umap = gp_hash_table<K, V, custom_hash>;
