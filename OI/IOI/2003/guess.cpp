/*
While you didn't find the cow yet, ask about the property that has 3 different values, if there is none ask about a property that has 2 different values,
and always choose the largest, so you can have the greater possibility of getting it right.

*/
//fold
#ifndef KHALIL
#include <bits/stdc++.h>
#else
#include "header.h"
#endif
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

//global
int n,p;
pair<string,int> a[55];
int what;

int solve(int l,int r,int i){
	if(l == r) return l;
	int l1,r1,l2,r2,l3,r3;
	int len1,len2,len3;
	bool good = false;
	int first = 1;
	int val = 1000000;
	rep(j,0,p){
		what = j;
		sort(a+l,a+r+1,[](pair<string,int> q,pair<string,int> w){
			return q.first[what] < w.first[what];
		});
		l1 = l;
		l2 = l1;
		while(l2 <= r && a[l2].first[j] == 'X') l2++;
		r1 = l2-1;
		l3 = l2;
		while(l3 <= r && a[l3].first[j] == 'Y') l3++;
		r2 = l3-1;
		r3 = r;
		len1 = r1-l1+1;
		len2 = r2-l2+1;
		len3 = r3-l3+1;
		if(len1 > 0 && len2 > 0 && len3 > 0){
			int misum = len1+len2+len3-max({len1,len2,len3});
			if(abs(misum-(len1+len2+len3)) < val){
				val = abs(misum-(len1+len2+len3));
				first = j;
			}
		}else if(len1 > 0 && len2 > 0){
			int misum = len1+len2+len3-max({len1,len2,len3});
			if(abs(misum-(len1+len2+len3)) < val){
				val = abs(misum-(len1+len2+len3));
				first = j;
			}
		}else if(len2 > 0 && len3 > 0){
			int misum = len1+len2+len3-max({len1,len2,len3});
			if(abs(misum-(len1+len2+len3)) < val){
				val = abs(misum-(len1+len2+len3));
				first = j;
			}
		}else if(len1 > 0 && len3 > 0){
			int misum = len1+len2+len3-max({len1,len2,len3});
			if(abs(misum-(len1+len2+len3)) < val){
				val = abs(misum-(len1+len2+len3));
				first = j;
			}
		}
	}
	i = first;
	what = i;
	sort(a+l,a+r+1,[](pair<string,int> q,pair<string,int> w){
		return q.first[what] < w.first[what];
	});
	l1 = l;
	l2 = l1;
	while(l2 <= r && a[l2].first[i] == 'X') l2++;
	r1 = l2-1;
	l3 = l2;
	while(l3 <= r && a[l3].first[i] == 'Y') l3++;
	r2 = l3-1;
	r3 = r;
	len1 = r1-l1+1;
	len2 = r2-l2+1;
	len3 = r3-l3+1;
	if(len1 == 0 && len2 > 0 && len3 > 0){
		cout << "Q " << i+1 << " Y" << endl;
		int val; cin >> val;
		if(val){
			l = l2; r = r2;
		}else{
			l = l3; r = r3;
		}
	}else if(len1 > 0 && len2 == 0 && len3 > 0){
		cout << "Q " << i+1 << " X" << endl;
		int val; cin >> val;
		if(val){
			l = l1; r = r1;
		}else{
			l = l3; r = r3;
		}
	}else if(len1 > 0 && len2 > 0 && len3 == 0){
		cout << "Q " << i+1 << " X" << endl;
		int val; cin >> val;
		if(val){
			l = l1; r = r1;
		}else{
			l = l2; r = r2;
		}
	}
	else if(len1 > 0 && len2 > 0 && len3 > 0){
		if(len1 >= len2 && len1 >= len3){
			cout << "Q " << i+1 << " X" << endl;
			int val; cin >> val;
			if(val){
				l = l1; r = r1;
			}else{
				cout << "Q " << i+1 << " Y" << endl;
				cin >> val;
				if(val){
					l = l2; r = r2;
				}else{
					l = l3; r = r3;
				}
			}
		}else if(len2 >= len1 && len2 >= len3){
			cout << "Q " << i+1 << " Y" << endl;
			int val; cin >> val;
			if(val){
				l = l2; r = r2;
			}else{
				cout << "Q " << i+1 << " X" << endl;
				cin >> val;
				if(val){
					l = l1; r = r1;
				}else{
					l = l3; r = r3;
				}
			}
		}else if(len3 >= len1 && len3 >= len2){
			cout << "Q " << i+1 << " Z" << endl;
			int val; cin >> val;
			if(val){
				l = l3; r = r3;
			}else{
				cout << "Q " << i+1 << " X" << endl;
				cin >> val;
				if(val){
					l = l1; r = r1;
				}else{
					l = l2; r = r2;
				}
			}
		}
	}
	return solve(l,r,i+1);
}

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	cin >> n >> p;
	rep(i,0,n){
		rep(j,0,p){
			string val;
			cin >> val;
			a[i].first += val;
		}
		a[i].second = i+1;
	}
	sort(a,a+n);
	int ans = solve(0,n-1,0);
	cout << "C " << a[ans].second << endl;
	return 0;
}