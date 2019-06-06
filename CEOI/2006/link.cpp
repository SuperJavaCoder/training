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
#define  N  (500005)
#define MOD (1000000000ll + 7ll)
#define OO (1050000000)
#define OOL (1100000000000000000)

//global



bool incycle[N];
struct cmp {
	bool operator()(const pair<int,int>& l,const pair<int,int>& r) const{
		if(l.first == r.first)
			return l.second < r.second;
		return l.first < r.first;
	}
};

int go[N];
set<int> par[N];
bool vi[N];
set<pair<int,int>,cmp> s;

void dfsdelete(int u,int dep){
	s.erase({sz(par[u]),u});
	if(!vi[u] && !vi[go[u]] && !incycle[go[u]]){
		int v = go[u];
		s.erase({sz(par[v]),v});
		par[v].erase(u);
		s.insert({sz(par[v]),v});
	}
	vi[u] = true;
	if(dep == 0) return;
	dfsdelete(go[u],dep-1);
}
int vis[N];

vector<vector<int>> cycles;

void mark(int u){
	incycle[u] = true;
	cycles.back().push_back(u);
	if(!incycle[go[u]]) mark(go[u]);
}

void dfs(int u){
	if(vis[u] == 2) return;
	vis[u] = 1;
	if(vis[go[u]] == 0) dfs(go[u]);
	else if(vis[go[u]] == 1){
		cycles.push_back({});
		mark(u);
	}
	vis[u] = 2;
}

int nex[N];
int dp[N][22];
int solve(string s,int len){
	int n = sz(s);
	int o = 0;
	rep(i,0,sz(s)){
		nex[i] = 0;
		o += (s[i]=='0');
	}
	if(o == sz(s)) return 0;
	int first = 0;
	while(s[first] == '0') first++;
	rep(i,0,first+1){
		nex[i] = first;
	}
	if(s[n-1] == '1') nex[n-1] = n-1;
	else nex[n-1] = first+n;
	for (int i = n-2; i > first; --i){
		if(s[i] == '1') nex[i] = i;
		else nex[i] = nex[i+1];
	}
	for (int i = 0; i < n; ++i){
		if(i+len >= n) dp[i][0] = (i+len)/n*n+nex[(i+len)%n];
		else dp[i][0] = nex[i+len];
	}
	for (int k = 1;k < 22; ++k){
		for (int i = 0; i < n; ++i){
			dp[i][k] = dp[i][k-1]/n*n+dp[(dp[i][k-1])%n][k-1];
		}
	}
	int mi = n;
	for (int i = 0; i < n; ++i){
		int l = 0,r = n,best = n;
		while(l <= r){
			int mid = (l+r)/2;
			int pos = i;
			for (int j = 0; j < 22; ++j){
				if(mid&(1<<j)){
					pos = pos/n*n+dp[pos%n][j];
				}
			}
			if(pos-i >= n){
				best = mid;
				r = mid-1;
			}else{
				l = mid+1;
			}
		}
		mi = min(mi,best);
	}
	return mi;
}

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	int n,k;
	cin >> n >> k;
	rep(i,0,n){
		int u,v;
		cin >> u >> v;
		go[u] = v;
		par[v].insert(u);
	}
	rep(i,0,n){
		dfs(i+1);
	}
	for (int i = 0; i < n; ++i){
		if(!incycle[i+1]) s.insert({sz(par[i+1]),i+1});
	}
	int ans = 0;
	dfsdelete(1,k);
	if(sz(s)) while(s.begin()->first == 0){
		dfsdelete(s.begin()->second,k-1);
		ans++;
		if(!sz(s)) break;
	}
	for(auto a:cycles){
		string s = "";
		for(auto el:a){
			s += '0'+!vi[el];
		}
		ans += solve(s,k);
	}
	cout << ans << endl;
	return 0;
}
