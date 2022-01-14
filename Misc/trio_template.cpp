template<typename A, typename B, typename C> struct Trio {
  A first; B second; C third;
  Trio(const A &a, const B &b, const C &c) : first(a), second(b), third(c) {}
  Trio() : first(A()), second(B()), third(C()) {}
  template<typename T> friend T& operator << (T &out, const Trio &trio) {
    out << "(" << trio.first << ", " << trio.second << ", " << trio.third << ")";
    return out;
  }
  template<typename T> friend T& operator >> (istream &in, T &trio) {return in >> trio.first >> trio.second >> trio.third;}
  friend bool operator == (const Trio &a, const Trio &b) {
    return a.first == b.first && a.second == b.second && a.third == b.third; 
  }
  friend bool operator != (const Trio &a, const Trio &b) {
    return !(a == b);
  }
  friend bool operator < (const Trio &a, const Trio &b) {
    if (a.third == b.third && a.second == b.second) return a.first < b.first;
    else if (a.third == b.third) return a.second < b.second;
    else return a.third < b.third; 
  }
  friend bool operator <= (const Trio &a, const Trio &b) {
    return a == b || a < b;
  }
  friend bool operator > (const Trio &a, const Trio &b) {
    return !(a <= b);
  }
  friend bool operator >= (const Trio &a, const Trio &b) {
    return !(a < b);
  }
};

template<typename A, typename B, typename C> Trio<A, B, C> mt(const A &a, const B &b, const C &c) {return Trio<A, B, C>(a, b, c);}

// using Tr = Trio<int, int, ld>;
