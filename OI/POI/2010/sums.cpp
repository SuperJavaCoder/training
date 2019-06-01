/*
Explanation: The problem is a well known problem called 'Coin Change'. However, this one has something different,
which is the upper limit of the queries done to the problem, and it doesn't ask for the number of coins used, it asks
if there's possible formation of coins or not.

Let's represent every query as 'a[0] + X = q[i]', if we take the reminder of both sides we will end up with:
a[0] + X = q[i]
(a[0] + X) % a[0] = q[i] % a[0]
(a[0] % a[0] + X % a[0]) % a[0] = q[i] % a[0]
X % a[0] = q[i] % a[0]
So what does that mean? It means that we should find a positive formation of numbers that gives us a number X, and
(X % a[0] == q[i] % a[0]) and (a[0] + X = q[i]). If we were able to get a number X such that: (X % a[0] == q[i] % a[0]) 
and (a[0] + X < q[i]), we could still get the solution by adding a[0] to X.

The value of (X % a[0]) can be in [0,45000]. So we could store an array ans, sized about 45000,
in which (ans[i] = the minimum value of X such that (a[0]+X)%a[0] == i) and (X is a positive formulation
of the coins [2,N])). The answer to q[i] is 'TAK' if (ans[ q[i]%a[0] ] <= q[i]) and 'NIE' otherwise. So the remaining
question is how to fill it?

We can observe that the problem can be represented as a graph where verticies [0,45000] are possible values for (X % a[0])
, and the edges (i -> j) as the minimum value of a[k] satisfying ((j - i + a[0]) % a[0] == a[k] % a[0]). Running SSSP on
the following graphs will fill the the array ans. However, we can observe that for a path (A---+3--->B---+5--->D) to exist,
any permutaion of the graph also exists, like (A---+5--->C---+3--->D). Which means we can run the following algorithm
without any problems:

Foreach K in [2,N]:
	Foreach Q in [0,GCD(a[1],a[K])):
		Last = Q
		Current = (Q + A[K]) % a[1]
		While Current != Q:
			ans[Current] = min(ans[Current],ans[Last]+A[k])
			Last = Current
			Current = (Current + A[K]) % a[1]

So why does this work? It works because we can represent the array ans as GCD(A[k],a[1]) discrete sets, in each one we
can traverse the whole set by just doing (Current = (Current + A[K]) % a[1]), proof left for the reader, and each path
can be found regardless of the order of the numbers as sum is commutative. This way the whole code is O(N*M) where M
is a[0]. Which is about O(2.5e8) which should be too slow, but calculations are pretty light, so that works.

*/
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
