/*
Store dp[i][k] where i is the node number and k is the number of nodes chosen,
we construct dp[i][k] from its children and then maximize dp[i][1] regarding val[i],
Each merge is O(M^2) but this will happend rarely and only O(N/M) times, so the
complexity is O(NM)

*/
//fold
#ifndef KHALIL
#include <bits/stdc++.h>
#else
#include "header.h"
#endif
#define endl '\n'
#define mp make_pair
#define tostr(x) static_cast<ostringstream&>((ostringstream()<<dec<<x)).str()
#define rep(i,begin,end) for(auto i = begin;i < end;i++)
#define repr(i,begin,end) for(auto i = begin-1;i >= end;i--)
#define pb push_back
#define sz(a) ((int)(a).size())
#define fi first
#define se second
#define abs(a) ((a) < (0) ? (-1)*(a) : (a))
#define SQ(a) ((a)*(a))
#define eqd(a,b) (abs(a-b)<1e-9)
#define X real()
#define Y imag()
using namespace std;
typedef long long ll;
typedef long double ld;
template <typename t> t in(t q){cin >> q;return q;}
template <typename T> ostream& operator<<(ostream& os, const vector<T>& v){os << "[";for (int i = 0; i < sz(v); ++i) { os << v[i]; if (i != sz(v) - 1) os << ",";}os << "]";return os;}
template <typename T, typename S>ostream& operator<<(ostream& os, const map<T, S>& v){for (auto it : v)os << "(" << it.first << ":" << it.second << ")";return os;}
template <typename T, typename S>ostream& operator<<(ostream& os, const pair<T, S>& v){os << "(" << v.first << "," << v.second << ")";return os;}
const long double PI = acosl(-1);
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
inline int rand(int l,int r){return uniform_int_distribution<int>(l, r)(rng);}
inline ll rand(ll l,ll r){return uniform_int_distribution<ll>(l, r)(rng64);}
//endfold
#define  N  (200'005)
#define MOD (1'000'000'007ll)
#define OO (1'050'000'000)
#define OOL (1'100'000'000'000'000'000ll)

//global
int root;
int n,m;
vector<int> adj[N];
int val[N];
pair<int,int> d[N];

void dfs(int u,int de){
	d[u] = {de,u};
	for(int v:adj[u]){
		dfs(v,de+1);
	}
}

vector<int> best[N];

void process(int u){
	if(sz(adj[u]) == 0){
		best[u] = {0,val[u]};
		return;
	}
	vector<int> base = best[adj[u][0]];
	rep(i,1,sz(adj[u])){
		int v = adj[u][i];
		vector<int> cop = base;
		rep(j,0,sz(best[v])){
			rep(k,0,min(sz(cop),m-j+1)){
				if(j+k >= sz(base)){
					base.resize(j+k+1);
				}
				base[j+k] = max(base[j+k],cop[k]+best[v][j]);
			}
		}
	}
	best[u] = base;
	best[u][1] = max(best[u][1],val[u]);
}

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	cin >> n >> m;
	rep(i,0,n){
		int u,v = i+1;
		cin >> u >> val[v];
		if(u) adj[u].push_back(v);
		else root = v;	
	}
	dfs(root,0);
	sort(d+1,d+n+1);
	reverse(d+1,d+n+1);
	rep(i,1,n+1){
		process(d[i].second);
	}
	cout << best[root][m] << endl;
	return 0;
}