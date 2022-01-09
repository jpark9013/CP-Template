struct BF {
	
	int n, root;
	const int _INF = 1e18;
	vector<int> dis, bef;
	
	void valid(int x) {assert(x >= 0 && x < n);}
	
	public:
	
	BF() {}
	template<typename Edge> BF(const vector<Edge> &edges, int _n, int _root) : n(_n), root(_root) {
		dis = vector<int>(n, _INF);
		bef = vector<int>(n, -1);
		dis[root] = 0;
		for (int i = 0; i < n; i++) {
			for (auto &edge : edges) {
				if (cmin(dis[edge.second], dis[edge.first] + edge.third)) {
					bef[edge.second] = edge.first;
				}
			}
		}
	}
	
	vector<int> path(int x) {
		valid(x);
		int cur = x;
		vector<int> ret;
		while (cur != root) {
			ret.pb(cur);
			cur = bef[cur];
			if (cur == -1) {
				return {-1};
			}
		}
		return ret;
	}
	
	int get(int x) {
		valid(x);
		return dis[x];
	}
};
