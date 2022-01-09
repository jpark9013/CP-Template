class SCC {
	
	private:
	
	template<typename Edge>
	class GraphIterator {
		
		public:
	
		class OutgoingEdges {
			
			public:
			
			OutgoingEdges(const GraphIterator *g, int l, int r): g(g), l(l), r(r) {
			}
	
			const Edge* begin() const {
				if (l == r) {
					return 0;
				}
				return &g->prepared_edges[l];
			}
	
			const Edge* end() const {
				if (l == r) {
					return 0;
				}
				return &g->prepared_edges[r];
			}
	
			private:
			
			int l, r;
			const GraphIterator *g;
		
		};
	
		void clear() {
			prepared_edges.clear();
			edges.clear();
			start.clear();
			prepared = false;
		}
	
		void add_edge(int from, const Edge &e) {
			assert(!prepared && from >= 0);
			edges.push_back({from, e});
		}
	
		void prepare() {
			assert(!prepared);
			int n = 0;
			for (const auto &e : edges) {
				n = max(n, e.first);
			}
			n += 2;
			start.resize(n);
			for (const auto &e : edges) {
				++start[e.first + 1];
			}
			for (int i = 1; i < n; ++i) {
				start[i] += start[i - 1];
			}
			prepared_edges.resize(edges.size() + 1);
			auto counter = start;
			for (const auto &e : edges) {
				prepared_edges[counter[e.first]++] = e.second;
			}
			prepared = true;
		}
	
		OutgoingEdges operator [] (int from) const {
			assert(prepared);
			if (from < 0 || from + 1 >= start.size()) {
				return {this, 0, 0};
			}
			return {this, start[from], start[from + 1]};
		}
	
		private:
		
		vector<Edge> prepared_edges;
		vector<pair<int, Edge>> edges;
		vector<int> start;
		bool prepared = false;
		
	};
	
	int n;
	int *nxt, *pr;
	bool *used;
	vector<int> comp, order;
	vector<vector<int>> ans;
	GraphIterator<int> g, rg;
	
	void dfs(int v) {
		used[v] = 1;
		for (int to : g[v]) {
			if (!used[to]) {
				dfs(to);
			}
		}
		order.push_back(v);
	}
	
	void dfs2(int v) {
		used[v] = 1;
		comp.push_back(v);
		for (int to : rg[v]) {
			if (!used[to]) {
				dfs2(to);
			}
		}
	}
	
	void build(const vector<pair<int, int>> &edges) {
		nxt = new int[n];
		pr = new int[n];
		used = new bool[n];
		
		for (auto &p : edges) {
			g.add_edge(p.first, p.second);
			rg.add_edge(p.second, p.first);
		}
		
		memset(used, 0, sizeof(used[0]) * n);
		
		g.prepare();
		rg.prepare();
		for (int i = 0; i < n; i++) {
			if (!used[i]) {
				dfs(i);
			}
		}
		
		reverse(order.begin(), order.end());
		memset(used, 0, sizeof(used[0]) * n);
		
		for (int v : order) {
			if (!used[v]) {
				comp.clear();
				dfs2(v);
				ans.push_back(comp);
			}
		}
	}
	
	public:
	
	~SCC() {
		delete[] nxt;
		delete[] pr;
		delete[] used;
	}
	
	SCC() {}
	
	SCC(const vector<pair<int, int>> &edges, int _n) : n(_n) {
		build(edges);
	}
	
	SCC(const vector<vector<int>> &adj) : n(sz(adj)) {
		vector<pair<int, int>> edges;
		for (int i = 0; i < n; i++) {
			for (int j : adj[i]) {
				edges.push_back({i, j});
			}
		}
		build(edges);
	}
	
	vector<vector<int>> get() {return ans;}
};
