struct _ENDLINE {
  
} _ENDL;

// #define _IACTIVE 

struct FastIO {
  
  private:
  
  #if defined(_IACTIVE) || defined(_LOCAL)
    #ifdef _WIN32
      inline char gcu() {return _getchar_nolock();}
      inline void pcu(char x) {_putchar_nolock(x);}
    #else
      inline char gcu() {return getchar_unlocked();}
      inline void pcu(char x) {putchar_unlocked(x);}
    #endif
  #else
    inline char gcu() {
      if (pos == len) {
        pos = 0;
        len = fread(rbuf, 1, bsz, stdin);
      }
      return rbuf[pos++];
    }
    inline void pcu(char x) {
      if (wp == bsz) {
        fwrite(wbuf, 1, bsz, stdout);
        wp = 0;
      }
      wbuf[wp++] = x;
    }
  #endif
  
  typedef __uint128_t big;
  
  char *buffer, *rbuf, *wbuf, *digit;
  big *pow10;
  int32_t pos = 0, len = 0, wp = 0, bmax = 41, bsz = 1 << 15, precision = 40, dfp;
  
  inline bool valid(char x) {return !isspace(x) && x != EOF;}
  
  inline big get_decimal(int32_t &c, int32_t &digits) {
    big value = 0;
    for (digits = 0; isdigit(c); digits++) {
      value = value * 10 + (c - '0');
      c = gcu();
    }
    return value;
  }
  
  inline char next() {
    char c = gcu();
    while (isspace(c)) c = gcu();
    return c;
  }
  
  template<typename T> void pint(T n) {
    int32_t i = bmax;
    bool neg = false;
    if (n < 0) {
      neg = true;
      n = -n;
    }
    do {
      buffer[--i] = (n % 10) + '0';
      n /= 10;
    } while (n);
    if (neg) buffer[--i] = '-';
    do {
      pcu(buffer[i]);
    } while (++i < bmax);
  } 
  
  template<typename T> void rint(T &x) {
    x = 0;
    char c;
    bool neg = false;
    while (true) {
      c = gcu();
      if (c == '-') {
        neg = true;
        break;
      } 
      if (c >= '0' && c <= '9') {
        x = c - '0';
        break;
      }
    }
    while (isdigit(c = gcu())) {
      x = x * 10 + (c - '0');
    }
    if (neg) x = -x;
  }
  
  public:
  
  FastIO(int32_t _precision = 9): dfp(_precision) {
    buffer = new char[bmax];
    pow10 = new big[precision];
    digit = new char[precision];
    big p = 1;
    for (int32_t i = 0; i < precision; i++) {
      pow10[i] = p;
      p *= 10;
    }
    rbuf = new char[bsz];
    wbuf = new char[bsz];
  }
  
  #define read FastIO& operator >>
  #define get(x) (*this) >> x
  #define ris return *this

  template<isint(Int)> read(Int &x) {rint(x); ris;}
  read(LL &x) {rint(x); ris;}
  
  template<isfloat(Float)> read(Float &n) {
    bool neg = false;
    int32_t digits, c = next();
    if (c == '-') {
      neg = true;
      c = gcu();
    }
    if (n = get_decimal(c, digits), c == '.') {
      c = gcu();
      const big f = get_decimal(c, digits), q = pow10[digits];
      n *= q;
      n += f;
      n /= q;
    }
    if (neg) n = -n;
    ris;
  }
  
  read(char &x) {while (!valid(x = gcu())) {} return *this;}
  
  read(string &s) {
    s.clear();
    char c;
    while (!valid(c = gcu())) ;
    s += c;
    while (valid(c = gcu())) s += c;
    ris;
  } 
  
  template<typename A, typename B> read(pair<A, B> &p) {
    get(p.first);
    get(p.second);
    ris;
  }
  
  #undef read
  #undef get
  
  string getline() {
    string s;
    char c;
    while ((c = gcu()) != '\n' && c != EOF) s += c;
    return s;
  }
  
  #define print FastIO& operator << 
  
  template<isint(Int)> print(Int n) {
    pint(n);
    ris;
  }
  
  print(LL n) {pint(n); ris;}
  
  template<isfloat(Float)> print(Float n) {
    if (n < 0) {
      pcu('-');
      n = -n;
    }
    const big p = pow10[dfp];
    const big x = roundl(n*p);
    pint(x/p); pcu('.');
    big r = x % p;
    for (int32_t i = 0; i < dfp; i++) {
      digit[i] = r % 10;
      r /= 10;
    }
    for (int32_t i = dfp-1; i >= 0; i--) pcu(digit[i] + '0');
    ris;
  }
  
  print(const char &c) {pcu(c); ris;}
  
  print(const string &s) {for (char i : s) pcu(i); ris;}
  print(const char * s) {
    for (const char * ptr = s; *ptr != '\0'; ptr++) pcu(*ptr);
    ris;
  }
  
  print(const _ENDLINE &x) {
    pcu('\n');
    flush();
    ris;
  }
  
  #undef print
  #undef ris
  
  #ifdef _IACTIVE
    inline void flush() {fflush(stdout);}
  #else
    inline void flush() {
      if (wp) fwrite(wbuf, 1, wp, stdout);
      wp = 0;
    }
  #endif
  
  ~FastIO() {
    flush();
    delete[] buffer;
    delete[] rbuf;
    delete[] wbuf;
    delete[] digit;
    delete[] pow10;
  }
} _FR;

#define cin _FR
#define cout _FR
