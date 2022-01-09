struct LCA {
	
	private:
	
	vector<int> lca_ind;
	vector<vector<int>> lca_sparse;
	vector<int> lca_p2;
	vector<int> depth;
	
	void build_lca_sparse(const vector<vector<int>>& g, int root = 0) {
		int n = g.size();
		vector<int> euler;
		lca_ind.resize(n);
		depth.assign(n, -1);
		function<void(int, int)> dfs = [&](int v, int d) {
			lca_ind[v] = euler.size();
			euler.pb(v);
			depth[v] = d;
			for (auto k : g[v]) {
				if (depth[k] == -1) {
					dfs(k, d + 1);
					euler.pb(v);
				}
			}
		};
		dfs(root, 0);
		int m = euler.size();
		int log = 1;
		while ((1 << log) < m)
			++log;
		lca_sparse.resize(log);
		lca_sparse[0].resize(m);
		lca_p2.resize(m + 1);
		int pp2 = 0;
		for (int i = 1; i < lca_p2.size(); ++i) {
			if (1 << (pp2 + 1) <= i)
				++pp2;
			lca_p2[i] = pp2;
		}
		lca_p2[0] = 0;
		for (int i = 0; i < m; ++i)
			lca_sparse[0][i] = euler[i];
		for (int i = 1; i < log; ++i) {
			lca_sparse[i].assign(m, 0);
			for (int j = 0; j < m - (1 << (i - 1)); ++j) {
				int v1 = lca_sparse[i - 1][j], v2 = lca_sparse[i - 1][j + (1 << (i - 1))];
				if (depth[v1] < depth[v2])
					lca_sparse[i][j] = v1;
				else
					lca_sparse[i][j] = v2;
			}
		}
	}
	
	void check(int x) {assert(x >= 0 && x < sz(depth));}
	void check(int x, int y) {check(x); check(y);}
	void check(int x, int y, int z) {check(x); check(y); check(z);}
	
	public:
	
	LCA() {}
	LCA(const vector<vector<int>> &adj, int root = 0) {
		build_lca_sparse(adj, root);
	}
	
	int lca(int u, int v) {
		check(u, v);
		if (u == v)
			return u;
		u = lca_ind[u];
		v = lca_ind[v];
		if (u > v)
			swap(u, v);
		int v1 = lca_sparse[lca_p2[v - u + 1]][u], v2 = lca_sparse[lca_p2[v - u + 1]][v - (1 << lca_p2[v - u + 1]) + 1];
		if (depth[v1] < depth[v2])
			return v1;
		else
			return v2;
	}
	
	int dis(int u, int v) {
		check(u, v);
		return depth[u] + depth[v] - 2 * depth[lca(u, v)];
	}
	
	bool is_ancestor(int u, int v) {
		check(u, v);
		if (depth[u] > depth[v]) return false;
		int d = depth[v] - depth[u];
		return dis(u, v) == d;
	}
	
	// checks if c is in the path of a and b
	// (order of a and b doesn't matter)
	bool in_path(int a, int b, int c) {
		check(a, b, c);
		int top = lca(a, b);
		return (is_ancestor(c, a) || is_ancestor(c, b)) && is_ancestor(top, c);
	}
};
