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
#define MOD (1000000007ll)
#define OO (1050000000)

//global
int MAX = 1000000000;

struct segment{
	int l,r;
	int bef,aft;
};
ostream& operator<<(ostream& os, const segment& v){
	os << "{(" << v.l << "," << v.r << "),(" << v.bef+1 << "," << v.aft+1 << ")}\n";
	return os;
}

int ans[N];

vector<segment> a = {
	{0,0,0,1},
	{1,MAX,0,2},
	{MAX+1,MAX+1,1,2}
};
set<pair<int,int>> s = {{1,1}};

void slpit(int i,int j){
	a.push_back({j,a[i].r,i,a[i].aft});
	a[i].r = j-1;
	a[i].aft = sz(a)-1;
	a[a[a[i].aft].aft] .bef = sz(a)-1;
	s.insert({j,sz(a)-1});
}

void merge(int i,int j){
	a[i].aft = j;
	a[j].bef = i;
}

void insert(int i,int j){
	int f = i,s = j,t = a[i].aft;
	a[f].aft = s;
	a[s].aft = t;
	a[s].bef = i;
	a[t].bef = s;
}

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	int n;
	cin >> n;
	rep(i,0,n){
		int a,b;
		cin >> a >> b;
		int idofcont = (--s.upper_bound({a,OO}))->second;
		int l = ::a[idofcont].l,r = ::a[idofcont].r;
		if(l != r){
			if(a == l){
				slpit(idofcont,a+1);
				merge(::a[idofcont].bef,::a[idofcont].aft);
			}else if(a == r){
				slpit(idofcont,r);
				idofcont = ::a[idofcont].aft;
				merge(::a[idofcont].bef,::a[idofcont].aft);
			}else{
				slpit(idofcont,a);
				idofcont = ::a[idofcont].aft;
				slpit(idofcont,a+1);
				merge(::a[idofcont].bef,::a[idofcont].aft);
			}
		}else{
			merge(::a[idofcont].bef,::a[idofcont].aft);
		}
		int idoftarget = (--s.upper_bound({b,OO}))->second;
		int lb = ::a[idoftarget].l,rb = ::a[idoftarget].r;
		if(lb != rb){
			if(b == lb){
				insert(::a[idoftarget].bef,idofcont);
			}else{
				slpit(idoftarget,b);
				insert(idoftarget,idofcont);
			}
		}else{
			insert(::a[idoftarget].bef,idofcont);
		}
	}
	vector<pair<int,int>> res;
	int cur = a[0].aft;
	while(a[cur].r != MAX+1){
		res.push_back({a[cur].l,a[cur].r});
		cur = a[cur].aft;
	}
	vector<pair<int,int>> pos;
	vector<pair<int,int>> num;
	int q;
	cin >> q;
	rep(i,0,q){
		string x;
		cin >> x;
		int e;
		cin >> e;
		if(x == "L"){
			pos.push_back({e,i});
		}else{
			num.push_back({e,i});
		}
	}
	sort(pos.begin(), pos.end());
	sort(num.begin(), num.end());
	cur = 1;
	int qwe = 0;
	rep(i,0,sz(res)){
		if(qwe < sz(pos)) while(pos[qwe].first <= cur+res[i].second-res[i].first){
			ans[pos[qwe].second] = res[i].first+(pos[qwe].first-cur);
			qwe++;
			if(qwe >= sz(pos)) break;
		}
		cur += res[i].second-res[i].first+1;
	}
	cur = 1;
	rep(i,0,sz(res)){
		int l = res[i].first,r = res[i].second;
		int f = lower_bound(num.begin(), num.end(),mp(l,0))-num.begin();
		int s = upper_bound(num.begin(), num.end(),mp(r,OO))-num.begin()-1;
		for(int j = f; j <= s; j++){
			ans[num[j].second] = cur+num[j].first-l;
		}
		cur += res[i].second-res[i].first+1;
	}
	rep(i,0,q){
		cout << ans[i] << endl;
	}
	return 0;
}