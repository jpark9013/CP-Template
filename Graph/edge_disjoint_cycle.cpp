// edge disjoint cycle
class EDCycle {
	
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
	int *used;
	pair<int, int> *parent;
	GraphIterator<pair<int, int>> g;
	vector<int> ans;
	bool found = false;
	
	void dfs(int v) {
		if (found) return;
		used[v] = 1;
		for (auto [to, id] : g[v]) {
			if (found) return;
			if (!used[to]) {
				parent[to] = {v, id};
				dfs(to);
			} else if (used[to] == 1) {
				found = true;
				ans.push_back(id);
				int cur = v;
				while (cur != to) {
					ans.push_back(parent[cur].second);
					cur = parent[cur].first;
				}
				reverse(ans.begin(), ans.end());
				return;
			}
		}
		used[v] = 2;
	}
	
	void build(const vector<pair<int, int>> &edges) {
		parent = new pair<int, int>[n];
		used = new int[n];
		
		for (int i = 0; i < sz(edges); i++) {
			g.add_edge(edges[i].first, {edges[i].second, i});
		}

		memset(used, 0, sizeof(used[0]) * n);
		
		g.prepare();
		for (int i = 0; i < n; i++) {
			if (!used[i]) {
				dfs(i);
			}
		}
	}
	
	public:
	
	~EDCycle() {
		delete[] parent;
		delete[] used;
	}
	
	EDCycle() {}
	
	EDCycle(const vector<pair<int, int>> &edges, int _n) : n(_n) {
		build(edges);
	}
	
	// returns indexes of edges input
	vector<int> get() {return ans;}
	
};
