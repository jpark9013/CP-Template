struct montgomery64 {
	using i64 = int64_t;
	using u64 = uint64_t;
	using u128 = __uint128_t;

	static u64 mod, r, n2;

	static u64 get_r() {
		u64 res = mod;
		for (int _ = 0; _ < 5; _++) res *= 2 - mod * res;
		return -res;
	}

	static void set_mod(u64 m) {
		assert(m < (1ULL << 62));
		assert((m & 1) == 1);
		mod = m;
		n2 = -u128(m) % m;
		r = get_r();
		assert(r * mod == -1ULL);
	}
	static u64 get_mod() { return mod; }

	static u64 reduce(const u128& x) noexcept { return (x + u128(u64(x) * r) * mod) >> 64; }

	u64 v;
	montgomery64() : v(0) {}
	montgomery64(const i64& v) : v(reduce((u128(v) + mod) * n2)) {}
	u64 value() const {
		u64 res = reduce(v);
		return res >= mod ? res - mod : res;
	}
	montgomery64& operator+=(const montgomery64& rhs) {
		if (i64(v += rhs.v - (mod << 1)) < 0) v += mod << 1;
		return *this;
	}
	montgomery64& operator-=(const montgomery64& rhs) {
		if (i64(v -= rhs.v) < 0) v += mod << 1;
		return *this;
	}
	montgomery64& operator*=(const montgomery64& rhs) {
		v = reduce(u128(v) * rhs.v);
		return *this;
	}
	montgomery64 operator+(const montgomery64& rhs) const { return montgomery64(*this) += rhs; }
	montgomery64 operator-(const montgomery64& rhs) const { return montgomery64(*this) -= rhs; }
	montgomery64 operator*(const montgomery64& rhs) const { return montgomery64(*this) *= rhs; }
	bool operator==(const montgomery64& rhs) const {
		return (v >= mod ? v - mod : v) == (rhs.v >= mod ? rhs.v - mod : rhs.v);
	}
	bool operator!=(const montgomery64& rhs) const {
		return (v >= mod ? v - mod : v) != (rhs.v >= mod ? rhs.v - mod : rhs.v);
	}
	montgomery64 pow(u64 n) const {
		montgomery64 self(*this), res(1);
		while (n > 0) {
			if (n & 1) res *= self;
			self *= self;
			n >>= 1;
		}
		return res;
	}
	friend istream& operator>>(istream& s, montgomery64& rhs) {
		i64 v;
		rhs = montgomery64{(s >> v, v)};
		return s;
	}
	friend ostream& operator<<(ostream& s, const montgomery64& rhs) { return s << rhs.v; }
};
typename montgomery64::u64 montgomery64::mod, montgomery64::r, montgomery64::n2;

struct Factorizer {
	
	using u64 = uint64_t;
	
	u64 rng(u64 n) { return uniform_int_distribution<u64>(0, n - 1)(RNG); }
	
	bool miller_rabin(const u64& n, const vector<u64>& as) {
		if (montgomery64::get_mod() != n) montgomery64::set_mod(n);
		const u64 d = (n - 1) >> __builtin_ctzll(n - 1);
		const montgomery64 one(1), minus_one(n - 1);
		for (u64 a : as) {
			if (n <= a) break;
			u64 t = d;
			montgomery64 y = montgomery64(a).pow(t);
			while (t != n - 1 && y != one && y != minus_one) {
				y *= y;
				t <<= 1;
			}
			if (y != minus_one && t % 2 == 0) return false;
		}
		return true;
	}
	bool is_prime(const u64& n) {
		if (n == 2 || n == 3 || n == 5 || n == 7) return true;
		if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;
		if (n < 121) return n > 1;
		if (n < (1ULL << 32)) return miller_rabin(n, {2, 7, 61});
		return miller_rabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
	}
	
	u64 pollard_rho(const u64& n) {
		if (~n & 1) return 2;
		if (is_prime(n)) return n;
		if (montgomery64::get_mod() != n) montgomery64::set_mod(n);
		montgomery64 R, one(1);
		auto f = [&](const montgomery64& x) { return x * x + R; };
		constexpr int m = 128;
		while (1) {
			montgomery64 x, y, ys, q = one;
			R = rng(n - 2) + 2, y = rng(n - 2) + 2;
			u64 g = 1;
			for (int r = 1; g == 1; r <<= 1) {
				x = y;
				for (int i = 0; i < r; i++) y = f(y);
				for (int k = 0; g == 1 && k < r; k += m) {
					ys = y;
					for (int i = 0; i < min(m, r - k); i++) q *= x - (y = f(y));
					g = gcd(q.value(), n);
				}
			}
			if (g == n) {
				do g = gcd((x - (ys = f(ys))).value(), n);
				while (g == 1);
			}
			if (g != n) return g;
		}
		cerr << "failed" << '\n';
		assert(false);
		return -1;
	}
	
	vector<u64> inner_factorize(u64 n) {
		if (n <= 1) return {};
		u64 p = pollard_rho(n);
		if (p == n) return {p};
		auto l = inner_factorize(p);
		auto r = inner_factorize(n / p);
		copy(r.begin(), r.end(), back_inserter(l));
		return l;
	}
	vector<u64> factorize(u64 n) {
		auto res = inner_factorize(n);
		sort(res.begin(), res.end());
		return res;
	}  
} fz;  // call .factorize(), already sorted
