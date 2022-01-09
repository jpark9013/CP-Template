struct Cycle {
	
	private:
	
	vector<vector<int>> adj;
	int n;
	vector<bool> seen;
	vector<int> bef, cycle;
	bool fin = false;
	
	void dfs(int cur, int p) {
		if (fin) return;
		if (seen[cur]) return;
		seen[cur] = true;
		for (int i : adj[cur]) {
			if (fin) return;
			if (i == p) continue;
			bef[i] = cur;
			if (seen[i]) {
				form_cycle(i);
				fin = true;
				return;
			} else {
				dfs(i, cur);
			}
		}
	}
	
	void form_cycle(int x) {
		int cur = bef[x];
		while (cur != x) {
			cycle.pb(cur);
			cur = bef[cur];
		}
		cycle.pb(x);
	}
	
	public:
	
	Cycle() {}
	Cycle(const vector<vector<int>> &_adj) : adj(_adj), n(sz(_adj)) {
		seen = vector<bool>(n);
		bef = vector<int>(n, -1);
		dfs(0, -1);
	}
	
	vector<int> get() {
		return cycle;
	}
};
