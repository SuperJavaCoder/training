/*
http://agc006.contest.atcoder.jp/data/agc/006/editorial.pdf
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
vector<ll> base;

vector<ll> mul(vector<ll> a,vector<ll> b){
	vector<ll> res(sz(a));
	rep(i,0,sz(a)){
		res[i] = b[a[i]-1];
	}
	return res;
}

vector<ll> binpow(ll b) {
	vector<ll> res = base;
	while (b > 0) {
		if (b & 1)
			res = mul(res,base);
		base = mul(base,base);
		b >>= 1;
	}
	return res;
}
ll a[N];
ll d[N];
ll op[N];

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	ll n;
	cin >> n;
	rep(i,1,n+1){
		cin >> a[i];
	}
	vector<ll> num;
	rep(i,2,n+1){
		d[i] = a[i]-a[i-1];
		num.push_back(d[i]);
	}
	ll m,k;
	cin >> m >> k;
	rep(i,1,n){
		base.push_back(i);
	}
	rep(i,0,m){
		cin >> op[i];
		op[i] -= 2;
		swap(base[op[i]],base[op[i]+1]);
	}
	base = binpow(k-1);
	num = mul(base,num);
	ll cur = a[1];
	rep(i,0,n){
		cout << cur << endl;
		if(i != n-1) cur += num[i];
	}
	return 0;
}