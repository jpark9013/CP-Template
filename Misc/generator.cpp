struct Generator {
	mt19937_64 RNG{random_device{}()};
	long long rnd (long long l, long long r) { return (long long)(RNG() % (r - l + 1)) + l; }
	long long rnd (long long r)	   { return RNG() % r; }
	long long rnd ()		   { return RNG(); }
	long double rndf()		   { return (long double)RNG() / (long double)ULLONG_MAX; }
	long double rndf(long double l, long double r) { return rndf() * (r - l) + l; }
	
	pair<int, int> dif_pair(int l, int r) {
		while (true) {
			int u = rnd(l, r), v = rnd(l, r);
			if (u != v)
				return {u, v};
		}
	}
	
	pair<int, int> lr(int l, int r, bool allow_same) {
		while (true) {
			int u = rnd(l, r), v = rnd(l, r);
			if (u == v && !allow_same) continue;
			if (u > v) swap(u, v);
			return {u, v};
		}
	}
	
	vector<pair<int, int>> tree(int n) {
		struct DSU {
			vector<int> rk;
			vector<int> p;
			int n;
	
			DSU(int n = 1) : n(n) {
				reset(n);
			}
	
			void reset(int n) {
				p.resize(n);
				iota(p.begin(), p.end(), 0);
				rk.assign(n, 1);
			}
	
			int par(int v) {
				return v == p[v] ? v : p[v] = par(p[v]);
			}
	
			bool un(int u, int v) {
				u = par(u);
				v = par(v);
				if (u == v) return false;
				if (rk[u] > rk[v]) swap(u, v);
				p[u] = v;
				rk[v] += rk[u];
				return true;
			}
		};
	
		DSU d(n);
		vector<pair<int, int>> res;
		int comps = n;
		while (comps > 1) {
			auto [u, v] = dif_pair(0, n - 1);
			if (d.un(u, v)) {
				res.emplace_back(u, v);
				--comps;
			}
		}
		return res;
	}
	
	vector<pair<int, int>> graph(int n, int m, bool connected) {
		set<pair<int, int>> has;
		vector<pair<int, int>> res;
		if (connected) {
			res = tree(n);
			for (auto& [u, v] : res)
				if (u > v)
					swap(u, v);
			has.insert(res.begin(), res.end());
		}
		while (res.size() < m) {
			auto p = lr(0, n - 1, false);
			if (has.count(p)) continue;
			has.insert(p);
			res.push_back(p);
		}
		shuffle(res.begin(), res.end(), RNG);
		for (auto& [u, v] : res)
			if (rnd(2))
				swap(u, v);
		return res;
	}
	
	void setio(const string &filename = "input.txt") {
		setin(filename);
		setout(filename);
	}
	
	void print(const vector<pair<int, int>> &v, const string &filename = "input.txt") {
		setio(filename);
		cout << sz(v) << endl;
		for (auto &pair : v) {
			cout << pair.first + 1 << ' ' << pair.second + 1 << endl;
		}
	}
	
	void print_tree(int n) {
		print(tree(n));
	}
	
	void print_graph(int n, int m, bool connected) {
		print(graph(n, m, connected));
	}
	
	template<typename T = int>
	vector<T> vec(int n, T l, T r) {
		vector<T> res(n);
		for (int i = 0; i < n; ++i)
			res[i] = rnd(l, r);
		return res;
	}
	
	template<typename T = int>
	void print_vec(int n, T l, T r) {
		for (int i : vec(n, l, r)) {
			cout << i << ' ';
		}
		cout << endl;
	}
	
	// a to print to input.txt
	// b will print after cin from input.txt 
	template<typename A, typename B> 
	void run(const A &a, const B &b, const string &filename = "input.txt") {
		setio(filename);
		a();
		b();
		exit(0);
	}
} gen;
