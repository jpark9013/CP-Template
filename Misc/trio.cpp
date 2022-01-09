struct Trio {
	int first, second, third;
	Trio(int a, int b, int c) {
		first = a;
		second = b;
		third = c;
	} 
	Trio() {first = 0, second = 0, third = 0;}
	template<typename T> friend T& operator << (T &out, const Trio &trio) {
		out << "(" << trio.first << ", " << trio.second << ", " << trio.third << ")";
		return out;
	}
	template<typename T> friend T& operator >> (T &in, Trio &trio) {return in >> trio.first >> trio.second >> trio.third;}
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

Trio mt(int a, int b, int c) {return Trio(a, b, c);}
