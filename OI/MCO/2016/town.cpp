/*
Let's find a node x, we have three cases, the path start on X, the path goes by x but doesn't start with it, the path doesn't go by x at all,
for each case we could handle it in O(sizeoftree), with the help of centroid decomposition, we can halve the tree to get O(N*log*log) solution

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
#define  N  (100'005)
#define MOD (1'000'000'007ll)
#define OO (1'050'000'000)
#define OOL (1'100'000'000'000'000'000ll)

//global
ll n,k;
set<ll> adj[N];
bool del[N];
ll sz[N];
ll ans = 0;


ll fillsize(ll u,ll p){
	if(del[u]) return 0;
	sz[u] = 1;
	for(ll w:adj[u]){
		if(w != p) sz[u] += fillsize(w,u);
	}
	return sz[u];
}

ll findcentroid(ll node,ll p,ll enough){
	ll mx = 0,id = node;
	for(ll v:adj[node]){
		if(v != p && !del[v]){
			if(sz[v] > mx){
				mx = sz[v]; id = v;
			}
		}
	}
	if(mx <= enough) return node;
	return findcentroid(id,node,enough);
}

map<ll,ll> m;
map<ll,ll> s;

void add(ll u,ll p,ll bef){
	ll childs = sz(adj[u])-(u!=p);
	if(u != p) m[childs+bef]++;
	for(ll v:adj[u]){
		if(v != p){
			if(!del[v]){
				add(v,u,bef+childs-1);
			}
		}
	}
}

void solve(ll node){
	fillsize(node,node);
	ll cen = findcentroid(node,node,sz[node]/2);
	s.clear();
	m.clear();
	ll childs = sz(adj[cen])-1;
	for(ll v:adj[cen]){
		if(!del[v]){
			add(v,cen,childs);
			if(m.count(k)) ans += m[k];
			for(auto p:m){
				if(s.count(k-(p.first-(sz(adj[cen])-1))+1)){
					ans += p.second*s[k-(p.first-(sz(adj[cen])-1))+1];
				}
			}
			for(auto p:m){
				s[p.first] += p.second;
			}
			m.clear();
		}
	}
	ans += (sz(adj[cen]) == k);
	del[cen] = true;
	for(ll v:adj[cen]){
		if(!del[v]) solve(v);
	}
}

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	cin >> n >> k;
	rep(i,0,n-1){
		ll u,v;
		cin >> u >> v;
		adj[u].insert(v);
		adj[v].insert(u);
	}
	solve(1); cout << ans << endl;
	return 0;
}