/*
O(N^2) solution is obvious, trying every k to see if it works, but the problem has an odd constrain, M <= 1000, how could we use that in our advantage?
Let's try solving this for every K but the actual check is done in O(M) time, how?
Create twp frequency array sized M which represents the current left and right K elements, and try matching them  beginning from the largest number to the smallest,
If in any time we had to match  a number from the left array with an equal or less number in the right array, we abort the check and return false, if everything goes well,
and the left pointer reaches -1 abort the check, since it's done. Finally print the largest K that worked. 
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
#define  N  (20005)

//global
int a[N];
int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	//freopen("bins.in","r",stdin);
	//freopen("bins.out","w",stdout);
	int n,m;
	cin >> m >> n;
	rep(i,0,n){
		cin >> a[i];
	}
	if(n == 1) return cout << 0,0;
	vector<int> l(1005,0);
	vector<int> r(1005,0);
	l[a[0]]++; 
	r[a[1]]++; 
	int w = 0;
	int e = 1;
	int ans = 0;
	rep(i,1,(n)/2+1){
		if(!r[1] && !l[m]){
			vector<int> curl = l;
			vector<int> curr = r;
			int z = m-1,x = m;
			bool good = true;
			while(true){
				if(curl[z] == curr[x]){
					z--;
					x--;
				}else if(curl[z] < curr[x]){
					curr[x] -= curl[z];
					z--;
				}else if(curl[z] > curr[x]){
					curl[z] -= curr[x];
					x--;
				}
				if(z >= x){
					good = false;
					break;
				}
				if(z < 0) break;
			}
			if(good) ans = i;
		}
		w++;
		l[a[w]]++;
		r[a[w]]--;
		e++;
		r[a[e]]++;
		e++;
		r[a[e]]++;
	}
	cout << ans << endl;
	return 0;
}