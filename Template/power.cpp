template <typename T> T power(T a, int b) {
  assert(b >= 0);
  T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}

// find mod of a^b
mod expo(ll a, ll b) { 
  assert(b >= 0);
  if (b >= _MOD-1) b %= (_MOD-1);
  return power(mod(a), b);
}

template<int T> modnum<T> expo(ll a, ll b) {
  assert(b >= 0);
  if (b >= T-1) b %= (T-1);
  return power(modnum<T>(a), b);
}
