#include <iostream>
using namespace std;
 
int a[5005];
int ans[50005];
 
int gcd(int a,int b){
	return (b?gcd(b,a%b):a);
}
 
int limit(int x,int a){
	if(x >= a){
		return x - a;
	}
	return x;
}
 
int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i){
		cin >> a[i];
	}
	for (int i = 1; i < a[0]; ++i){
		ans[i] = 1000000001;
	}
	for (int i = 1; i < n; ++i){
		int step = a[i]%a[0];
		int gc = gcd(a[i],a[0]);
		for (int j = 0; j < gc; ++j){
			int l = j;
			int c = limit(j+step,a[0]);
			while(c != j){
				ans[c] = min(ans[c],ans[l]+a[i]);
				l = c;
				c = limit(c+step,a[0]);
			}
		}
	}
	int k;
	cin >> k;
	for (int i = 0; i < k; ++i){
		int w;
		cin >> w;
		cout << (ans[w%a[0]] <= w?"TAK":"NIE") << endl;
	}
	return 0;
}
