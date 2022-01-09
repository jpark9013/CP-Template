// https://judge.yosupo.jp/submission/44879
template<int T> 
class Partition {
	
	private:
	
	// If [mod] needs to be variable, move it to the struct and initialize
	// it in the beginning of the constructor.
	template <int mod>
	struct FormalSeries {
	private:
		
		#define SZ(x) (int(x.size()))
		
		using vi = vector<int>;
		using ll = long long;
	
		int maxn;
		int root;
	
		static inline void add_mod(int &a, int b) {
			a += b;
			if (a >= mod) { a -= mod; }
		}
		static inline void sub_mod(int &a, int b) {
			a -= b;
			if (a < 0) { a += mod; }
		}
		static inline int mul_mod(int a, int b) {
			return (int)((ll)a * b % mod);
		}
		static inline int pow_mod(int a, int n) {
			int r = 1;
			while (n) {
				if (n & 1) { r = mul_mod(r, a); }
				n >>= 1;
				a = mul_mod(a, a);
			}
			return r;
		}
		static inline int inv_mod(int a) {
			return pow_mod(a, mod - 2);
		}
		static inline int div_mod(int a, int b) {
			return mul_mod(a, inv_mod(b));
		}
	
		vector<int> FindPrimeFactors(int num) {
			vector<int> ans;
			for (int p = 2; p * p <= num; ++p) {
				if (num % p == 0) {
					ans.push_back(p);
					while (num % p == 0) { num /= p; }
				}
			}
			if (num > 1) { ans.push_back(num); }
			return ans;
		}
	
		void FindGenerator() {
			vector<int> prime_factors = FindPrimeFactors(mod - 1);
			while (true) {
				const int g = rand() % (mod - 1) + 1;
				bool ok = true;
				for (int p : prime_factors) {
					if (pow_mod(g, mod / p) == 1) {
						ok = false;
						break;
					}
				}
				if (ok) {
					root = pow_mod(g, mod / maxn);
					break;
				}
			}
		}
	
		// Follows https://github.com/cuber2460/acmlib07/blob/master/code/finaly/code/FFT.cpp.
		void DFT(vi &a) const {
			const int n = a.size();
			for (int i = 1, k = 0; i < n; ++i) {
				for (int bit = n / 2; (k ^= bit) < bit; bit /= 2);;;
				if (i < k) { swap(a[i], a[k]); }
			}
			for (int len = 1, who = 0; len < n; len *= 2, ++who) {
				static vi t[32];
				vi &om = t[who];
				if (om.empty()) {
					om.resize(len + 1);
					if (who == 0) {
						om[0] = 1;
						om[1] = mod - 1;
					} else {
						const int stepg = pow_mod(root, maxn / (2 * len));
						for (int i = 0; i < len; ++i) {
							om[i] = t[who - 1][i / 2];
							if (i & 1) {
								om[i] = mul_mod(om[i], stepg);
							}
						}
					}
					om.back() = om[0];
				}
				for (int i = 0; i < n; i += 2 * len) {
					for (int k = 0; k < len; ++k) {
						const int x = a[i + k];
						const int y = mul_mod(a[i + k + len], om[k]);
						add_mod(a[i + k], y);
						a[i + k + len] = x;
						sub_mod(a[i + k + len], y);
					}
				}
			}
		}
	
		// Given n, computes some square root of n mod [mod], or -1 if no such
		// square root exists. If n != 0 and square root [R] exists, the other root
		// is given by [mod - R].
		// The algorithm uses randomness; the choice of the square root may be
		// non-deterministic.
		// The implementation uses the Tonelli-Shanks algorithm.
		int SqrtMod(int n) const {
			if (n == 0) { return 0; }
			if (pow_mod(n, (mod - 1) / 2) != 1) { return -1; }
	
			int s; int q;
			for (s = 0, q = mod - 1; q % 2 == 0; s++, q /= 2);
			if (s == 1) { return pow_mod(n, (mod + 1) / 4); }
			int z;
			do {
				z = rand() % (mod - 1) + 1;
			} while(pow_mod(z, (mod - 1) / 2) == 1);
			int c = pow_mod(z, q); int r = pow_mod(n, (q + 1) / 2);
			int t = pow_mod(n, q); int m = s;
			while (true) {
				if (t == 1) { return r; }
				int i;
				for (i = 1; pow_mod(t, 1 << i) != 1; ++i);
				int b = pow_mod(c, 1 << (m - i - 1));
				r = mul_mod(r, b); c = mul_mod(b, b);
				t = mul_mod(t, c); m = i;
			}
		}
	
		void Normalize(vi &P) const {
			while (!P.empty() && P.back() == 0) { P.pop_back(); }
			if (P.empty()) { P.push_back(0); }
		}
	
		// For GCD start
		template<int sz>
		struct PolyMatrix {
			vi elems[sz][sz];
		};
	
		template<int sz>
		PolyMatrix<sz> Mul(const PolyMatrix<sz> &A, const PolyMatrix<sz> &B) const {
			PolyMatrix<sz> ans;
			for (int i = 0; i < sz; ++i) {
				for (int j = 0; j < sz; ++j) {
					for (int k = 0; k < sz; ++k) {
						ans.elems[i][k] = Add(ans.elems[i][k],
							Mul(A.elems[i][j], B.elems[j][k]));
					}
				}
			}
			for (int i = 0; i < sz; ++i) {
				for (int j = 0; j < sz; ++j) {
					Normalize(ans.elems[i][j]);
				}
			}
			return ans;
		}
	
		template<int sz>
		vector<vi> Mul(const PolyMatrix<sz> &A, const vector<vi> &x) const {
			assert(SZ(x) == sz);
			vector<vi> ans(sz);
			for (int i = 0; i < sz; ++i) {
				for (int j = 0; j < sz; ++j) {
					ans[i] = Add(ans[i], Mul(A.elems[i][j], x[j]));
				}
				Normalize(ans[i]);
			}
			return ans;
		}
	
		// The PGCD ('half-gcd') algorithm, as in https://doi.org/10.1145/800125.804045.
		PolyMatrix<2> PGCD(const vi &A, const vi &B) const {
			assert(!A.empty() && !B.empty());
			const int da = SZ(A) - 1;
			const int db = SZ(B) - 1;
			if (da - db >= db || (da == 1 && db == 1)) {  // In paper it was incorrectly <=.
				auto Q = DivFloor(A, B);
				NegSelf(Q);
				return PolyMatrix<2>{{{vi{0}, vi{1}}, {vi{1}, Q}}};
			}
			if (da < db) {
				// Not described in paper, but needed.
				auto res = PGCD(B, A);
				swap(res.elems[0][0], res.elems[0][1]);
				swap(res.elems[1][0], res.elems[1][1]);
				return res;
			}
			const int split_deg = (da + 1) / 2;
			const int first_a_elem_idx = SZ(A) - (split_deg + 1);
			assert(first_a_elem_idx < SZ(B));
			auto R1 = PGCD(
				vi(A.begin() + first_a_elem_idx, A.end()),
				vi(B.begin() + first_a_elem_idx, B.end()));
			auto mul_polys = Mul(R1, vector<vi>{A, B});
			auto &Anew = mul_polys[0];
			auto &Bnew = mul_polys[1];
			if (SZ(Anew) - SZ(Bnew) >= SZ(Bnew)) {  // In paper it was <.
				return R1;
			}
			const int first_anew_elem_idx = SZ(Anew) - (split_deg + 1);
			assert(0 <= first_anew_elem_idx && first_anew_elem_idx < SZ(Bnew));
			auto R2 = PGCD(
				vi(Anew.begin() + first_anew_elem_idx, Anew.end()),
				vi(Bnew.begin() + first_anew_elem_idx, Bnew.end()));
			return Mul(R2, R1);
		}
	
		PolyMatrix<2> EGCD(const vi &A, const vi &B) const {
			assert(!A.empty() && !B.empty());
			const int da = SZ(A) - 1;
			const int db = SZ(B) - 1;
			auto R1 = PGCD(A, B);
			auto mul_polys = Mul(R1, vector<vi>{A, B});
			auto &Anew = mul_polys[0];
			auto &Bnew = mul_polys[1];
			if (SZ(Bnew) == 1 && Bnew[0] == 0) {
				return R1;
			}
			auto R2 = EGCD(Anew, Bnew);
			auto res = Mul(R2, R1);
			return res;
		}
		// For GCD end
	
	public:
		FormalSeries(int max_terms) {  // (max_terms = max_degree + 1)
			maxn = 1;
			while (maxn < max_terms) { maxn *= 2; }
			assert((mod - 1) % maxn == 0 && "Not enough powers of 2 in mod-1");
			FindGenerator();
		}
		
		FormalSeries() {}
	
		// Multiplies polynomials [a] and [b].
		// Expect: ~0.2s for |a|=|b|=2^19.
		vi Mul(const vi &a, const vi &b) const {
			if (a.empty() || b.empty()) { return {}; }
			int n = a.size() + b.size();
			const int ans_size = n - 1;
			if (n <= 80) {
				return MulSlow(a, b);
			}
			assert(n <= maxn);
			while (n & (n - 1)) { ++n; }
	
			static vi X, Y;
			X = a; Y = b; X.resize(n); Y.resize(n);
			DFT(X);
			DFT(Y);
			for (int i = 0; i < n; ++i) {
				X[i] = mul_mod(X[i], Y[i]);
			}
			reverse(X.begin() + 1, X.end());
			const int div = inv_mod(n);
			for (int &x : X) { x = mul_mod(x, div); }
			DFT(X);
			X.resize(ans_size);
			return X;
		}
	
		// Multiplies polynomials [a] and [b], in O(|a| * |b|) time.
		// Useful if |a| or |b| is very small.
		vi MulSlow(const vi &a, const vi &b) const {
			const int ans_size = SZ(a) + SZ(b) - 1;
			vi ans(ans_size);
			constexpr ll sub = 7LL * mod * mod;
			for (int r = 0; r < ans_size; ++r) {
				ll val = 0;
				for (int i = MAX(0, r - SZ(b) + 1); i < SZ(a); ++i) {
					const int j = r - i;
					if (j < 0) { break; }
					val += (ll)a[i] * b[j];
					if (val >= sub) { val -= sub; }
				}
				ans[r] = val % mod;
			}
			return ans;
		}
	
		vi MakeConst(int x) const {
			assert(x >= 0);
			return vi{x % mod};
		}
	
		void NegSelf(vi &A) const {
			for (int &x : A) {
				if (x) { x = mod - x; }
			}
		}
	
		void TrimSelf(vi &A, int num_terms) const {
			if (SZ(A) > num_terms) {
				A.resize(num_terms);
			}
		}
	
		vi Trim(vi A, int num_terms) const {
			TrimSelf(A, num_terms);
			return A;
		}
	
		vi Add(const vi &A, const vi &B) const {
			vi res = A;
			if (SZ(res) < SZ(B)) { res.resize(SZ(B)); }
			for (int i = 0; i < SZ(B); ++i) {
				add_mod(res[i], B[i]);
			}
			return res;
		}
	
		vi Sub(const vi &A, const vi &B) const {
			vi res = A;
			if (SZ(res) < SZ(B)) { res.resize(SZ(B)); }
			for (int i = 0; i < SZ(B); ++i) {
				sub_mod(res[i], B[i]);
			}
			return res;
		}
	
		// Returns the derivative of [Q]. [Q] must be nonempty.
		// Time complexity: O(n).
		vi Differentiate(vi Q) const {
			assert(!Q.empty());
			const int n = SZ(Q);
			for (int i = 1; i < n; ++i) {
				Q[i - 1] = mul_mod(i, Q[i]);
			}
			Q.pop_back();
			return Q;
		}
	
		// Returns the integral of [Q], with 0 as the lowest term of the result.
		// Time complexity: O(n).
		vi Integrate(const vi &Q) const {
			if (Q.empty()) { return {0}; }
			const int n = SZ(Q);
			vi P(n + 1);
			// Make inverses of 1..n.
			P[1] = 1;
			for (int i = 2; i <= n; ++i) {
				P[i] = mul_mod(mod - mod / i, P[mod % i]);
			}
			// Now, multiply them pointwise with Q.
			for (int i = 1; i <= n; ++i) {
				P[i] = mul_mod(P[i], Q[i - 1]);
			}
			return P;
		}
	
		// Given Q, |Q|=n, finds P, |P|=n such that P*Q = 1 (mod x^n).
		// If more than [n] terms are needed, simply extend [Q] by zeroes.
		// Time complexity: O(n log n).
		// Expect: ~0.4s for n = 2^19
		vi Inv(const vi &Q) const {
			// By Newton's method (x_{n+1} = x_n - f(x_n) / f'(x_n)):
			// Given Q. Find P, such that P = 1 / Q.
			// f(P) := Q - 1/P. Then, P_0 = inv(Q[0]), P_{n+1} = P_n * (2 - Q * P_n) mod x^{2^{n+1}}.
			// But Q * P_n = 1 + x^{2^n}*T (mod x^{2^{n+1}}).
			// So compute T, and then P_{n+1} = P_n - x^{2^n} * P_n * T (mod x^{2^{n+1}}).
			const int n = SZ(Q);
			assert(n > 0 && Q[0] != 0);
			assert(n <= maxn / 2);
			auto P = MakeConst(inv_mod(Q[0]));
			while (SZ(P) < n) {
				const int sz = SZ(P) * 2;
				vi Pcopy = P;
				P.resize(sz);
				Pcopy.resize(sz);
				DFT(Pcopy);
				auto cur = Trim(Q, sz);
				cur.resize(sz);
				DFT(cur);
				for (int i = 0; i < sz; ++i) {
					cur[i] = mul_mod(Pcopy[i], cur[i]);
				}
				reverse(cur.begin() + 1, cur.end()); DFT(cur);
				const int inv_sz = inv_mod(sz);
				for (int i = 0; i < sz / 2; ++i) {
					cur[i] = mul_mod(cur[i + sz / 2], inv_sz);
					cur[i + sz / 2] = 0;
				}
				// Now, [cur] stores T.
				DFT(cur);
				for (int i = 0; i < sz; ++i) {
					cur[i] = mul_mod(Pcopy[i], cur[i]);
				}
				reverse(cur.begin() + 1, cur.end()); DFT(cur);
				for (int i = 0; i < sz / 2; ++i) {
					cur[i] = mul_mod(cur[i], inv_sz);
				}
				// Now, sz/2 terms of [cur] store P_n * T.
				for (int i = 0; i < sz / 2; ++i) {
					sub_mod(P[i + sz / 2], cur[i]);
				}
	
				// Or easier, slower variant of the loop (replace everything in the loop):
				// const int sz = SZ(P) * 2;
				// auto cur = Mul(Trim(Q, sz), P);
				// TrimSelf(cur, sz);
				// NegSelf(cur);
				// add_mod(cur[0], 2);
				// P = Trim(Mul(cur, P), sz);
			}
			TrimSelf(P, n);
			return P;
		}
	
		// Given Q, |Q|=n, finds P, |P|=n such that P = log(Q) (mod x^n).
		// If more than [n] terms are needed, simply extend [Q] by zeroes.
		// Asserts that Q[0] = 1 (otherwise, the operation is not in Z_p.)
		// Time complexity: O(n log n).
		// Expect: ~0.5s for n = 2^19
		vi Log(const vi &Q) const {
			// P = log(Q) -> P' = Q' / Q. Just compute Q' / Q and integrate.
			const int n = Q.size();
			assert(n > 0 && Q[0] == 1);
			assert(n <= maxn / 2);
			auto Qdif = Differentiate(Q);
			return Integrate(Trim(Mul(Qdif, Inv(Q)), n - 1));
		}
	
		// Given Q, |Q|=n, finds P, |P|=n such that P = exp(Q) (mod x^n).
		// If more than [n] terms are needed, simply extend [Q] by zeroes.
		// Asserts that Q[0] = 0 (otherwise, the operation is not in Z_p).
		// Time complexity: O(n log n).
		// Expect: ~0.7s for n = 2^19
		vi Exp(const vi &Q) const {
			const int n = SZ(Q);
			assert(n > 0 && Q[0] == 0);
			assert(n <= maxn / 2);
			auto P = MakeConst(1);
			while (SZ(P) < n) {
				const int sz = SZ(P);
				P.resize(sz * 2);
				auto Plog = Log(P);
				TrimSelf(P, sz);
				NegSelf(Plog);
				for (int i = 0; i < SZ(Q) && i < sz * 2; ++i) {
					add_mod(Plog[i], Q[i]);
				}
				add_mod(Plog[0], 1);
				P = Trim(Mul(P, Plog), sz * 2);
			}
			TrimSelf(P, n);
			return P;
		}
	
		// Given Q, |Q|=n, finds P, |P|=n, such that P = Q^n.
		// If more terms are needed, simply extend [Q] by zeroes.
		// This method works for any formal series, even if Q[0] = 0.
		// Time complexity: O((n log n) + log M).
		// Expect: ~0.9s for n = 2^19
		vi Pow(vi Q, int M) const {
			if (Q.empty()) { return {}; }
			const int n = SZ(Q);
			assert(n <= maxn / 2);
			int pref_zero = 0;
			while (pref_zero < n && !Q[pref_zero]) { ++pref_zero; }
			if ((ll)pref_zero * M >= n) { return vi(n); }
			Q.erase(Q.begin(), Q.begin() + pref_zero);
	
			const int elem = Q[0];
			const int inv_elem = inv_mod(elem);
			for (int &x : Q) { x = mul_mod(x, inv_elem); }
			assert(Q[0] == 1);
	
			Q = Log(Q);
			for (int &x : Q) { x = mul_mod(x, M); }
			Q = Exp(Q);
			const int pwr_elem = pow_mod(elem, M);
			for (int &x : Q) { x = mul_mod(x, pwr_elem); }
	
			Q.resize(n - pref_zero * M);
			Q.insert(Q.begin(), pref_zero * M, 0);
	
			return Q;
		}
	
		// Given Q, |Q|=n, finds some P, |P|=n, such that P^2 = Q.
		// If more terms are needed, simply extend [Q] by zeroes.
		// If no such P exists, returns an empty vector.
		// This method works for any formal series, even if Q[0] = 0.
		// Time complexity: O(n log n), but with a rather large constant
		// (could be faster if we instead used a hand-crafted Newton method for sqrt).
		// Expect: ~0.9s for n = 2^19
		vi Sqrt(vi Q) const {
			if (Q.empty()) { return {}; }
			const int n = SZ(Q);
			assert(n <= maxn / 2);
			int pref_zero = 0;
			while (pref_zero < n && !Q[pref_zero]) { ++pref_zero; }
			if (pref_zero == n) { return vi(n); }
			if (pref_zero % 2 == 1) { return {}; }
			const int s2 = Q[pref_zero];
			const int s1 = SqrtMod(s2);
			if (s1 == -1) { return {}; }
	
			const int inv_s2 = inv_mod(s2);
			Q.erase(Q.begin(), Q.begin() + pref_zero);
			for (int &x : Q) { x = mul_mod(x, inv_s2); }
			assert(Q[0] == 1);
			Q.resize(n - pref_zero / 2);
	
			Q = Log(Q);
			for (int &x : Q) { x = mul_mod(x, (mod + 1) / 2); }
			Q = Exp(Q);
			for (int &x : Q) { x = mul_mod(x, s1); }
	
			Q.insert(Q.begin(), pref_zero / 2, 0);
			return Q;
		}
	
		// Given P, Q, |P|=n, |Q|=m, Q nonzero, finds some polynomial X such that
		// |P - Q * X| < m.
		// Then, P - Q * X is also P mod Q.
		// If fails (for Q=0), returns the empty vector.
		// Time complexity: O(n log n).
		vi DivFloor(vi P, vi Q) const {
			while (!P.empty() && P.back() == 0) { P.pop_back(); }
			while (!Q.empty() && Q.back() == 0) { Q.pop_back(); }
			if (Q.empty()) { return {}; }
			const int n = SZ(P);
			const int m = SZ(Q);
			if (n < m) { return {0}; }
			reverse(P.begin(), P.end()); P.resize(n - m + 1);
			reverse(Q.begin(), Q.end()); Q.resize(n - m + 1);
			vi D = Trim(Mul(P, Inv(Q)), n - m + 1);
			reverse(D.begin(), D.end());
			return D;
		}
	
		// Given P, Q, |P|=n, |Q|=m, Q nonzero, finds polynomials X, Y such that
		// Y = P - Q * X, and |Y| < m.
		// If fails (for Q=0), returns two empty vectors.
		// Time complexity: O(n log n).
		pair<vi, vi> DivMod(vi P, const vi &Q) const {
			auto X = DivFloor(P, Q);
			if (X.empty()) { return {{}, {}}; }
			if (X == vi{0}) { return {{0}, P}; }
			auto TT = Mul(X, Q);
			assert(SZ(TT) == SZ(P));
			for (int i = 0; i < SZ(Q); ++i) {
				sub_mod(P[i], TT[i]);
			}
			P.resize(SZ(Q) - 1);
			return {X, P};
		}
	
		// Given polynomial [P], |P|=n, and set [xs], |xs|=m, evaluates P
		// in each point x \in xs.
		// Time complexity: O(n log n + m log^2 m), space complexity: O(n + m log m).
		// Expect: ~1.2s for n = 2^17
		vi MultipointEval(const vi &P, const vi &xs) const {
			const int n = SZ(P);
			const int m = SZ(xs);
			if (m == 0) { return {}; }
			assert(n <= maxn / 2);
			assert(m <= maxn / 2);
			vector<vi> mod_polys(2 * m);
			for (int i = 0; i < m; ++i) {
				mod_polys[m + i] = {(mod - xs[i]) % mod, 1};
			}
			for (int i = m - 1; i > 0; --i) {
				mod_polys[i] = Mul(mod_polys[2 * i], mod_polys[2 * i + 1]);
			}
			mod_polys[1] = DivMod(P, mod_polys[1]).second;
			for (int i = 2; i < 2 * m; ++i) {
				mod_polys[i] = DivMod(mod_polys[i / 2], mod_polys[i]).second;
			}
			vi answer(m);
			for (int i = 0; i < m; ++i) {
				assert(SZ(mod_polys[m + i]) == 1);
				answer[i] = mod_polys[m + i][0];
			}
			return answer;
		}
	
		// Given sets [xs], [ys], |xs|=|ys|=n, finds a polynomial P of degree
		// <n such that P(xs[i]) = ys[i] for each i.
		// All [xs] must be different, but this method does not verify that.
		// Time complexity: O(n log^2 n), space complexity: O(n log n).
		// Expect: ~2.1s for n = 2^17
		vi Interpolation(const vi &xs, const vi &ys) const {
			const int n = SZ(xs);
			assert(SZ(ys) == n);
			if (n == 0) { return {0}; }
			assert(n <= maxn / 2);
			vector<vi> mod_polys(2 * n), coef_polys(2 * n);
			for (int i = 0; i < n; ++i) {
				mod_polys[n + i] = {(mod - xs[i]) % mod, 1};
			}
			for (int i = n - 1; i > 0; --i) {
				mod_polys[i] = Mul(mod_polys[2 * i], mod_polys[2 * i + 1]);
			}
			coef_polys[1] = {1};
			for (int i = 1; i < n; ++i) {
				coef_polys[2 * i] =
					DivMod(Mul(coef_polys[i], mod_polys[2 * i + 1]), mod_polys[2 * i]).second;
				coef_polys[2 * i + 1] =
					DivMod(Mul(coef_polys[i], mod_polys[2 * i]), mod_polys[2 * i + 1]).second;
			}
			for (int i = n; i < 2 * n; ++i) {
				assert(SZ(coef_polys[i]) == 1);
				const int coef = coef_polys[i][0];
				coef_polys[i][0] = div_mod(ys[i - n], coef);
			}
			for (int i = n - 1; i > 0; --i) {
				coef_polys[i] = Add(
					Mul(coef_polys[2 * i], mod_polys[2 * i + 1]),
					Mul(coef_polys[2 * i + 1], mod_polys[2 * i]));
			}
			return coef_polys[1];
		}
	
		// Given polynomials P, Q (n=max(|P|, |Q|)), finds polynomials
		// X, Y, D such that
		// P * X + Q * Y = D and D = gcd(P, Q) and |X| < |Q| and |Y| < |P|.
		// Time complexity: O(n log^2 n).
		// Expect: ~0.8s for n = 50,000
		tuple<vi, vi, vi> ExGCD(const vi &P, const vi &Q) const {
			assert(!P.empty() && !Q.empty());
			auto matrix = EGCD(P, Q);
			auto mul_res = Mul(matrix, vector<vi>{P, Q});
			assert(mul_res[1] == vi{0});
	
			vi X = matrix.elems[0][0];
			vi Y = matrix.elems[0][1];
			vi D = mul_res[0];
			assert(!D.empty() && D.back() != 0);
			const int mul_coef = inv_mod(D.back());
			for (int &t : X) { t = mul_mod(t, mul_coef); }
			for (int &t : Y) { t = mul_mod(t, mul_coef); }
			for (int &t : D) { t = mul_mod(t, mul_coef); }
			return {X, Y, D};
		}
	
		// Given polynomial P = \sum a_i * x^i, computes the polynomial
		// Q(x) = P(x + c) = \sum a_i * (x+c)^i.
		// Time complexity: O(n log n).
		// Expect: ~0.2s for n = 2^19.
		vi TaylorShift(const vi &P, int c) const {
			const int n = SZ(P);
			vi F(n), G(n), inv_f(n);
			F[0] = 1;
			for (int i = 1; i < n; ++i) {
				F[i] = mul_mod(F[i - 1], i);
			}
			inv_f.back() = inv_mod(F.back());
			for (int i = n - 2; i >= 0; --i) {
				inv_f[i] = mul_mod(inv_f[i + 1], i + 1);
			}
			int powc = 1;
			for (int i = 0; i < n; ++i) {
				F[i] = mul_mod(F[i], P[i]);
				G[n - i - 1] = mul_mod(powc, inv_f[i]);
				powc = mul_mod(powc, c);
			}
			auto conv = Mul(F, G);
			for (int i = 0; i < n; ++i) {
				F[i] = mul_mod(conv[n + i - 1], inv_f[i]);
			}
			return F;
		}
	
		// Computes the signed Stirling numbers of the first kind s(N, k), given
		// by: x(x - 1)(x - 2)...(x - (N - 1)) = \sum_{k=0}^N s(N, k) x^k.
		// Time complexity: O(n log n).
		// Expect: ~0.2s for n = 500,000.
		vi MakeStirlingFirstKind(int N) const {
			if (N == 0) { return vi{1}; }
			auto res = MakeStirlingFirstKind(N / 2);
			res = Mul(res, TaylorShift(res, mod - (N / 2)));
			if (N % 2 == 1) {
				res = MulSlow(res, vi{mod - N + 1, 1});
			}
			return res;
		}
	
		// Computes the signed Stirling numbers of the second kind S(N, k), given
		// by: x^N = \sum_{k=0}^N S(N, k) * x(x - 1)(x - 2)...(x - (k - 1)).
		// Time complexity: O(n log n).
		// Expect: <0.2s for n = 500,000.
		vi MakeStirlingSecondKind(int N) const {
			vi A(N + 1);
			A[0] = 1;
			for (int i = 1; i <= N; ++i) { A[i] = mul_mod(A[i - 1], i); }
			A.back() = inv_mod(A.back());
			for (int i = N - 1; i >= 0; --i) { A[i] = mul_mod(A[i + 1], i + 1); }
			vi B = A;
			for (int i = 1; i <= N; i += 2) { B[i] = mod - B[i]; }
			for (int i = 0; i <= N; ++i) { A[i] = mul_mod(A[i], pow_mod(i, N)); }
			return Trim(Mul(A, B), N + 1);
		}
	
		// Computes Bernoulli numbers B(0)..B(N), with the convention B(1) = -1/2.
		// With the convention, the Faulhaber's formula is as follows:
		// sum_{k=1}^n k^m =
		//	 = 1/(m + 1) * \sum_{j=0}^m [(-1)^j * \binom{m + 1}{j} * B(j) * n^{m + 1 - j}].
		// Time complexity: O(n log n).
		// Expect: <0.2s for n = 500,000.
		vi MakeBernoulli(int N) const {
			// Use the egf: t/(e^t - 1) = 1/(1 + t/2 + t^2/6 + t^3/24 + ...).
			vi A(N + 1), B(N + 1);
			A[0] = 1;
			for (int i = 1; i <= N; ++i) { A[i] = mul_mod(A[i - 1], i); }
			B.back() = inv_mod(mul_mod(A.back(), N + 1));
			for (int i = N - 1; i >= 0; --i) { B[i] = mul_mod(B[i + 1], i + 2); }
			B = Inv(B);
			for (int i = 0; i <= N; ++i) { B[i] = mul_mod(B[i], A[i]); }
			return B;
		}
	
		// Computes partition numbers p(0)..p(N).
		// Time complexity: O(n log n).
		vi MakePartitionNumbers(int N) const {
			// Use Euler's pentagonal formula:
			// \sum_{n>=0} p(n)x^n = 1/[\sum_{k=-oo}^{oo} (-1)^k x^{k(3k-1)/2}].
			vi A(N + 1);
			A[0] = 1;
			for (int k = 1;; ++k) {
				const int x = k * (3 * k - 1) / 2;
				if (x > N) { break; }
				const int coef = k % 2 == 0 ? 1 : mod - 1;
				A[x] = coef;
				const int y = k * (3 * k + 1) / 2;
				if (y <= N) { A[y] = coef; }
			}
			return Inv(A);
		}
		
		#undef SZ
	};
	
	vector<int> data;
	
	public:
	
	Partition() {}
	Partition(int N) {
		FormalSeries<T> fft(N * 2 + 10);
		data = fft.MakePartitionNumbers(N);
	}
	
	vector<int> get() {return data;}
};

// usage:
// Partition<998244353> p(n); 
