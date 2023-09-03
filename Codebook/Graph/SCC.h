struct SCC {
	int N, sccSz; V<vi> adj, radj;
	vi todo, comp; V<bool> vis;
	void init(int _N) { // vertex: [0,N)
		N = _N, adj.rsz(N), radj.rsz(N), 
		comp = vi(N,-1), vis.rsz(N), sccid = 0;
	}
	void ae(int x, int y) { 
		adj[x].pb(y), radj[y].pb(x); 
	}
	void dfs(int x) {
		vis[x] = 1; 
		for (auto y: adj[x]) if (!vis[y]) dfs(y);
		todo.pb(x);
	}
	void dfs2(int x, int v) {
		comp[x] = v; 
		for (auto y: radj[x]) if (comp[y] == -1) dfs2(y,v);
	}
	// assign all vertex a sccid, start from 0, 
	void gen() { 
		F0R(i,0,N) if (!vis[i]) dfs(i);
		reverse(all(todo)); 
		for (auto x: todo) if (comp[x] == -1)
			dfs2(x,sccSz++);
	}
};
