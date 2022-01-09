template<typename T> struct ucountset {
	umap<T, int> m;
	umultiset<T> ms;
	bool empty() {return m.empty();}
	bool size() {return ms.size();}
	void clear() {m.clear(); ms.clear();}
	void emplace(const T &x) {m[x]++; ms.emplace(x);}
	void erase_all(const T &x) {m.erase(x); ms.erase(x);}
	void erase(const T &x) {if (m.count(x)) {m[x]--; if (m[x] == 0) m.erase(x); ms.erase(ms.find(x));}}
	int count(const T &x) {if (!m.count(x)) return 0; return m[x];}
	template<typename T> friend T& operator << (T &out, const ucountset &cs) {return out << cs.ms;}
	auto begin() {return ms.begin();}s
	auto end() {return ms.end();}
};
