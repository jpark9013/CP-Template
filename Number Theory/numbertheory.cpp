struct NT {
	
	int n = 0;
	vector<int> hfac;  // highest factor 
	vector<int> primes;
	
	NT(int _n): n(_n) {
		hfac.resize(n+1);
		hfac.assign(n+1, 1);
		for (int i = 2; i <= n; i++) {
			if (hfac[i] == 1) {
				primes.pb(i);
				for (int j = i; j <= n; j += i) {
					hfac[j] = i;
				}
			}
		}
	}
	
	NT() {}
	
	bool isprime(int x) {
		if (x <= 1) return false;
		if (x > n) {
			for (int i = 2; i*i <= x; i++) {
				if (x % i == 0) {
					return false;
				}
			}
			return true;
		}
		return hfac[x] == x;
	}
	
	// log n 
	vector<int> factors(int x) {  // 60 -> [2, 2, 3, 5]
		assert(x >= 1 && x <= n);
		vector<int> ret; 
		while (x != 1) {
			ret.pb(hfac[x]);
			x /= hfac[x];
		} 
		reverse(all(ret));
		return ret;
	}
	
	// sqrt n
	vector<int> divisors(int x) {  
		assert(x >= 1);
		vector<int> vec;
		for (int i = 1; i*i <= x; i++) {
			if (x % i == 0) {
				vec.pb(i);
				if (i*i != x) vec.pb(x/i);
			}
		}
		vector<int> ret;
		for (int i = 0; i < sz(vec); i += 2) ret.pb(vec[i]);
		int start = sz(vec) % 2 == 0 ? sz(vec)-1 : sz(vec)-2;
		for (int i = start; i >= 1; i -= 2) ret.pb(vec[i]);
		return ret;
	}
	
	vector<int> getprimes(int lim) {
		vector<int> ret;
		for (int i : primes) {
			if (i > lim) break;
			ret.pb(i);
		}
		return ret;
	}
	
	vector<int> getprimes() {
		return primes;
	}
	
	vector<int> getnprimes(int n) {
		vector<int> ret(n);
		for (int i = 0; i < n; i++) ret[i] = primes[i];
		return ret;
	}
};
