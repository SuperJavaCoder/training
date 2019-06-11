/*
This solution doesn't score full 25, it fails on two test giving TLE.
Observation: suppose we have a ring, each node outside the ring will reach only one node of the ring (it can't reach two without passing the first).
Solution: For each lar(u), find a ring that contains it, if there is none, lar(u) = MAX(1+lar(v)) where v is node connected to u,
if there is a ring, for each node in the ring find gar(u) which is the longest path from u and returns to u without using the ring and without repeating the edges.
After that the answer becomes MAX(lar(v)+MAX_PATH_IN_THE_RING_WITHOUT_V) which can be done using prefix sum.

I'm not sure about the complexity but it should be close to O(N^2)
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
#define  N  (10005)

//global

unordered_set<short> adj[N];
vector<short> ring;
bitset<N> vis;
short curreturn;
short one = 1;

bool far(short u,short p){
	ring.push_back(u);
	vis[u] = true;
	for(short v:adj[u]){
		if(v == curreturn && p != curreturn) return true;
		if(v != p && !vis[v]){
			if(far(v,u)) return true; 
		}
	}
	vis[u] = false;
	ring.pop_back();
	return false;
}

short gar(short u){
	vis.reset();
	ring.clear();
	curreturn = u;
	far(u,u);
	if(sz(ring) == 0) return 0;
	vector<short> curing = ring;
	short ans = sz(curing);
	short len = sz(curing);
	for(short i = 0; i < len; i++){
		short bef = curing[(i?i-1:sz(curing)-1)];
		short cur = curing[i];
		short nex = curing[(i==sz(curing)-1?0:i+1)];
		adj[cur].erase(bef);
		adj[cur].erase(nex);
		ans += gar(cur);
		adj[cur].insert(bef);
		adj[cur].insert(nex);
	}
	return ans;
}

short lar(short u){
	vis.reset();
	ring.clear();
	curreturn = u;
	far(u,u);
	if(sz(ring) == 0){
		short ans = 0;
		vector<short> curnei;
		for(short v:adj[u]){
			curnei.push_back(v);
		}
		for(short v:curnei){
			adj[v].erase(u);
			ans = max(ans,short(lar(v)+1));
			adj[v].insert(u);
		}
		return ans;
	}
	vector<short> curing = ring;
	short len = sz(curing);
	vector<short> grs;
	short bef,cur,nex;
	for(int i = 0; i < len; i++){
		bef = curing[(i?i-1:sz(curing)-1)];
		cur = curing[i];
		nex = curing[(i==sz(curing)-1?0:i+1)];
		adj[cur].erase(bef);
		adj[cur].erase(nex);
		short val = gar(cur);
		if(i) grs.push_back(grs.back()+val);
		else grs.push_back(val);
		adj[cur].insert(bef);
		adj[cur].insert(nex);
	}
	short ev = grs.back()-grs[0];
	short ans = 0;
	for(short i = 0; i < len; i++){
		bef = curing[(i?i-1:sz(curing)-1)];
		cur = curing[i];
		nex = curing[(i==sz(curing)-1?0:i+1)];
		adj[cur].erase(bef);
		adj[cur].erase(nex);
		short dist;
		if(i == 0) dist = ev+sz(curing);
		else dist = max(grs[i-1]+i,grs.back()-grs[i]+grs[0]+(sz(curing)-i));
		ans = max(ans,short(lar(cur)+dist));
		adj[cur].insert(bef);
		adj[cur].insert(nex);
	}
	return ans;
}

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	rep(i,0,m){
		short u,v;
		scanf("%d %d",&u,&v);
		adj[u].insert(v);
		adj[v].insert(u);
	}
	ring.reserve(n);
	printf("%d", (int) lar(1));
	return 0;
}