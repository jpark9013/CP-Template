template<typename T> 
class BinarySearch { 

	private:

	using ftype = function<bool(T)>;
	ftype f;
	
	void valid(T a, T b) {assert(b >= a);}

	public:
	
	BinarySearch() {}
	BinarySearch(const ftype& _f) : f(_f) {}
	
	T low(T low, T high) {
		valid(low, high);
		while (low < high) {
			T m = (low + high) / 2;
			f(m) ? high = m : low = m + 1;
		}
		return low;
	}
	
	T high(T low, T high) {
		valid(low, high);
		while (low < high) {
			T m = (low + high + 1) / 2;
			f(m) ? low = m : high = m - 1;
		}
		return low;
	}
};
