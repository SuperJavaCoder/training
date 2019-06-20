/*
for each number from m to 1, we can observe that we are connecting all multiples of that number. If we read queries beforehand and inserted them in a dsu, we can merge them in logarithmic
time, and there will be no more than n-1 merges, and with smaller to larger merge, the solution will become O(N*log(N)) 
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
template <typename T> ostream& operator<<(ostream& os, const set<T>& v){os << "[";for (auto i = v.begin(); i != v.end();) { os << *i; i++; if (i != v.end()) os << ",";}os << "]";return os;}
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
int ans[N];

struct component{
	int par;
	int sz;
	set<int> numbers;
	map<int,vector<int>> requests;
};

component dsu[N];

int home(int u){
	if(dsu[u].par == u) return u;
	dsu[u].par = home(dsu[u].par);
	return dsu[u].par;
}

void merge(int u,int v,int c){
	u = home(u); v = home(v);
	if(u == v) return;
	if(sz(dsu[u].requests) <= sz(dsu[v].numbers)){
		vector<int> tbd;
		for(auto el:dsu[u].requests){
			if(dsu[v].numbers.count(el.first)){
				tbd.push_back(el.first);
				for(int id:el.second){
					ans[id] = c;
				}
			}
		}
		for(int el:tbd) dsu[u].requests.erase(el);
	}else{
		vector<int> tbd;
		for(int tar:dsu[v].numbers){
			if(dsu[u].requests.count(tar)){
				tbd.push_back(tar);
				for(int id:dsu[u].requests[tar]){
					ans[id] = c;
				}
			}
		}
		for(int el:tbd) dsu[u].requests.erase(el);
	}
	if(sz(dsu[v].requests) <= sz(dsu[u].numbers)){
		vector<int> tbd;
		for(auto el:dsu[v].requests){
			if(dsu[u].numbers.count(el.first)){
				tbd.push_back(el.first);
				for(int id:el.second){
					ans[id] = c;
				}
			}
		}
		for(int el:tbd) dsu[v].requests.erase(el);
	}else{
		vector<int> tbd;
		for(int tar:dsu[u].numbers){
			if(dsu[v].requests.count(tar)){
				tbd.push_back(tar);
				for(int id:dsu[v].requests[tar]){
					ans[id] = c;
				}
			}
		}
		for(int el:tbd) dsu[v].requests.erase(el);
	}
	if(dsu[u].sz < dsu[v].sz) swap(u,v);
	for(int el:dsu[v].numbers) dsu[u].numbers.insert(el);
	for(auto el:dsu[v].requests)
		dsu[u].requests[el.first].insert(
			dsu[u].requests[el.first].end(),
			el.second.begin(), el.second.end()
		);
	dsu[u].sz += dsu[v].sz;
	dsu[v].par = u;
}

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	int n,m,q;
	cin >> n >> m >> q;
	for (int i = 0; i < n; ++i){
		dsu[i+1] = {i+1,1,{i+1},{}};
	}
	rep(i,0,q){
		int u,v;
		cin >> u >> v;
		if(u > v) swap(u,v);
		dsu[u].requests[v].push_back(i);
	}
	for (int i = m; i >= 1; --i){
		set<int> tm;
		for(int j = i; j <= n; j += i){
			tm.insert(home(j));
		}
		int fir = *tm.begin();
		for(int w:tm){
			if(w == fir) continue;
			merge(fir,w,m-i+1);
		}
	}
	rep(i,0,q){
		cout << ans[i] << endl;
	}
	return 0;
}