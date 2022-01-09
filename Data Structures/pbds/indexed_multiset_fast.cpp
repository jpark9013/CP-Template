#include <ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds;
template<class T> struct omultiset {
	
	private:
	
	typedef tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update> tree_t;
	tree_t s;
	int cur = 0;  // current time 
	
	void dec(const T &x) {
		auto it = s.lower_bound(make_pair(x, 0));
		if (it->first == x) s.erase(it);
	}
	
	void check(int ind) {
		if (ind < 0 || ind >= int(s.size())) {
			cerr << "Invalid index in omultiset: " << ind << '\n';
			assert(false);
		}
	}
	
	static constexpr int _inf = 1e18;
	
	public:
	
	bool empty() {return s.empty();}
	int size() {return s.size();}
	
	void clear() {
		s.clear();
		cur = 0;
	}
	
	void insert(const T &x) {
		s.insert(make_pair(x, cur++));
	} 
	void emplace(const T &x) {insert(x);}
	
	int index(const T &x) {return s.order_of_key(x);}
	
	void erase(const T &x) {
		dec(x);
	}
	void erase_at(int ind) {
		check(ind);
		dec(s.find_by_order(ind)->first);
	}
	void erase_range(int a, int b) {
		check(a); check(b); assert(b >= a);
		while (b-- >= a) dec(s.find_by_order(a)->first);
	}
	
	friend bool operator == (const omultiset &a, const omultiset &b) {return a.s == b.s;}
	friend bool operator != (const omultiset &a, const omultiset &b) {return a.s != b.s;}
	
	int count(const T &x) {return leq(x) - lt(x);}
	
	// number less than, leq, geq, gt etc
	int lt(const T &x) {return s.order_of_key(make_pair(x, 0));}
	int leq(const T &x) {return s.order_of_key(make_pair(x, _inf));}
	int geq(const T &x) {return size() - lt(x);}
	int gt(const T &x) {return size() - leq(x);}
	
	T operator [] (int ind) {
		check(ind);
		return s.find_by_order(ind)->first;
	}
	
	template<typename U> friend U& operator << (U &out, omultiset &ms) {
		out << '[';
		int c = 0;
		for (const auto &x : ms.s) {
			if (c) out << ", ";
			out << x.first;
			c++;
		}
		return out << ']';
	}
};
