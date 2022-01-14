struct MC {
  vector<mod> _fac, _inv;
  int n = 0;
  
  MC() {}
  MC(int _n) : n(_n) {
    assert(n >= 1);
    _fac.resize(n+1);
    _inv.resize(n+1);
    _fac[0] = 1;
    _fac[1] = 1;
    _inv[0] = 1;
    _inv[1] = 1;
    
    for (int i = 2; i <= n; i++) _fac[i] = _fac[i-1] * i;
    _inv[n] = inverse(int(_fac[n]), int(mod::mod()));
    for (int i = n-1; i >= 2; i--) _inv[i] = _inv[i+1] * (i+1);
  }
  
  mod comb(int a, int b) {
    assert(n != 0 && a <= n && b <= n);
    if (a < b) return 0;
    return _fac[a] * _inv[b] * _inv[a-b];
  }
  
  mod fac(int a) {
    assert(a >= 0 && a <= n);
    return _fac[a];
  }
  
  mod inv(int a) {
    assert(a >= 0 && a <= n);
    return _inv[a];
  }
};
