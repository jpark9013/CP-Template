template<isfloat(D)> struct Double {
	
	private:
	
	D v;
	constexpr static D eps = 1e-9;
	
	public:
	
	Double(const D &x): v(x) {}
	Double(): v(0) {}
	operator int32_t() const {return v;}
	operator int64_t() const {return v;}
	operator uint64_t() const {return v;}
	template<typename U> friend U& operator << (U &out, const Double &d) {return out << d.v;}
	template<typename U> friend U& operator >> (U &in, Double &d) {return in >> d.v;}
	
	friend bool operator == (const Double &a, const Double &b) {return abs(a.v-b.v) <= Double::eps;}
	friend bool operator != (const Double &a, const Double &b) {return !(a == b);}
	friend bool operator <= (const Double &a, const Double &b) {return a.v <= b.v;}
	friend bool operator >= (const Double& a, const Double& b) { return a.v >= b.v; }
  friend bool operator > (const Double& a, const Double& b) { return a.v > b.v; }
  friend bool operator < (const Double& a, const Double& b) { return a.v < b.v; }
  template<typename T> friend bool operator == (const Double& a, const T& b) {return a.v == b;}
  template<typename T> friend bool operator != (const Double& a, const T& b) {return a.v != b;}
  template<typename T> friend bool operator >= (const Double& a, const T& b) {return a.v >= b;}
  template<typename T> friend bool operator <= (const Double& a, const T& b) {return a.v <= b;}
  template<typename T> friend bool operator > (const Double& a, const T& b) {return a.v > b;}
  template<typename T> friend bool operator < (const Double& a, const T& b) {return a.v < b;}
  
  Double operator - () const {return Double(-v);}
  Double operator + () const {return Double(*this);}
  Double& operator ++ () {v++;}
  Double& operator -- () {v--;}
  Double& operator += (const Double &d) {
  	v += d.v;
  	return *this;
  }
  Double& operator -= (const Double &d) {
  	v -= d.v;
  	return *this;
  }
  Double& operator *= (const Double &d) {
  	v *= d.v;
  	return *this;
  }
  Double& operator /= (const Double &d) {
  	v /= d.v;
  	return *this;
  }
  
  friend Double operator ++ (Double &d, int32_t) { Double a = d; a++; return a; }
  friend Double operator -- (Double &d, int32_t) { Double a = d; a--; return a; }
  friend Double operator + (const Double &a, const Double &b) { return Double(a) += b;}
  friend Double operator - (const Double &a, const Double &b) { return Double(a) -= b;}
  friend Double operator * (const Double &a, const Double &b) { return Double(a) *= b;}
  friend Double operator / (const Double &a, const Double &b) { return Double(a) /= b;}
};

#define double Double<double>
#define ld Double<ld>
