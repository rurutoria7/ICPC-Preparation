/**
* Description: Calculates a valid assignment to boolean variables a, b, c,... 
* to a 2-SAT problem, so that an expression of the type 
* $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, 
* or reports that it is unsatisfiable.
* Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
* Usage;
	* TwoSAT ts; ts.init(5);
	* ts.either(1,2)   // (var 1 is true) or (var 2 is true)
	* ts.either(~0, 3) // (var 0 is false) or (var 3 is true)
	* auto ans = ts.solve() 
 */
#include "SCC.h"

struct TwoSAT {
	int N = 0; V<pii> edges;
	void init(int _N) { N = _N; }
	int addVar() { return N++; }
	void either(int x, int y) {
		x = max(2*x,-1-2*x), y = max(2*y,-1-2*y);
		edges.pb(mp(x,y)); }
	void implies(int x, int y) { either(~x,y); }
	void must(int x) { either(x,x); }
	void atMostOne(const vi& li) {
		if (sz(li) <= 1) return;
		int cur = ~li[0];
		FOR(i,2,sz(li)) {
			int next = addVar();
			either(cur,~li[i]); either(cur,next);
			either(~li[i],next); cur = ~next;
		}
		either(cur,~li[1]);
	}
	V<bool> solve() {
		SCC S; S.init(2*N);
		for (auto e: edges)
			S.addEdge(e.ff^1,e.ss),
			S.addEdge(e.ss^1,e.ff);
		// reverse topo order
		S.gen(); reverse(all(S.comps)); 
		for (int i = 0; i < 2*N; i += 2)
			if (S.comp[i] == S.comp[i^1]) 
				return {};
		vi tmp(2*N);
		for (auto i: S.comps) if (!tmp[i])
			tmp[i] = 1, tmp[S.comp[i^1]] = -1;
		V<bool> ans(N); 
		F0R(i,0,N) ans[i] = tmp[S.comp[2*i]] == 1;
		return ans;
	}
};
