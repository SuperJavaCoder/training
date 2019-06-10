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
int a[N];


int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	int n,x;
	cin >> n >> x;
	if(x == 1 || x == 2*n-1) return cout << "No",0;
	if(x == n){
		cout << "Yes" << endl;
		rep(i,0,2*n-1){
			cout << i+1 << endl;
		}
		return 0;
	}
	cout << "Yes\n";
	if(x < n){
		rep(i,1,x-1){
			a[i] = i;
		}
		rep(i,x-1,n-1){
			a[i] = i+2;
		}
		a[n-1] = x-1;
		a[n] = x;
		rep(i,n+1,2*n){
			a[i] = i;
		}
		rep(i,0,2*n-1){
			cout << a[i+1] << endl;
		}
	}else{
		rep(i,1,n){
			a[i] = i;
		}
		a[n] = x;
		a[n+1] = x+1;
		rep(i,n+2,n+2+x-n){
			a[i] = i-2;
		}
		rep(i,n+2+x-n,2*n){
			a[i] = i;
		}
		rep(i,1,2*n){
			cout << a[i] << endl;
		}
	}
	return 0;
}