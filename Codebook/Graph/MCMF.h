/**
Minimum-cost maximum flow, assumes no negative cycles. 
* It is possible to choose negative edge costs such that the first 
* run of Dijkstra is slow, but this hasn't been an issue in the past. 
* Edge weights $\ge 0$ for every subsequent run. To get flow through 
* original edges, assign ID's during \texttt{ae}.
* Time: Ignoring first run of Dijkstra, $O(FM\log M)$ 
* if caps are integers and $F$ is max flow.
 */

struct MCMF {
	// flow type, cost type
	using F = ll; using C = ll; 
	struct Edge { int to; F flo, cap; C cost; };
	int N; V<C> p, dist; vi pre; 
	V<Edge> eds; V<vi> adj;
	void init(int _N) { N = _N;
		p.rsz(N), dist.rsz(N), 
		pre.rsz(N), adj.rsz(N);
	}
	void ae(int u, int v, F cap, C cost) { 
		assert(cap >= 0);
		adj[u].pb(sz(eds)); 
		eds.pb({v,0,cap,cost});
		adj[v].pb(sz(eds)); 
		eds.pb({u,0,0,-cost});
	} // use asserts, don't try smth dumb
	bool path(int s, int t) { 
		// find lowest cost path to send flow through
		const C inf = numeric_limits<C>::max(); F0R(i,0,N) dist[i] = inf;
		using T = pair<C,int>; priority_queue<T,vector<T>,greater<T>> todo;
		todo.push({dist[s] = 0,s});
		while (sz(todo)) { // Dijkstra
			T x = todo.top(); todo.pop(); 
			if (x.ff > dist[x.ss]) continue;
			foreach(e,adj[x.ss]) { 
				const Edge& E = eds[e]; 
				// all weights should be non-negative
				if (E.flo < E.cap && cmin(dist[E.to],x.ff+E.cost+p[x.ss]-p[E.to]))
					pre[E.to] = e, 
					todo.push({dist[E.to],E.to});
			}
		} // if costs are doubles, add some EPS so you
		// don't traverse ~0-weight cycle repeatedly
		return dist[t] != inf; // return flow
	}
	pair<F,C> calc(int s, int t) { assert(s != t);
		F0R(_,0,N) F0R(e,0,sz(eds)) { 
			const Edge& E = eds[e]; 
			// Bellman-Ford
			if (E.cap) cmin(p[E.to],p[eds[e^1].to]+E.cost); 
		}
		F totFlow = 0; C totCost = 0;
		while (path(s,t)) {
			// p -> potentials for Dijkstra
			F0R(i,0,N) p[i] += dist[i]; 
			// don't matter for unreachable nodes
			F df = numeric_limits<F>::max();
			for (int x = t; x != s; x = eds[pre[x]^1].to) {
				const Edge& E = eds[pre[x]]; cmin(df,E.cap-E.flo); 
			}
			totFlow += df; 
			totCost += (p[t]-p[s])*df;
			for (int x = t; x != s; x = eds[pre[x]^1].to)
				eds[pre[x]].flo += df, 
				eds[pre[x]^1].flo -= df;
		} // get max flow you can send along path
		return {totFlow,totCost};
	}
};
