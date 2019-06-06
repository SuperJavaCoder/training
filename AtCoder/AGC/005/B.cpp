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
#define MOD (1000000000ll + 7ll)
#define OO (1050000000)
#define OOL (1100000000000000000)

//global
pair<ll,ll> a[N];

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	ll n;
	cin >> n;
	rep(i,0,n){
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a,a+n);
	set<ll> gr;
	set<ll,greater<ll>> ls;
	ll ans = 0;
	rep(i,0,n){
		if(gr.lower_bound(a[i].second) == gr.end()){
			if(ls.lower_bound(a[i].second) == ls.end()){
				ans += a[i].first*(n-a[i].second)*(a[i].second+1);
			}else{
				ans += a[i].first*(n-a[i].second)*
				(a[i].second-*ls.lower_bound(a[i].second));
			}
		}else{
			if(ls.lower_bound(a[i].second) == ls.end()){
				ans += a[i].first*
				(*gr.lower_bound(a[i].second)-a[i].second)
				*(a[i].second+1);
			}else{
				ans += a[i].first*
				(*gr.lower_bound(a[i].second)-a[i].second)*
				(a[i].second-*ls.lower_bound(a[i].second));
			}
		}
		gr.insert(a[i].second);
		ls.insert(a[i].second);
	}
	cout << ans << endl;
	return 0;
}
