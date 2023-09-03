struct DSU {
	vi e; void init(int N) { e = vi(N,-1); }
	int get(int x) {
		return e[x] < 0 ? x : e[x] = get(e[x]);
	} 
	bool sameSet(int a, int b) {
		return get(a) == get(b);
	}
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y);
		if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};

template<class T> T
kruskal(int N, vector<pair<T,pii>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(N);
	// edges that unite are in MST
	foreach(a,ed)
		if (D.unite(a.ss.ff,a.ss.ss)) ans += a.ff;
	return ans;
}
