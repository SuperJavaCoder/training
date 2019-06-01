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
#define  N  (200005)
#define MOD (1000000000l + 7l)
#define OO (1050000000)
#define OOL (1100000000000000000)
 
//global
int n,m;
vector<pair<int,int>> edges;
 
struct query{
	int i,a,b,z,l,r,best;
};
 
vector<query> v;
 
int p[N];
int s[N];
 
void setup(){
	rep(i,0,n+5){
		p[i] = i;
		s[i] = 1;
	}
}
 
int fin(int u){
	if(p[u] == u) return u;
	return p[u] = fin(p[u]);
}
 
void merge(int w,int e){
	w = fin(w);
	e = fin(e);
	if(s[e] > s[w]) swap(w,e);
	p[e] = w;
	s[w] += s[e];
}
 
bool same(int w,int e){
	return (fin(w) == fin(e));
}
 
void print(query we){
	cout << we.i << ": (" << we.a << "," << we.b << "," <<  we.z
	<< ") (" << we.l << "," << we.r << "," << we.best << ")\n";
}
 
void pass(){
	sort(v.begin(), v.end(),[](query w,query e){
		if(w.l <= w.r && e.l > e.r) return true;
		if(w.l > w.r && e.l > e.r) return false;
		if(w.l > w.r && e.l <= e.r) return false;
		return (w.l+w.r)/2 < (e.l+e.r)/2;
	});
//	rep(i,0,v.size()){
//		print(v[i]);
//	}
	int re = 0;
	setup();
	rep(i,0,edges.size()){
		if(!same(edges[i].first,edges[i].second)){
			merge(edges[i].first,edges[i].second);
		}
//		cout << "DSU: ";
//		rep(j,1,n+1){
//			cout << p[j] << " ";
//		}cout << endl;
		while((v[re].l+v[re].r)/2 == i+1){
			if(s[fin(v[re].a)]+s[fin(v[re].b)]
				-s[fin(v[re].b)]*(same(v[re].b,v[re].a)) >= v[re].z){
				v[re].best = i+1;
				v[re].r = i;
			}else{
				v[re].l = i+2;
			}
			re++;
		}
	}
}
 
int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	cin >> n >> m;
	rep(i,0,m){
		int u,v;
		cin >> u >> v;
		edges.push_back({u,v});
	}
	int q;
	cin >> q;
	rep(i,0,q){
		int a,b,z;
		cin >> a >> b >> z;
		v.push_back({i,a,b,z,1,m-1,m});
	}
	rep(i,0,25){
		pass();
	}
	sort(v.begin(), v.end(),[](query w,query e){
		return w.i < e.i;
	});
	rep(i,0,q){
		cout << v[i].best << endl;
	}
	return 0;
}