template<typename T> struct SegTree {
	using ftype = function<T(T, T)>;
	vector<T> vec;
	int n;
	ftype f;
	SegTree(const vector<T> &v, const ftype &func) : n(sz(v)), f(func) {
		assert(n >= 1);
		vec = vector<T>(n*2);
		for (int i = n; i < n * 2; i++) vec[i] = v[i-n];
		for (int i = n-1; i >= 0; i--) {
			vec[i] = f(vec[2*i], vec[2*i+1]);
		}
	}
	SegTree() : n(0) {}
	void valid(int x) {assert(x >= 0 && x < n);}
	T get(int a, int b) {
		valid(a); valid(b); assert(b >= a);
		a += n; b += n;
		int s = vec[a];
		a++;
		while (a <= b) {
			if (a % 2 == 1) {
				s = f(s, vec[a]);
				a++;
			}
			if (b % 2 == 0) {
				s = f(s, vec[b]);
				b--;
			}
			a /= 2; b /= 2;
		}
		return s;
	}
	void add(int x, const T &c) {
		valid(x);
		x += n;
		vec[x] += c;
		for (x /= 2; x >= 1; x /= 2) {
			vec[x] = f(vec[2*x], vec[2*x+1]);
		}
	}
	void update(int x, const T &c) {add(x, c-vec[x+n]);}
	const T& operator[](int x) {valid(x); return vec[x+n];}
};
