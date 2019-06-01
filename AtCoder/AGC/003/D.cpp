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
#define MOD (1000000000ll + 7ll)
#define OO (1050000000)
#define OOL (1100000000000000000)
 
//global
ll a[N];
map<ll,int> act;
map<ll,int> ful;
 
vector<int> s;
bitset<100005> prim;
 
void fill(){
	int sqr = 47;
	s.push_back(2);
	for (int i = 3; i <= 2200; i += 2){
		if(!prim[i]){
			if(i <= sqr)
				for (int j = i*i; j <= 2200; j += i)
					prim[j] = true;
			s.push_back(i);
		}
	}
}
 
ll sqr(ll x){
	ll l = 1,r = x;
	while(l <= r){
		ll mid = (l+r)/2;
		ll ans = mid*mid;
		if(ans < x) l = mid+1;
		if(ans > x) r = mid-1;
		if(ans == x) return mid;
	}
	return 0;
}
 
int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	fill();
	int n;
	cin >> n;	
	rep(i,0,n){
		cin >> a[i];
	}
	rep(i,0,n){
		vector<pair<int,int>> bs;
		for (int j = 0; j < sz(s) && s[j]*s[j] <= a[i]; ++j){
			int k = 0;
			while(a[i]%s[j] == 0){
				k++;
				a[i] /= s[j];
				if(k == 3) k = 0;
			}
			if(k) bs.push_back({s[j],k});
		}
		if(a[i] > 1){
			ll q = sqrtl(a[i]);
			if(q*q == a[i]) bs.push_back({q,2});
			else bs.push_back({a[i],1});
		}
		ll bsn = 1;
		ll rsn = 1;
		for(pair<int,int> w:bs){
			if(w.second == 1){
				bsn *= w.first;
				rsn *= w.first;
				rsn *= w.first;
			}
			if(w.second == 2){
				bsn *= w.first;
				bsn *= w.first;
				rsn *= w.first;
			}
		}
		if(bsn <= rsn) act[bsn]++;
		ful[min(bsn,rsn)]++;
	}
	int ans = 0;
	for(auto el:ful){
		if(el.first == 1) continue;
		ans += max(act[el.first],el.second-act[el.first]);
	}
	cout << ans+(act[1]>0);
	return 0;
}