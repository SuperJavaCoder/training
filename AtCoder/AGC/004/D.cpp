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
vector<pair<int,int>> s;
int n,k;
vector<int> adj[N];
int ans = 0;
int d[N];
int bef[N];
vector<int> st;
bool vis[N];
 
void dfs(int u,int cd){
	st.push_back(u);
	bef[u] = (sz(st) >= k?st[sz(st)-k]:1);
	d[u] = cd;
	for(int v:adj[u]){
		dfs(v,cd+1);
	}
	st.pop_back();
}
 
void dfsdelete(int u){
	if(vis[u]) return;
	vis[u] = true;
	for(int v:adj[u]){
		dfsdelete(v);
	}
}
 
int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	cin >> n >> k;
	rep(i,0,n){
		int u = i+1,v;
		cin >> v;
		swap(u,v);
		if(u == v) continue;
		if(v == 1){
			ans++;
			continue;
		}
		adj[u].push_back(v); 
	}
	dfs(1,0);
	rep(i,1,n+1){
		if(d[i] > k) s.push_back({-d[i],i});
	}
	sort(s.begin(), s.end());
	rep(i,0,sz(s)){
		if(!vis[s[i].second]){
			ans++;
			dfsdelete(bef[s[i].second]);
		}
	}
	cout << ans << endl;
	return 0;
}