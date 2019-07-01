/*
We can observe that minimal Q numbers will appear in the same way if they were in the same order, regardless of the other N-Q bigger numbers,
So we could iterate over a vector of the possible solutions of the minimum Q numbers, then find the possible insertion points for each solution,
and try it if it creates the same one as in the input, multiple optimization here and there and the solution will work.

Complexity: unknown, but it's kinda like backtracking, and it's close to O(N!) but a bit faster
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
template <typename T> ostream& operator<<(ostream& os, const vector<T>& v){os << "{";for (int i = 0; i < sz(v); ++i) { os << v[i]; if (i != sz(v) - 1) os << ",";}os << "}";return os;}
template <typename T, typename S>ostream& operator<<(ostream& os, const map<T, S>& v){for (auto it : v)os << "{" << it.first << "," << it.second << "}";return os;}
template <typename T, typename S>ostream& operator<<(ostream& os, const pair<T, S>& v){os << "{" << v.first << "," << v.second << "}";return os;}
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
vector<vector<int>> ans;

void fulltest13(vector<int>& v){
	ans = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
	int curnum;
	int currow;
	for(int i = 0; i < sz(v); i++){
		curnum = v[i];
		currow = 0;
		while(true){
			auto pos = upper_bound(ans[currow].begin(),
				ans[currow].end(),curnum);
			if(pos == ans[currow].end()){
				ans[currow].push_back(curnum);
				break;
			}
			int idx = pos-ans[currow].begin();
			swap(ans[currow][idx],curnum);
			currow++;
		}
	}
}

int main(){
	//fold
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(10);
	//endfold
	int n;
	cin >> n;
	vector<int> empty = {};
	vector<vector<vector<int>>> all(15,vector(15,vector(empty)));
	vector<vector<int>> re =
	{{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
	map<int,int> idxcomp;
	int tot = 0;
	rep(i,0,n){
		int x;
		cin >> x;
		rep(j,0,x){
			int e;
			cin >> e;
			tot++;
			re[i].push_back(e);
			idxcomp[e]++;
		}
	}
	int num = 1;
	vector<int> rev;
	for(auto &x:idxcomp){
		x.second = num++;
		rev.push_back(x.first);
	}
	rep(i,0,n){
		rep(j,0,sz(re[i])){
			re[i][j] = idxcomp[re[i][j]];
			rep(k,0,15){
				if(re[i][j] <= k+1){
					all[k][i].push_back(re[i][j]);
				}
			}
		}
	}
	vector<vector<int>> res = {{1}};
	vector<vector<int>> res2;
	vector<int> vqwe;
	rep(i,2,tot+1){
		vqwe = vector(i,0);
		if(i == 15){
			for(int cur = 0; cur < sz(res); cur++){
				rep(j,0,sz(res[cur])+1){
					rep(k,0,i){
						if(k < j){
							vqwe[k] = res[cur][k];
						}else if(k == j){
							vqwe[k] = i;
						}else{
							vqwe[k] = res[cur][k-1];
						}
					}
					fulltest13(vqwe);
					if(ans == all[i-1]){
						rep(p,0,tot){
							cout << vqwe[p] << " ";
						}cout << endl;
					}
				}
			}
			return 0;
		}
		for(int cur = 0; cur < sz(res); cur++){
			rep(j,0,sz(res[cur])+1){
				rep(k,0,i){
					if(k < j){
						vqwe[k] = res[cur][k];
					}else if(k == j){
						vqwe[k] = i;
					}else{
						vqwe[k] = res[cur][k-1];
					}
				}
				fulltest13(vqwe);
				if(ans == all[i-1]){
					res2.push_back(vqwe);
				}
			}
		}
		swap(res,res2);
		res2.clear();
	}
	for(auto& x:res){
		rep(i,0,tot){
			cout << rev[x[i]-1] << " ";
		}cout << endl;
	}
	return 0;
}