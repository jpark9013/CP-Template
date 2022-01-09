struct RDSU {
	vector<int> p;
	vector<pair<int, int>> joins;
	
	RDSU() {}
	RDSU(int n) : p(n, -1) {}

	int find(int i) const { return p[i] < 0 ? i : find(p[i]); }
	bool same(int i, int j) const { return find(i) == find(j); }
	int size(int i) const { return -p[find(i)]; }
	int time() const { return sz(joins); }

	bool join(int i, int j) {
		i = find(i), j = find(j);
		if (i == j) return false;
		if (p[i] > p[j]) swap(i, j);
		joins.emplace_back(j, p[j]);
		p[i] += p[j], p[j] = i;
		return true;
	}

	void rollback(int t) {
		while (sz(joins) > t) {
			auto [i, pi] = joins.back(); joins.pop_back();
			assert(p[p[i]] < 0);
			p[p[i]] -= pi;
			p[i] = pi;
		}
	}
};
