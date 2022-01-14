struct frac {
  int num, den;
  frac() {num = 0; den = 1;}  
  frac(int a, int b, bool s = true) {assert(b); num = a; den = b; if (s) simplify();}
  frac(pii pair, bool s = true) {assert(pair.second); num = pair.first; den = pair.second; if (s) simplify();}
  frac(int a) {num = a; den = 1;}
  frac(string &a, bool s = true) {
    vector<string> vec = split(a, "/");
    assert(vec.size()==2);
    num = stoll(vec[0]);
    den = stoll(vec[1]);
    if (s) simplify();
  } 
  int ncd(int a, int b) {return gcd(abs(a), abs(b));}
  void simplify() {int g = ncd(num, den); num /= g; den /= g;}
  ld value() {return (ld)num/(ld)den;}
  friend std::ostream& operator << (std::ostream& out, const frac& n) { 
    if (n.den < 0) return out << n.num*-1 << "/" << n.den*-1;
    return out << n.num << "/" << n.den; 
  }
  friend std::istream& operator >> (std::istream& in, frac& n) {in >> n.num; n.den = 1; return in;}
  friend bool operator == (const frac &a, const frac &b) {return a.num == b.num && a.den == b.den;}
  friend bool operator != (const frac &a, const frac &b) {return a.num != b.num || a.den != b.den;}
  friend bool operator >= (const frac &a, const frac &b) {return a.num*b.den >= a.den*b.num;}
  friend bool operator <= (const frac &a, const frac &b) {return a.num*b.den <= a.den*b.num;}
  friend bool operator > (const frac &a, const frac &b) {return a.num*b.den > a.den*b.num;}
  friend bool operator < (const frac &a, const frac &b) {return a.num*b.den < a.den*b.num;}
  template<typename T> friend bool operator == (const frac &a, const T b) {b *= a.den; return a.num == b;}
  template<typename T> friend bool operator != (const frac &a, const T b) {b *= a.den; return a.num != b;}
  template<typename T> friend bool operator >= (const frac &a, const T b) {b *= a.den; return a.num >= b;}
  template<typename T> friend bool operator <= (const frac &a, const T b) {b *= a.den; return a.num <= b;}
  template<typename T> friend bool operator > (const frac &a, const T b) {b *= a.den; return a.num > b;}
  template<typename T> friend bool operator < (const frac &a, const T b) {b *= a.den; return a.num < b;}
  
  void change(frac f) {num = f.num; den = f.den;}
  frac inv() {return frac(den, num);}
  static frac add(frac a, const frac &b) {
    int n = a.num, d = a.den;
    a.num = n*b.den+d*b.num;
    a.den = d*b.den;
    a.simplify();
    return a;
  }
  static frac mult(frac a, const frac &b) {
    int other = b.den; swap(a.den, other);
    a.simplify();
    a.num *= b.num;
    a.den *= other;
    return a;
  }
  
  frac operator- () const {return frac(-num, den, false);}
  frac operator+ () const {return frac(num, den, false);}
  frac& operator += (const frac &f) {change(add(*this, f)); return *this;}
  frac& operator -= (const frac &f) {change(add(*this, -f)); return *this;}
  frac& operator *= (const frac &f) {change(mult(*this, f)); return *this;}
  frac& operator /= (const frac &f) {frac a = f; a = a.inv(); change(mult(*this, a)); return *this;}
  
  friend frac operator + (const frac& a, const frac& b) { return frac(a) += b; }
  friend frac operator - (const frac& a, const frac& b) { return frac(a) -= b; }
  friend frac operator * (const frac& a, const frac& b) { return frac(a) *= b; }
  friend frac operator / (const frac& a, const frac& b) { return frac(a) /= b; }
};
