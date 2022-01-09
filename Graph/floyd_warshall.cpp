struct FW {
	
	private:
	
	int n;
	vector<vector<pii>> adj;
	vector<vector<int>> af, dis;
	const int _INF = 1e18;
	
	void fw() {
		vector<vector<int>> is_adj(n, vector<int>(n, -1));
		for (int i = 0; i < n; i++) {
			for (auto &pair : adj[i]) {
				is_adj[i][pair.first] = pair.second;
			}
		}
		dis = vector<vector<int>>(n, vector<int>(n));
		af = vector<vector<int>>(n, vector<int>(n, -1));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					dis[i][j] = 0;
					af[i][j] = i;
				}	
				else if (is_adj[i][j] != -1) {
					dis[i][j] = is_adj[i][j];
					af[i][j] = j;
				}
				else dis[i][j] = _INF;
			}
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (cmin(dis[i][j], dis[i][k] + dis[k][j])) {
						af[i][j] = af[i][k];
 					}
				}
			}
		}
	}
	
	void valid(int x) {assert(x >= 0 && x < n);}
	void valid(int a, int b) {valid(a); valid(b);}
	
	public:
	
	FW() {}
	FW(const vector<vector<pii>> &_adj) : adj(_adj), n(sz(_adj)) {fw();}
	template<typename Edge> FW(const vector<Edge> &vec, int _n, bool directed) {
		n = _n;
		adj = vector<vector<pii>>(n);
		for (const Edge &edge : vec) {
			adj[edge.first].pb({edge.second, edge.third});
			if (!directed) adj[edge.second].pb({edge.first, edge.third});
		}
		fw();
	}
	
	// constructs a path from -> to, including both nodes
	vector<int> path(int from, int to) {
		valid(from, to);
		int cur = from;
		vector<int> ret = {cur};
		while (cur != to) {
			cur = af[cur][to];
			if (cur == -1) return {-1};
			ret.pb(cur);
		}
		return ret;
	}
	
	int get(int from, int to) {
		valid(from, to);
		return dis[from][to];
	}
	
	vector<vector<int>> get_all() {return dis;}
};
