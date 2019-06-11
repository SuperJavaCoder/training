/*
Observation: suppose we have a ring, each node outside the ring will reach only one node of the ring (it can't reach two without passing the first).
Solution: For each lar(u), find a ring that contains it, if there is none, lar(u) = MAX(1+lar(v)) where v is node connected to u,
if there is a ring, for each node in the ring find gar(u) which is the longest path from u and returns to u without using the ring and without repeating the edges.
After that the answer becomes MAX(lar(v)+MAX_PATH_IN_THE_RING_WITHOUT_V) which can be done using prefix sum. The solution makes things faster by re-allocating
rings and deleting bridges beforehand, which makes the complexity as close as (NlogN) but with a huge constant factor.
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
#define UNVISITED (-1)
//global

struct custom_hash {
	size_t operator()(const pair<int,int> &x) const {
		return hash<int>()(x.first)^hash<int>()(x.second);
	}
};

unordered_set<int> adj[N];
unordered_set<pair<int,int>,custom_hash> nadj[N];
vector<short> dfs_num(N,UNVISITED);
vector<short> dfs_low(N,0);
vector<short> dfs_parent(N,0);
vector<int> orig[N];
int counter = 0;
vector<int> ring;
bitset<N> vis;
int curreturn;
int one = 1;
int par[N];
vector<pair<int,int>> tbe;

void bridges(int u){
	dfs_low[u] = dfs_num[u] = counter++;
	for(int v:adj[u]){
		if(dfs_num[v] == UNVISITED){
			dfs_parent[v] = u;
			bridges(v);
			if(dfs_low[v] > dfs_num[u]){
				tbe.emplace_back(u,v);
				tbe.emplace_back(v,u);
			}
			dfs_low[u] = min(dfs_low[u],dfs_low[v]);
		}else if(v != dfs_parent[u]){
			dfs_low[u] = min(dfs_low[u],dfs_num[v]);
		}
	}
}

bool fil(int u,int p){
	ring.push_back(u);
	vis[u] = true;
	for(int v:adj[u]){
		if(v == curreturn && p != curreturn) return true;
		if(v != p && !vis[v]){
			if(fil(v,u)) return true; 
		}
	}
	vis[u] = false;
	ring.pop_back();
	return false;
}
int chewawa;

bool far(int u,int p,int col){
	ring.push_back(u);
	vis[u] = true;
	for(auto v:nadj[u]){
		if(v.second == -1) continue;
		if(v.first == curreturn && p != curreturn){
			chewawa = col;
			return true;
		}
		if(v.first != p && !vis[v.first]){
			if(col && v.second != col) continue;
			if(far(v.first,u,v.second)) return true; 
		}
	}
	vis[u] = false;
	ring.pop_back();
	return false;
}

int gar(int u){
	vis.reset();
	ring.clear();
	curreturn = u;
	far(u,u,0);
	if(sz(ring) == 0) return 0;
	vector<int> curing = ring;
	int ans = sz(curing);
	int len = sz(curing);
	int fr = chewawa;
	for(int i = 0; i < len; i++){
		int bef = curing[(i?i-1:sz(curing)-1)];
		int cur = curing[i];
		int nex = curing[(i==sz(curing)-1?0:i+1)];
		assert(nadj[cur].count({bef,fr}));
		assert(nadj[cur].count({nex,fr}));
		nadj[cur].erase({bef,fr});
		nadj[cur].erase({nex,fr});
		ans += gar(cur);
		nadj[cur].insert({bef,fr});
		nadj[cur].insert({nex,fr});
	}
	return ans;
}

int lar(int u){
	vis.reset();
	ring.clear();
	curreturn = u;
	far(u,u,0);
	if(sz(ring) == 0){
		int ans = 0;
		vector<int> curnei;
		for(auto v:nadj[u]){
			curnei.push_back(v.first);
		}
		for(auto v:curnei){
			assert(nadj[v].count({u,-1}));
			assert(nadj[u].count({v,-1}));
			nadj[v].erase({u,-1});
			nadj[u].erase({v,-1});
			ans = max(ans,lar(v)+1);
			nadj[v].insert({u,-1});
			nadj[u].insert({v,-1});
		}
		return ans;
	}
	int fr = chewawa;
	vector<int> curing = ring;
	int len = sz(curing);
	vector<int> grs;
	int bef,cur,nex;
	for(int i = 0; i < len; i++){
		bef = curing[(i?i-1:sz(curing)-1)];
		cur = curing[i];
		nex = curing[(i==sz(curing)-1?0:i+1)];
		assert(nadj[cur].count({nex,fr}));
		assert(nadj[cur].count({bef,fr}));
		nadj[cur].erase({bef,fr});
		nadj[cur].erase({nex,fr});
		int val = gar(cur);
		if(i) grs.push_back(grs.back()+val);
		else grs.push_back(val);
		nadj[cur].insert({bef,fr});
		nadj[cur].insert({nex,fr});
	}
	int ev = grs.back()-grs[0];
	int ans = 0;
	for(int i = 0; i < len; i++){
		bef = curing[(i?i-1:sz(curing)-1)];
		cur = curing[i];
		nex = curing[(i==sz(curing)-1?0:i+1)];
		assert(nadj[cur].count({nex,fr}));
		assert(nadj[cur].count({bef,fr}));
		nadj[cur].erase({bef,fr});
		nadj[cur].erase({nex,fr});
		int dist;
		if(i == 0) dist = ev+sz(curing);
		else dist = max(grs[i-1]+i,grs.back()-grs[i]+grs[0]+(sz(curing)-i));
		ans = max(ans,lar(cur)+dist);
		nadj[cur].insert({bef,fr});
		nadj[cur].insert({nex,fr});
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n,m;
	cin >> n >> m;
	rep(i,0,m){
		int u,v;
		cin >> u >> v;
		adj[u].insert(v);
		adj[v].insert(u);
		orig[u].push_back(v);
		orig[v].push_back(u);
	}
	for(int i = 1; i <= n; i++){
		if(dfs_num[i] == UNVISITED){
			bridges(i);
		}
	}
	for(auto edge:tbe){
		adj[edge.first].erase(edge.second);
	}
	int col = 0;
	vector<pair<pair<int,int>,int>> ew;
	for(int k = n; k >= 1; k--){
		int i = k;
		curreturn = i;
		while(true){
			vis.reset();
			if(sz(adj[i]) == 0) break;
			int target = *adj[i].begin();
			adj[i].erase(target);
			queue<pair<int,int>> q;
			q.push({i,0});
			vis[i] = true;
			int an = -1;
			while(!q.empty() && an == -1){
				auto u = q.front(); q.pop();
				for(int v:adj[u.first]){
					if(v == i && u.second > 1 && u.first == target){
						an = u.first;
						break;
					}
					if(!vis[v]){
						q.push({v,u.second+1});
						vis[v] = true;
						par[v] = u.first;
					}
				}
			}
			if(an == -1) assert(false);
			while(an != i){
				ring.push_back(an);
				an = par[an];
			}
			ring.push_back(i);
			col++;
			int len = sz(ring);
			for(int j = 0; j < len-1; j++){
				vis[j] = false;
				adj[ring[j]].erase(ring[j+1]);
				adj[ring[j+1]].erase(ring[j]);
				ew.push_back({{ring[j],ring[j+1]},col});
				ew.push_back({{ring[j+1],ring[j]},col});
			}
			vis[len-1] = false;
			adj[ring[0]].erase(ring[len-1]);
			adj[ring[len-1]].erase(ring[0]);
			ew.push_back({{ring[0],ring[len-1]},col});
			ew.push_back({{ring[len-1],ring[0]},col});
			ring.clear();
		}
	}
	sort(ew.begin(), ew.end());
	for(int u = 1; u <= n; u++){
		for(int v:orig[u]){
			auto fir = lower_bound(ew.begin(), ew.end(), mp(mp(u,v),0));
			if(fir == ew.end()){
				nadj[u].emplace(v,-1);
			}else{
				auto sec = *fir;
				if(sec.first.first != u || sec.first.second != v)
					nadj[u].emplace(v,-1);
				else
					nadj[u].emplace(v,sec.second);
			}
		}
	}
	ring.reserve(n);
	cout << lar(1);
	return 0;
}