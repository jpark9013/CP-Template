struct DSU {
	vector<int> rep, sz;
	vector<vector<int>> _nodes;
	int cnt;
	DSU(int n) {
		rep.resize(n);
		iota(all(rep), 0);
		sz.resize(n);
		sz.assign(n, 1);
		_nodes.resize(n);
		for (int i = 0; i < n; i++) _nodes[i] = {i};
		cnt = n;
	}
	DSU() {}
	int find(int x) {
		while (x != rep[x]) x = rep[x];
		return x;
	}
	bool same(int a, int b) {return find(a) == find(b);}
	bool join(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		if (sz[a] < sz[b]) swap(a, b);
		rep[b] = a;
		sz[a] += sz[b];
		cnt--;
		for (int i : _nodes[b]) _nodes[a].pb(i);
		return true;
	}
	int size(int x) {return sz[find(x)];}
	int size() {return cnt;}
	vector<int> nodes(int x) {return _nodes[find(x)];}
};
