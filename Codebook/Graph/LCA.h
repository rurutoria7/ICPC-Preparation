struct LCA {
	int N; V<vi> par, adj; vi depth;
	void init(int _N) {  N = _N; 
		// vertices indexed [0, N)
		int d = 1; while ((1<<d) < N) ++d;
		par.assign(d,vi(N)); 
		adj.rsz(N); depth.rsz(N);
	}
	void ae(int x, int y) { 
		adj[x].pb(y), adj[y].pb(x); 
	}
	void gen(int R = 0) { par[0][R] = R; dfs(R); }
	void dfs(int x = 0) {
		F0R(i,1,sz(par)) 
			par[i][x] = par[i-1][par[i-1][x]];
		for (auto y: adj[x]) 
			if (y != par[0][x]) 
				depth[y] = depth[par[0][y]=x]+1, 
				dfs(y);
	}
	int jmp(int x, int d) {
		F0R(i,0,sz(par)) 
			if ((d>>i)&1) x = par[i][x];
		return x;
	}
	int lca(int x, int y) {
		if (depth[x] < depth[y]) swap(x,y);
		x = jmp(x,depth[x]-depth[y]); 
		if (x == y) return x;
		for (int i=sz(par)-1; i>=0; i--) {
			int X = par[i][x], Y = par[i][y];
			if (X != Y) x = X, y = Y;
		}
		return par[0][x];
	}
	int dist(int x, int y) { // # edges on path
		return depth[x]+depth[y]-2*depth[lca(x,y)];
	}
};

