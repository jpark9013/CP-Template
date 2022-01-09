template<typename T> 
struct DirectedMST {

	private:
	
	struct Dsu {
		vector<int> p;
	
		explicit Dsu(int n) : p(n, -1) {}
	
		int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
		bool same(int i, int j) { return find(i) == find(j); }
		int size(int i) { return -p[find(i)]; }
		bool join(int i, int j) {
			i = find(i), j = find(j);
			if (i == j) return false;
			if (p[i] > p[j]) swap(i, j);
			p[i] += p[j], p[j] = i;
			return true;
		}
	};

	struct RollbackDsu {
	
		vector<int> p;
		vector<pair<int, int>> joins;
	
		explicit RollbackDsu(int n) : p(n, -1) {}
	
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
	// end "../data-structure/dsu/rollback.hpp"
	
	template <class W>
	struct MinCostArborescenceGraph {
	 private:
		struct SkewHeapNode { int l, r, from, to; W weight, lz; };
		vector<SkewHeapNode> nodes;
		vector<int> heap;
	
		void apply(int i, W upd) { nodes[i].weight -= upd; nodes[i].lz += upd; }
		void push(int i) {
			if (nodes[i].l != -1) apply(nodes[i].l, nodes[i].lz);
			if (nodes[i].r != -1) apply(nodes[i].r, nodes[i].lz);
			nodes[i].lz = W(0);
		}
		int merge(int u, int v) {
			if (u == -1 || v == -1) return (u == -1 ? v : u);
			if (nodes[v].weight < nodes[u].weight) swap(u, v);
			push(u);
			nodes[u].r = merge(nodes[u].r, v);
			swap(nodes[u].l, nodes[u].r);
			return u;
		}
		void pop(int v) {
			push(heap[v]);
			heap[v] = merge(nodes[heap[v]].l, nodes[heap[v]].r);
		}
	
	 public:
	 	MinCostArborescenceGraph() {}
		explicit MinCostArborescenceGraph(int n, int m = 0) : heap(n, -1) { nodes.reserve(m); }
	
		void add_edge(int from, int to, W weight) {
			assert(0 <= from && from < sz(heap) && 0 <= to && to < sz(heap));
			nodes.push_back(SkewHeapNode{-1, -1, from, to, weight, W(0)});
			heap[to] = merge(heap[to], sz(nodes) - 1);
		}
	
		pair<W, vector<int>> solve(int root) {
			assert(0 <= root && root < sz(heap));
			auto ans = W(0);
			vector<int> edge(sz(heap), -1);
			vector<pair<int, int>> cycles;
			Dsu dsu_cyc(sz(heap));
			RollbackDsu dsu_contract(sz(heap));
			for (int i = 0; i < sz(heap); i++) {
				if (i == root) continue;
				int v = i;
				while (true) {
					if (heap[v] == -1) return {W(0), {}};
					edge[v] = heap[v];
					ans += nodes[edge[v]].weight;
					apply(edge[v], nodes[edge[v]].weight);
					if (dsu_cyc.join(v, dsu_contract.find(nodes[edge[v]].from)))
						break;
	
					int vnext = dsu_contract.find(nodes[edge[v]].from), t = dsu_contract.time();
					while (dsu_contract.join(v, vnext)) {
						heap[dsu_contract.find(v)] = merge(heap[v], heap[vnext]);
						v = dsu_contract.find(v);
						vnext = dsu_contract.find(nodes[edge[vnext]].from);
					}
					cycles.emplace_back(edge[v], t);
	
					while (heap[v] != -1 && dsu_contract.same(nodes[heap[v]].from, v))
						pop(v);
				}
			}
	
			for (auto it = rbegin(cycles); it != rend(cycles); ++it) {
				int vrepr = dsu_contract.find(nodes[it->first].to);
				dsu_contract.rollback(it->second);
				int vinc = dsu_contract.find(nodes[edge[vrepr]].to);
				edge[vinc] = exchange(edge[vrepr], it->first);
			}
	
			for (int i = 0; i < sz(heap); i++)
				edge[i] = (i == root ? -1 : nodes[edge[i]].from);
			return {ans, edge};
		}
	};
	
	MinCostArborescenceGraph<T> g;
	T cost;
	vector<int> parents;
	
	public:
	
	DirectedMST() {}
	template<typename Edge> DirectedMST(const vector<Edge> &_edges, int n, int root = 0) {
		g = MinCostArborescenceGraph<T>(n, sz(_edges));
		for (const Edge &edge : _edges) {
			g.add_edge(edge.first, edge.second, edge.third);
		}
		auto s = g.solve(root);
		cost = s.first;
		parents = s.second;
	}
	
	T get_cost() {return cost;}
	vector<int> get_parents() {return parents;}
};
