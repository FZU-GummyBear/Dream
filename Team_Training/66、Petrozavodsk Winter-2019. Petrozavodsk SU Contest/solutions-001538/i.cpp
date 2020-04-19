#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma GCC optimize("O3") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx") 
#define __USE_MINGW_ANSI_STDIO 0
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include<stdio.h>
#include<iomanip>
#include<set>
#include<string>
#include<map>
#include<bitset>
#include <math.h>
#include<queue>
#include<complex>
#include<ctime>
#include<list>
#include<stack>
#define ll long long
#define is_bit(a,b) (a&(1<<b))
using namespace std; 
const ll mod = 1000000007;
ll m,n;
int T;
ll binpow(ll m, ll n){
	if(!n)
		return 1;
	if(n&1)
		return (m*binpow(m,n-1))%mod;
	ll b = binpow(m, n/2);
	return(b*b)%mod;
}	
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//	 freopen("o.in", "r", stdin);
//		 freopen("o.out", "w", stdout);
	cin >> T;
	for(int i = 0 ; i< T; i++){
	cin >> n >> m;
	//ans = m^(n*n - 2*n)
	if(n == 4 && m % 2 == 0 )
		cout << (2 *binpow(m,n * n - 2*n)) % mod << "\n";
	else	
		cout << binpow(m,n * n - 2*n) << "\n";
	}
	return 0;
}