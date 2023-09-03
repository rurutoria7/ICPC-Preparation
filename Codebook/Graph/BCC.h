/**
* Remove any vertex in BCC doesn't disconnect it.
* To get block-cut tree, create a bipartite graph
* with the original vertices on the left and a vertex for each BCC on the right.
* Draw edge $u\leftrightarrow v$ if $u$ is contained within the BCC for $v$.
* Self-loops are not included in any BCC while BCCS of size 1 (edgeSets) represent bridges.
* Time: O(N+M)
*/
struct BCC {
	V<V<pii>> adj; V<pii> ed;
	V<vi> edgeSets, vertSets;
	int N, ti = 0; vi disc, stk;
	void init(int _N) {
		N = _N; disc.rsz(N), adj.rsz(N);
	}
	void ae(int x, int y) {
		adj[x].pb(mp(y,sz(ed))),
		adj[y].pb(mp(x,sz(ed))),
		ed.pb(mp(x,y));
	}
	// return lowest disc
	int dfs(int x, int p = -1) { 
		int low = disc[x] = ++ti;
		for (auto e: adj[x]) if (e.ss != p) {
			if (!disc[e.ff]) {
				stk.pb(e.ss);
				int LOW = dfs(e.ff,e.ss);
				cmin(low,LOW);
				// x is AP, get edges in bcc
				if (disc[x] <= LOW) {
					edgeSets.pb(vi());
					vi& tmp = edgeSets.back();
					for (int y = -1; y != e.ss; )
						tmp.pb(y = stk.back()),
						stk.pop_back();
				}
			} else if (disc[e.ff] < disc[x]){
				// back-edge
				cmin(low,disc[e.ff]),
				stk.pb(e.ss);
			}
		}
		return low;
	}
	void gen() {
		F0R(i,0,N) if (!disc[i]) dfs(i);
		V<bool> in(N);
		for (auto c: edgeSets) {
			vertSets.pb(vi());
			auto ad = [&](int x) {
				if (!in[x]) in[x] = 1,
					vertSets.back().pb(x);
			};
			for (auto e: c)
				ad(ed[e].ff), ad(ed[e].ss);
			for (auto e: c)
				in[ed[e].ff] = in[ed[e].ss] = 0;
		}
	}
};
