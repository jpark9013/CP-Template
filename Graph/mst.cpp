template<typename T> struct MST {
	
	private:
	
	struct DSU {
		vector<int> rep, sz;
		int cnt;
		DSU(int n) {
			rep = vector<int>(n);
			for (int i = 0; i < n; i++) rep[i] = i;
			sz = vector<int>(n, 1);
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
			return true;
		}
		int size(int x) {return sz[find(x)];}
		int size() {return cnt;}
	};

	T val = 0;
	DSU dsu;
	
	public:
	
	MST() {}
	template<typename Edge> MST(int n, const vector<Edge> &edges) {
		dsu = DSU(n);
		sort(all(edges));
		reverse(all(edges));
		for (Edge &edge : edges) {
			if (dsu.join(edge.first, edge.second)) {
				val += edge.third;
			}
		}
	}
	
	T get() {
		return val;
	}
};
