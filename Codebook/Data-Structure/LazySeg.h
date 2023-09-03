template<class T, int SZ> struct LazySeg { // SZ must be power of 2
	const T ID{}; T cmb(T a, T b) { return a+b; }
	T seg[2*SZ], lazy[2*SZ]; 
	LazySeg() { 
		F0R(i,0,2*SZ) seg[i] = lazy[i] = ID; 
	}
	/// modify values for current node
	void push(int ind, int L, int R) { 
		// dependent on operation
		seg[ind] += (R-L+1)*lazy[ind]; 
		if (L != R) F0R(i,0,2) lazy[2*ind+i] += lazy[ind]; /// prop to children
		lazy[ind] = 0; 
	}
	void pull(int ind){
		seg[ind]=cmb(seg[2*ind],seg[2*ind+1]);
	}
	void build() {
		for (int i=SZ; i>0; i--) pull(i);
	}
	void upd(int lo,int hi,T inc,int ind=1,int L=0, int R=SZ-1) {
		push(ind,L,R); 
		if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) { 
			lazy[ind] = inc; push(ind,L,R); return;
		}
		int M = (L+R)/2; 
		upd(lo,hi,inc,2*ind,L,M); 
		upd(lo,hi,inc,2*ind+1,M+1,R); 
		pull(ind);
	}
	T query(int lo, int hi, int ind=1, int L=0, int R=SZ-1) {
		push(ind,L,R);
		if (lo > R || L > hi) return ID;
		if (lo <= L && R <= hi) return seg[ind];
		int M = (L+R)/2; 
		return cmb(query(lo,hi,2*ind,L,M),
			query(lo,hi,2*ind+1,M+1,R));
	}
};
