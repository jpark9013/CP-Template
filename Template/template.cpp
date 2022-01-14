#ifndef _LOCAL
  #pragma GCC optimize("O3")
  #pragma GCC optimize("unroll-loops")
  #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#endif
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define eb emplace_back
#define fi first
#define google_codejam int MMR; cin>>MMR; for (int i = 1; i <= MMR; i++) {cout << "Case #" << i << ": "; solve();}
#define int int64_t
#define isint(a) typename a, enable_if_t<is_integral<a>::value, bool> = true
#define isfloat(a) typename a, enable_if_t<is_floating_point<a>::value, bool> = true
#define left gazzy_garcia_ioi
#define len(x) (int(sizeof(x)/sizeof(x[0])))
#define mp make_pair
#define output_time cerr << "Time elapsed: " << 1000*clock() / CLOCKS_PER_SEC << "ms" << '\n'
#define pb push_back
#define right bossreaper_sucks_at_csgo
#define se second
#define sep cerr << "-----------------------------\n" 
#define short int32_t
#define sz(x) (int(x.size()))
#define test_cases int MMR; cin>>MMR; for (int i = 0; i < MMR; i++) 
#define test_input ifstream in("input.txt"); if (in) cin.rdbuf(in.rdbuf());
#define test_local freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); freopen("error.txt", "w", stderr)

typedef long double ld;
typedef __int128 LL;
using namespace std;
typedef pair<int, int> pii;
typedef pair<ld, ld> pld;
typedef pair<LL, LL> pLL;
typedef pair<int32_t, int32_t> spii;
template<class T> using minpq = priority_queue<T, vector<T>, greater<T>>;
template<class T> using maxpq = priority_queue<T, vector<T>>;
template<class A, class B> using pq = priority_queue<A, vector<A>, B>;

#ifdef _LOCAL
  void debug_out() {cerr << endl;}
  template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
    cerr << H << ", ";
    debug_out(T...);
  }
  #define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
  #define debug(...)
#endif

const int INTMAX = 9223372036854775807;
const int INTMIN = -9223372036854775807;
const ld pi = 3.1415926535897932385;

template<typename A, typename B> auto MIN(const A &a, const B &b) {return ((a) < (b) ? (a) : (b));}
template<typename A, typename B> auto MAX(const A &a, const B &b) {return ((a) > (b) ? (a) : (b));}

mt19937 RNG{random_device{}()};
template<typename T> T rand(const T &a, const T &b) {
  T m = b - a + 1;
  return a + RNG() % m;
}

struct custom_hash {
  
  template<int32_t m> 
  struct Hasher {
    
    private:
    
    static_assert(m >= 1, "Mod must be at least 1.");
  
    // change if necessary, but 
    // i really don't think strings will pass 5e5 in length
    static const int N = 5e5; 
    
    array<int32_t, N> powers;
    int p;
    bool a = false;
    
    int norm(int x) const {
      if (-m < x && x < m) {
        if (x < 0) x += m;
        return x;
      }
      return x % m;
    }
    
    void add(int &a, int b) const {
      int c = a + b;
      if (c >= m) c -= m;
      a = c;
    }
    
    void build() {
      powers[0] = 1;
      for (int i = 1; i < N; i++) {
        powers[i] = norm(powers[i - 1] * p);
      }
    }
    
    public:
    
    Hasher(int P) : p(P) {
      build();
    }
    
    Hasher() {}
    
    uint64_t get(const string &s) const {
      int v = 0;
      for (int i = 0; i < s.size(); i++) {
        add(v, norm(int64_t(powers[i]) * (s[i] - 'a')));
      }
      
      return uint64_t(v);
    }
  };
  
  struct HashTable {
    
    private:
    
    static constexpr int a = 1e9 + 7, b = 1e9 + 9;
    static constexpr int c = 1e6 + 3, d = 1e5 + 3;
    
    Hasher<a> hash1;
    Hasher<b> hash2;
    
    public:
    
    HashTable() {
      hash1 = Hasher<a>(c);
      hash2 = Hasher<b>(d);
    }
    
    pair<uint64_t, uint64_t> get(const string &s) const {
      return make_pair(hash1.get(s), hash2.get(s));  
    }
  } ht;
  
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  
  size_t get_pair(const pair<uint64_t, uint64_t> &x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
  }
  
   size_t operator()(const uint64_t &x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
  
  size_t operator()(const pair<uint64_t, uint64_t> &x) const {
    return get_pair(x);
  }
  
  size_t operator()(const string &s) const {
    return get_pair(ht.get(s));
  }
};

template<typename K, typename V> using umap = unordered_map<K, V, custom_hash>;
template<typename K, typename V> using umultimap = unordered_multimap<K, V, custom_hash>;
template<typename T> using uset = unordered_set<T, custom_hash>;
template<typename T> using umultiset = unordered_multiset<T, custom_hash>;

bool setin(const string &s) {ifstream in(s.c_str()); if (in) freopen(s.c_str(), "r", stdin); return bool(in);}
void setout(const string &s) {freopen(s.c_str(), "w", stdout);}
void open(const string &s) {if (setin(s+".in")) setout(s+".out");}
template<typename A, typename B> ostream& operator<<(ostream &out, pair<A, B> const &pair);
template<typename T> ostream& operator<<(ostream &out, uset<T> const &s);
template<typename T> ostream& operator<<(ostream &out, set<T> const &s);
template<typename T> ostream& operator<<(ostream &out, multiset<T> const &s);
template<typename T> ostream& operator<<(ostream &out, umultiset<T> const &s);
template<typename K, typename V> ostream& operator<<(ostream &out, multimap<K, V> const &m);
template<typename K, typename V> ostream& operator<<(ostream &out, umultimap<K, V> const &m);
template<typename T> ostream& operator<<(ostream &out, vector<T> const &v);
template<typename K, typename V> ostream& operator<<(ostream &out, map<K, V> const &m);
template<typename K, typename V> ostream& operator<<(ostream &out, umap<K, V> const &m);
template<typename T> ostream& operator<<(ostream &out, deque<T> d);
template<typename T> ostream& operator<<(ostream &out, stack<T> s);
template<typename A, typename B> ostream& operator<<(ostream &out, pq<A, B> heap);
ostream& operator<<(ostream &out, LL x);
template<typename A, typename B> ostream& operator<<(ostream &out, pair<A, B> const &pair) {
  out << "(" << pair.first << ", " << pair.second;
  return out << ")";
}
template<typename T> ostream& operator<<(ostream &out, uset<T> const &s) {
  out << "["; int c = 0;
  for (T i : s) {if (c) out << ", "; out << i; c++;}
  return out << "]";
}
template<typename T> ostream& operator<<(ostream &out, set<T> const &s) {
  out << "["; int c = 0;
  for (T i : s) {if (c) out << ", "; out << i; c++;}
  return out << "]";
}
template<typename T> ostream& operator<<(ostream &out, vector<T> const &v) {
  out << "[";
  for (int i = 0; i < v.size(); i++) {if (i) out << ", "; out << v[i];}
  return out << "]";
}
template<typename K, typename V> ostream& operator<<(ostream &out, map<K, V> const &m) {
  out << "{"; int c = 0;
  for (const auto &pair : m) {if (c) out << ", "; out << pair.first << "=" << pair.second; c++;}
  return out << "}";
}
template<typename K, typename V> ostream& operator<<(ostream &out, umap<K, V> const &m) {
  out << "{"; int c = 0;
  for (const auto &pair : m) {if (c) out << ", "; out << pair.first << "=" << pair.second; c++;}
  return out << "}";
}
template<typename T> ostream& operator<<(ostream &out, multiset<T> const &s) {
  out << "["; int c = 0;
  for (T i : s) {if (c) out << ", "; out << i; c++;}
  return out << "]";
}
template<typename T> ostream& operator<<(ostream &out, umultiset<T> const &s) {
  out << "["; int c = 0;
  for (T i : s) {if (c) out << ", "; out << i; c++;}
  return out << "]";
}
template<typename K, typename V> ostream& operator<<(ostream &out, multimap<K, V> const &m) {
  out << "{"; int c = 0;
  for (const auto &pair : m) {if (c) out << ", "; out << pair.first << "=" << pair.second; c++;}
  return out << "}";
}
template<typename K, typename V> ostream& operator<<(ostream &out, umultimap<K, V> const &m) {
  out << "{"; int c = 0;
  for (const auto &pair : m) {if (c) out << ", "; out << pair.first << "=" << pair.second; c++;}
  return out << "}";
}
template<typename T> ostream& operator<<(ostream &out, deque<T> d) {
  out << "["; int c = 0;
  while (!d.empty()) {if (c) out << ", "; out << d.front(); d.pop_front(); c++;}
  return out << "]";
}
template<typename T> ostream& operator<<(ostream &out, stack<T> s) {
  out << "["; int c = 0;
  while (!s.empty()) {if (c) out << ", "; out << s.top(); s.pop(); c++;}
  return out << "]";
}
template<typename A, typename B> ostream& operator<<(ostream &out, pq<A, B> heap) {
  out << "["; int c = 0;
  while (!heap.empty()) {if (c) out << ", "; out << heap.top(); heap.pop(); c++;}
  return out << "]";
}
ostream& operator<<(ostream &out, LL n) {
  if (n < 0) {
    out.put('-');
    n = -n;
  }
  if (n > 9) out << n / 10;
  return out.put(n % 10 + '0');
}
istream& operator>>(istream &in, LL &n) {
  n = 0; 
  LL f = 1;
  char c; in.get(c);
  while (c < '0' || c > '9') {
    if (in.eof()) assert(false && "Reached EOF before reading next __int128.");
    if (c == '-') f = -1;
    in.get(c);
  }
  while (!in.eof() && c >= '0' && c <= '9') {
    n = n * 10 + c - '0';
    in.get(c);
  } 
  n *= f;
  return in;
}
template<typename A, typename B> istream& operator>>(istream &in, pair<A, B> &pair) {return in >> pair.first >> pair.second;}

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

template<typename T> void next_vec(vector<T> &vec, int l) {
  vec = vector<T>(l);
  for (int i = 0; i < l; i++) cin >> vec[i];
}
template<typename T> void next_grid(vector<vector<T>> &vec, int h, int w) {
  vec = vector<vector<T>>(h, vector<T>(w));
  for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) cin >> vec[i][j];
}
template<typename T> void next_graph(vector<vector<T>> &adj, int nodes, int edges) {
  adj = vector<vector<int>>(nodes);
  for (int i = 0; i < edges; i++) {
    int a, b; cin >> a >> b;
    a--; b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
}
template<typename T> void next_directed_graph(vector<vector<T>> &adj, int nodes, int edges) {
  adj = vector<vector<int>>(nodes);
  for (int i = 0; i < edges; i++) {
    int a, b; cin >> a >> b;
    a--; b--;
    adj[a].pb(b);
  }
}
template<typename T> void next_weighted_graph(vector<vector<pair<int, T>>> &adj, int nodes, int edges) {
  adj = vector<vector<pair<int, T>>>(nodes);
  for (int i = 0; i < edges; i++) {
    int a, b; T c; cin >> a >> b >> c;
    a--; b--;
    adj[a].eb(mp(b, c));
    adj[b].eb(mp(a, c));
  }
}
template<typename T> void next_dw_graph(vector<vector<pair<int, T>>> &adj, int nodes, int edges) {
  adj = vector<vector<pair<int, T>>>(nodes);
  for (int i = 0; i < edges; i++) {
    int a, b; T c; cin >> a >> b >> c;
    a--; b--;
    adj[a].eb(mp(b, c));
  }
}
string join(const vector<string> &vec, const string &t) {
  int l = vec.size();
  string s;
  for (int i = 0; i < l; i++) {
    s += vec[i];
    if (i != l-1) s += t;
  }
  return s;
}
template<typename T> void shuffle_vec(vector<T> &vec) {
  shuffle(vec.begin(), vec.end(), mt19937(random_device()()));
}
int gcd(int a, int b) {
  assert(a >= 1 && b >= 1);
  return __gcd(a, b);
}
int lcm(int a, int b) {return a/gcd(a, b)*b;}
vector<string> split(const string& str, const string& delim = " ") {
  vector<string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == string::npos) pos = str.length();
    string token = str.substr(prev, pos-prev);
    if (!token.empty()) tokens.push_back(token);
    prev = pos + delim.length();
  }
  while (pos < str.length() && prev < str.length());
  return tokens;
}
template<typename T> int sum(const T &x) {return accumulate(all(x), 0ll);}
template<typename A, typename B> int sum(const A &x, const B &f) {return accumulate(all(x), 0ll, f);}
template<typename T> int mine(const T &x) {return *min_element(all(x));} 
template<typename A, typename B> int mine(const A &x, const B &f) {return *min_element(all(x), f);}
template<typename T> int maxe(const T &x) {return *max_element(all(x));}
template<typename A, typename B> int maxe(const A &x, const B &f) {return *max_element(all(x), f);}
template<typename T> int mini(const T &x) {return min_element(all(x)) - x.begin();}
template<typename A, typename B> int mini(const A &x, const B &f) {return min_element(all(x), f);}
template<typename T> int maxi(const T &x) {return max_element(all(x)) - x.begin();}
template<typename A, typename B> int maxi(const A &x, const B &f) {return max_element(all(x), f) - x.begin();}
template<typename A, typename B> int lowb(const A &a, const B &b) {return lower_bound(all(a), b) - a.begin();}
template<typename A, typename B, typename C> int lowb(const A &a, const B &b, const C &f) {return lower_bound(all(a), b, f) - a.begin();}
template<typename A, typename B> int uppb(const A &a, const B &b) {return upper_bound(all(a), b) - a.begin();}
template<typename A, typename B, typename C> int uppb(const A &a, const B &b, const C &f) {return upper_bound(all(a), b, f) - a.begin();}
template<typename A, typename B> bool bs(const A &a, const B &b) {return binary_search(all(a), b);} 
template<typename A, typename B, typename C> bool bs(const A &a, const B &b, const C &f) {return binary_search(all(a), b, f);}
template<typename T> umap<T, int> compress(const vector<T> &vec) {
  vector<T> sorted = vec;
  sort(all(sorted));
  int l = sorted.size();
  umap<T, int> m;
  for (int i = 0; i < l; i++) m[sorted[i]] = i;
  return m;
}
template <typename T> T power(T a, int b) {
  assert(b >= 0);
  T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}
template<typename A, typename B> bool cmin(A &a, const B &b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}
template<typename A, typename B> bool cmax(A &a, const B &b) {
  if (b > a) {
    a = b;
    return true;
  }
  return false;
}

// If interactive, change above
#ifndef _LOCAL 
  #ifdef _IACTIVE
    #define endl _ENDL
  #else
    #define endl '\n'
  #endif
#else 
  #define endl _ENDL
#endif

#define inf 1e18
#define yes() {cout << "YES" << endl; return;}
#define no() {cout << "NO" << endl; return;}

void solve() {
  
}

int32_t main() {
  open("fcolor");
  cerr.precision(16);
  test_cases
  solve();
  //output_time;
}
