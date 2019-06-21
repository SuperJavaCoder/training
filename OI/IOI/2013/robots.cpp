/*
Let's binary search for the answer, suppose we are trying to find if it's possible to fit all toys in K minutes,
first we insert min(T,A*K) numbers into a map (each number repeated K times). Then we insert the same thing
but for the small robots into a vector (it will be sorted). Then sorting all toys by their Size (increasing) and then
by their Weight (decreasing). Then, we try to match toys (in decreasing order) with the weakest weak robot possible,
if it doesn't exist, we try to match it with the largest small robot, if it doesn't exist, abort the check and return false,
if everything went fine, return true
*/
#include <vector>
#include <utility>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
typedef long long ll;
using namespace std;
#include "robots.h"

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
	vector<pair<int,int>> ok;
	for (int i = 0; i < T; ++i){
		ok.push_back({S[i],W[i]});
	}
	sort(X,X+A);
	reverse(X,X+A);
	sort(Y,Y+B);
	reverse(Y,Y+B);
	int l = (T+A+B-1)/(A+B),r = T,ans = -1;
	vector<pair<int,int>> q;
	for (int i = 0; i < T; ++i){
		q.push_back(ok[i]);
	}
	sort(q.begin(), q.end(),[](auto e,auto z){
		if(e.first == z.first) return e.second > z.second;
		return e.first < z.first;
	});
	while(l <= r){
		int mid = (l+r)/2;
		bool good = true;
		map<int,int> ava;
		vector<int> ad;
		// (S W) (Y X) 
		int mx1 = min(ll(T),ll(A)*ll(mid));
		int mx2 = min(ll(T),ll(B)*ll(mid));
		for (int i = 0; i < mx1; ++i){
			ava[X[i/mid]]++;
		}
		for (int i = 0; i < mx2; ++i){
			ad.push_back(Y[i/mid]);
		}
		int j = size(q)-1;
		int done = 0;
		while(j >= 0){
			auto fr = q[j];
			auto fl = ava.upper_bound(fr.second);
			if(fl == ava.end()){
				if(done != size(ad)){
					if(ad[done] <= fr.first){
						good = 0;
						break;
					}else{
						done++;		
					}
				}else{
					good = 0;
					break;
				}
			}else{
				ava[(*fl).first]--;
				if(!ava[(*fl).first]) ava.erase((*fl).first);
			}
			j--;
		}
		if(good){
			ans = mid;
			r = mid-1;
		}else{
			l = mid+1;
		}
	}
	return ans;
}
