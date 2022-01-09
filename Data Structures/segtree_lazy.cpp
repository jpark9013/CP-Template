// TODO: support direct update function
template<class T> struct LSegTree {
	using ftype = function<T(T, T)>;
	public:
		LSegTree() {}
		LSegTree(vector<T> v, const T &U, const ftype &F) : N(sz(v)), U(U), F(F), t(4*(N+1),U), lz(4*(N+1),0) {
			v.insert(v.begin(), T());
			build(v);
		} 
		void add(int L, int R, const T &v) {upd(++L,++R,v,1,0,N); }
		T get(int L, int R) {return qry(++L,++R,1,0,N); }
	private:
		int N; vector<T> t, lz;
		T U;
		ftype F;
		void pull(int i) { t[i] = F(t[i*2],t[i*2+1]); }
		void push(int i, int l, int r) {
			t[i]+=lz[i];
			if(l!=r) lz[i*2]+=lz[i], lz[i*2+1]+=lz[i];
			lz[i]=0; }
		void build(const vector<T> &v) { build(v,1,0,N); }
		void build(const vector<T> &v, int i, int l, int r) {
			if(l==r) { t[i]=v[l]; return; } int m=(l+r)/2;
			build(v,i*2,l,m); build(v,i*2+1,m+1,r); pull(i);
		}
		void upd(int L, int R, const T &v, int i, int l, int r) {
			push(i,l,r); if(R<l || L>r) return;
			if(L<=l && R>=r) { lz[i]+=v; push(i,l,r); return; }
			int m=(l+r)/2; upd(L,R,v,i*2,l,m);
			upd(L,R,v,i*2+1,m+1,r); pull(i);
		}
		T qry(int L, int R, int i, int l, int r) {
			push(i,l,r); if(R<l || L>r) return U;
			if(L<=l && R>=r) return t[i]; int m=(l+r)/2;
			return F(qry(L,R,i*2,l,m), qry(L,R,i*2+1,m+1,r));
		}
};
// usage: (0 indexed)
 
// LSegTree<int> st(vec, val, func)
// vec is the vector to pass in 
// val is the min (or whatever equivalent) value to pass in
// func is the communicative relation between the two numbers
 
// st.add(a, b, c) 
// updates indexes a through b, adding the value c
// IMPORTANT: 
// if you're doing single point update with respect to a vector, always remember
// to update the vector as well 
 
// st.get(a, b)
// gets the sum (or whatever equivalent) from indexes a to b
