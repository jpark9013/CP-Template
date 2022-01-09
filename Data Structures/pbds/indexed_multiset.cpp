// ordered
#include <ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds;
template<class T> struct omultiset {
	
	private:
	
	typedef tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update> tree_t;
	tree_t s;
	umap<T, int> cnt;  // O(1) .count() function
	multiset<T> ms;  // provide begin and end iterators
	int cur = 0;  // current time 
	
	void dec(const T &x) {
		cnt[x]--;
		ms.erase(ms.find(x));
		s.erase(make_pair(x, 0));
	}
	
	void check(int ind) {
		if (ind < 0 || ind >= int(ms.size())) {
			cerr << "Invalid index in omultiset: " << ind << '\n';
			assert(false);
		}
	}
	
	static constexpr int _inf = 1e18;
	
	public:
	
	auto begin() {return ms.begin();}
	auto cbegin() {return ms.cbegin();}
	auto end() {return ms.end();}
	auto cend() {return ms.cend();}
	auto rbegin() {return ms.rbegin();}
	auto crbegin() {return ms.cbegin();}
	auto rend() {return ms.rend();}
	auto crend() {return ms.crend();}
	
	bool empty() {return ms.empty();}
	int size() {return ms.size();}
	
	void clear() {
		s.clear();
		cnt.clear();
		ms.clear();
		cur = 0;
	}
	
	void insert(const T &x) {
		cnt[x]++;
		s.insert(make_pair(x, cur++));
		ms.emplace(x);
	} 
	void emplace(const T &x) {insert(x);}
	
	void erase(const T &x) {
		if (cnt[x] == 0) return;
		dec(x);
	}
	void erase_at(int ind) {
		check(ind);
		dec(s.find_by_order(ind)->first);
	}
	void erase_all(const T &x) {
		while (cnt[x]) dec(x);
	}
	void erase_range(int a, int b) {
		check(a); check(b); assert(b >= a);
		while (b-- >= a) dec(s.find_by_order(a)->first);
	}
	
	int count(const T &x) {return cnt[x];}
	bool contains(const T &x) {return cnt[x];}
	
	friend bool operator == (const omultiset &a, const omultiset &b) {return a.cnt == b.cnt;}
	friend bool operator != (const omultiset &a, const omultiset &b) {return a.cnt != b.cnt;}
	
	// number less than, leq, geq, gt etc
	int lt(const T &x) {return s.order_of_key(make_pair(x, 0));}
	int leq(const T &x) {return s.order_of_key(make_pair(x, _inf));}
	int geq(const T &x) {return size() - lt(x);}
	int gt(const T &x) {return size() - leq(x);}
	
	int index_left(const T &x) {  // find leftmost index of x, can return -1
		assert(size());
		if (x < *ms.begin()) return -1;
		return lt(x) - (cnt[x] ? 1 : 0);
	}
	int index_right(const T &x) {  // find rightmost index of x, can return -1
		assert(size());
		if (x < *ms.begin()) return -1;
		return leq(x) - (cnt[x] ? 1 : 0);
	}
	
	T operator [] (int ind) {
		check(ind);
		return s.find_by_order(ind)->first;
	}
	
	template<typename U> friend U& operator << (U &out, omultiset &ms) {
		out << '[';
		int c = 0;
		for (const T &x : ms) {
			if (c) out << ", ";
			out << x;
			c++;
		}
		return out << ']';
	}
};
