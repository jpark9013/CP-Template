// works in 250ms for n=1e11, in ~1s for n=1e12
// O(n^2/3 logn)
// just call pc.count(n)
struct PC {
  
  int32_t *s, *smalls, *roughs;
  int64_t *larges;
  bool *skip;
  
  int64_t count(int64_t n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    
    const int32_t v = sqrtl(n);  
    int32_t s = (v + 1) / 2; 
    smalls = new int32_t[s]; for (int32_t i = 1; i < s; i++) smalls[i] = i;
    roughs = new int32_t[s]; for (int32_t i = 0; i < s; i++) roughs[i] = 2 * i + 1;
    larges = new int64_t[s]; for (int32_t i = 0; i < s; i++) larges[i] = (n / (2 * i + 1) - 1) / 2;
    skip = new bool[v + 1];
    memset(skip, 0, sizeof(bool) * (v + 1));

    #define _DIVIDE(n, d) ((int32_t)((double)(n)/d))
    #define _HALF(n) (((n)-(1))>>(1))

    int32_t pc = 0;
    for (int32_t p = 3; p <= v; p += 2) if (!skip[p]) {
      int32_t q = p * p;
      if ((int64_t)q * q > n) break;
      skip[p] = true;
      for (int32_t i = q; i <= v; i += 2 * p) skip[i] = true;
      int32_t ns = 0;
      for (int32_t k = 0; k < s; k++) {
        int32_t i = roughs[k];
        if (skip[i]) continue;
        int64_t d = (int64_t)i * p;
        larges[ns] = larges[k] - (d <= v ? larges[smalls[d >> 1] - pc] : smalls[_HALF(_DIVIDE(n, d))]) + pc;
        roughs[ns++] = i;
      }
      s = ns;
      for (int32_t i = _HALF(v), j = ((v / p) - 1) | 1; j >= p; j -= 2) {
        int32_t c = smalls[j >> 1] - pc;
        for (int32_t e = (j * p) >> 1; i >= e; i--) smalls[i] -= c;
      }
      pc++;
    }
    larges[0] += (int64_t)(s + 2 * (pc - 1)) * (s - 1) / 2;
    for (int32_t k = 1; k < s; k++) larges[0] -= larges[k];
    for (int32_t l = 1; l < s; l++) {
      int64_t q = roughs[l];
      int64_t M = n / q;
      int32_t e = smalls[_HALF(M / q)] - pc;
      if (e < l + 1) break;
      int64_t t = 0;
      for (int32_t k = l + 1; k <= e; k++) t += smalls[_HALF(_DIVIDE(M, roughs[k]))];
      larges[0] += t - (int64_t)(e - l) * (pc + l - 1);
    }

    #undef _DIVIDE
    #undef _HALF

    return larges[0] + 1;
  }
  
  ~PC() {
    delete[] s;
    delete[] smalls;
    delete[] roughs;
    delete[] larges;
  }
  
} pc;
