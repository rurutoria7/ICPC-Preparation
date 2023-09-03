#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define V vector
#define sz(a) ((int)a.size())
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define pb push_back
#define rsz resize
#define mp make_pair
#define mt make_tuple
#define ff first
#define ss second

#define FOR(i,j,k) for (int i=(j); i<=(k); i++)
#define F0R(i,j,k) for (int i=(j); i<(k); i++)
#define REP(i) FOR(_,1,i)
#define foreach(a,x) for (auto& a: x)


template<class T> bool cmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0; } // set a = min(a,b)
template<class T> bool cmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0; } // set a = max(a,b)

ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); }
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); }

#define roadroller ios::sync_with_stdio(0), cin.tie(0);
#define de(x) cerr << #x << '=' << x << ", "
#define dd cerr << '\n';
