#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class T> struct oset {
	
	private:
	
	typedef tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> tree_t;
	tree_t s;
	int cur = 0;  // current time 
	
	void dec(const T &x) {if (count(x)) s.erase(x);}
	
	void check(int ind) {
		if (ind < 0 || ind >= int(s.size())) {
			cerr << "Invalid index in oset: " << ind << '\n';
			assert(false);
		}
	}
	
	public:
	
	auto begin() {return s.begin();}
	auto cbegin() {return s.cbegin();}
	auto end() {return s.end();}
	auto cend() {return s.cend();}
	auto rbegin() {return s.rbegin();}
	auto crbegin() {return s.crbegin();}
	auto rend() {return s.rend();}
	auto crend() {return s.crend();}
	
	bool empty() {return s.empty();}
	int size() {return s.size();}
	
	void clear() {
		s.clear();
		cur = 0;
	}
	
	void insert(const T &x) {s.insert(x);} 
	void emplace(const T &x) {insert(x);}
		
	int index(const T &x) {return s.order_of_key(x);}
	int count(const T &x) {return *s.find_by_order(index(x)) == x;}
	bool contains(const T &x) {return count();}
	
	void erase(const T &x) {dec(x);}
	void erase_at(int ind) {check(ind); dec(*s.find_by_order(ind));}
	void erase_range(int a, int b) {
		check(a); check(b); assert(b >= a);
		while (b-- >= a) dec(*s.find_by_order(a));
	}
	
	friend bool operator == (const oset &a, const oset &b) {return a.s == b.s;}
	friend bool operator != (const oset &a, const oset &b) {return a.s != b.s;}
	
	// number less than, leq, geq, gt etc
	int lt(const T &x) {return s.order_of_key(x);}
	int leq(const T &x) {return s.order_of_key(x) + count(x);}
	int geq(const T &x) {return size() - lt();}
	int gt(const T &x) {return size() - leq(x);}
	
	T operator [] (int ind) {
		check(ind);
		return *s.find_by_order(ind);
	}
	
	template<typename U> friend U& operator << (U &out, oset &ms) {
		out << '[';
		int c = 0;
		for (const auto &x : ms.s) {
			if (c) out << ", ";
			out << x;
			c++;
		}
		return out << ']';
	}
};
//template<class K, class V> using umap = gp_hash_table<K, V, custom_hash>;
