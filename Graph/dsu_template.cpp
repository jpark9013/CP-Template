template<typename T> struct DSU {
 	// replace with umap if it can be hashed
	map<T, int> ind;
	vector<int> rep, sz;
	void push_back(const T &x) {
		ind[x] = rep.size();
		rep.pb(rep.size());
		sz.pb(1);
	}
	int find(const T &x) {
		int a = ind[x];
		while (a != rep[a]) a = rep[a];
		return a;
	}
	bool same(const T &a, const T &b) {return find(a) == find(b);}
	bool join(const T &x, const T &y) {
		int a = find(x);
		int b = find(y);
		if (a == b) return false;
		if (sz[a] < sz[b]) swap(a, b);
		rep[b] = a;
		sz[a] += sz[b];
		return true;
	}
	int size(const T &x) {return sz[find(x)];}
	int size() {return rep.size();}
};
