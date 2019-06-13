/*
http://agc007.contest.atcoder.jp/data/agc/007/editorial.pdf
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
ll x[N];
ll dp[N];
 
int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	ll n,e,t;
	cin >> n >> e >> t;
	rep(i,0,n){
		cin >> x[i];
	}
	dp[n] = 0;
	x[n] = e;
	queue<pair<ll,ll>> q;
	ll mi = OOL;
	for (int i = n-1; i >= 0; --i){
		ll k = lower_bound(x+i+1,x+n,x[i]+(t+1)/2)-x;
		if(sz(q)) while(q.front().first >= k){
			mi = min(mi,q.front().second);
			q.pop();
			if(q.empty()) break;
		}
		ll ans = mi-3*x[i];
		k--;
		ans = min(ans,t+x[k+1]-x[i]+dp[k+1]);
		dp[i] = ans;
		q.push({i,2*x[i]+x[i+1]+dp[i+1]});
	}
	cout << dp[0]+x[0] << endl;
	return 0;
}