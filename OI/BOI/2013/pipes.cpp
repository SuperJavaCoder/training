/*
We can observe that the problems is a set of linear equations asking for solution, since N <= 1e5, we can't use gaussian elimination,
We also can observe that if M > N (the number of variables > the number of linear equations) we can't solve the problem, also M >= N-1
So we are left with two possible scenarios, when M=N-1 (the graph is a tree), and when M = N (the graph contains one circle and trees attached to the node of the circle).
We start by creating a set that contains node sorted by their current degree, as far as the first one has one node attached to it, we can find the value of that edge and 
delete the node and update the set. If we got some nodes left (the circle in the graph) we have two scenarios depending in the parity of the length of the circle,
if it's even there is no unique solution, if it's odd, there is one solution, we can get an edge value by solving the special linear equation, and then delete it, resulting a line,
which can be solved by the first step
 
O(NlogN)
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
set<pair<ll,ll>> s;
set<pair<ll,ll>> adj[N];
ll sum[N];
ll val[N];

vector<ll> res;

void dfs(ll u,ll p){
	res.push_back(u);
	for(auto v:adj[u]){
		if(v.first != p && v.first != res[0]){
			dfs(v.first,u);
			return;
		}
	}
}

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	ll n,m;
	cin >> n >> m;
	if(m > n) return cout << 0,0;
	rep(i,1,n+1){
		cin >> sum[i];
	}
	rep(i,0,m){
		ll u,v;
		cin >> u >> v;
		adj[u].insert({v,i});
		adj[v].insert({u,i});
	}
	rep(i,1,n+1){
		if(sz(adj[i])) s.insert({sz(adj[i]),i});
	}
	
	while(sz(s) && s.begin()->first == 1){
		ll u = s.begin()->second;
		s.erase(s.begin());
		ll v = adj[u].begin()->first;
		ll edgide = adj[u].begin()->second;
		s.erase({sz(adj[v]),v});
		adj[u].erase(adj[u].begin());
		adj[v].erase({u,edgide});
		val[edgide] = sum[u];
		sum[u] = 0;
		sum[v] -= val[edgide];
		if(sz(adj[v])) s.insert({sz(adj[v]),v});
	}
	if(sz(s) && s.begin()->first == 2){
		dfs(s.begin()->second,0);
		if(sz(res)%2 == 0) return cout << 0,0;
		ll ans = sum[res[0]];
		rep(i,1,sz(res)){
			if(i&1) ans += sum[res[i]];
			else ans -= sum[res[i]];
		}
		ans /= 2;
		ll u = res[0];
		s.erase({sz(adj[u]),u});
		ll v = res[1];
		ll edgide = (*adj[u].lower_bound({v,0})).second;
		s.erase({sz(adj[v]),v});
		adj[u].erase({v,edgide});
		adj[v].erase({u,edgide});
		val[edgide] = ans;
		sum[u] -= val[edgide];
		sum[v] -= val[edgide];
		if(sz(adj[v])) s.insert({sz(adj[v]),v});
	}
	while(sz(s) && s.begin()->first == 1){
		ll u = s.begin()->second;
		s.erase(s.begin());
		ll v = adj[u].begin()->first;
		ll edgide = adj[u].begin()->second;
		s.erase({sz(adj[v]),v});
		adj[u].erase(adj[u].begin());
		adj[v].erase({u,edgide});
		val[edgide] = sum[u];
		sum[u] = 0;
		sum[v] -= val[edgide];
		if(sz(adj[v])) s.insert({sz(adj[v]),v});
	}
	rep(i,0,m){
		cout << val[i]*2 << endl;
	}
	return 0;
}