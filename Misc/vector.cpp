template<typename T, int n> class Vector {
	
	private:
	
	vector<T> vec;
	T _mag = 0;
	using cls = const Vector<T, n>&;	
	using ncls = Vector<T, n>;
	using rcls = Vector<T, n>&;
	#define self (*this)
	
	template<typename F> static ncls apply(cls a, cls b, const F &f) {
		ncls c;
		for (int i = 0; i < n; i++) c[i] = f(a[i], b[i]);
		return c;
	}
	template<typename F> void apply(ncls other, const F &f) {
		for (int i = 0; i < n; i++) self[i] = f(self[i], other[i]);
	}
	
	public:
	
	Vector() : vec(vector<int>(n)) {}
	Vector(const vector<int> &_vec) {
		assert(sz(_vec) == n);
		vec = _vec;
		for (int i = 0; i < n; i++) _mag += vec[i] * vec[i];
		_mag = sqrtl(_mag);
	}
	
	vector<int> elements() {return vec;}
	const vector<int>& celements() {return vec;}
	
	int size() {return n;}
	
	T& operator [] (int ind) {return vec[ind];}
	
	rcls operator += (cls other) {
		apply(other, [](int a, int b){return a+b;});
		return self;
	}
	rcls operator -= (cls other) {
		apply(other, [](int a, int b){return a-b;});
		return self;
	}
	rcls operator *= (cls other) {
		apply(other, [](int a, int b){return a*b;});
		return self;
	}
	rcls operator /= (cls other) {
		apply(other, [](int a, int b){return a/b;});
		return self;
	}
	friend ncls operator + (cls a, cls b) {return ncls(a) += b;}
	friend ncls operator - (cls a, cls b) {return ncls(a) -= b;}
	friend ncls operator * (cls a, cls b) {return ncls(a) *= b;}
	friend ncls operator / (cls a, cls b) {return ncls(a) /= b;}
	
	bool operator < (cls other) {return celements() < other.clemenents();}
	bool operator <= (cls other) {return celements() <= other.celements();}
	bool operator == (cls other) {return celements() == other.celements();}
	bool operator >= (cls other) {return celements() >= other.clements();}
	bool operator > (cls other) {return celements() > other.celements();}
	
	template<typename U> U& operator << (U& out) {return out << vec;}
	
	auto begin() {return vec.begin();}
	auto end() {return vec.end();}
	
	T mag() {return _mag;}
	T dot(ncls other) {
		T a = 0;
		for (int i = 0; i < n; i++) a += self[i] * other[i];
		return a;
	}
	
	// projection of this onto vector b
	T proj(rcls b) {return b * (dot(b) / b.dot(b));}
	
	#undef self
};

template<int n> using Vi = Vector<int, n>;
template<int n> using Vld = Vector<long double, n>;
template<int n> using Vd = Vector<double, n>;
template<int n> using Vs = Vector<short, n>;
