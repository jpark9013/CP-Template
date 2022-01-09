struct Bipartite {
	int n;
	DSU dsu;
	
	Bipartite(int _n) : n(_n), dsu(DSU(n * 2)) {}
	
	void add_equal(int x, int y) {
		dsu.join(x, y);
		dsu.join(x+n, y+n);
	}
	
	void add_opp(int x, int y) {
		dsu.join(x, y+n);
		dsu.join(x+n, y);
	}
	
	bool good() {
		for (int i = 0; i < n; i++) if (dsu.same(i, i+n)) return false;
		return true;
	}
	
	// construct answer with index corresponding to node
	// trying to minimize either 0 or 1 for "which" 
	vector<int> answer(int which) {
		
		assert(good());
	
		vector<int> a(n), cnt(2 * n);
		vector<bool> b(2 * n); 
		
		for (int i = 0; i < 2*n; i++) cnt[dsu.find(i)] += (i > n) ^ which;
		
		for (int i = 0; i < n; i++) {
			int cur = dsu.find(i), complement = dsu.find(i+n);
			if (b[cur] || b[complement]) continue;
			if (cnt[cur] < cnt[complement]) b[cur] = true;
			else b[complement] = true;
		}
		
		for (int i = 0; i < n; i++) a[i] = b[dsu.find(i)];
		return a;
	}
};
