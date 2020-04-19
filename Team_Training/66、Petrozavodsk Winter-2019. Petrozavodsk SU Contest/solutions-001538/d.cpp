#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

long long n, k;

#define ll long long
long double one = 1.0;
void load () {
	cin >> n >> k;
}

void solve () {
	long long al, ar;
	al = max(-1ll, (ll)ceil((1 - sqrtl(one+8*k)) / 2.0));
	ar = (ll)floor((1 + sqrtl(one+8*k)) / 2.0);
	
	long long bl, br;
	bl = (ll)ceil(((2*n - one) - sqrtl((one-2*n)*(1-2*n)-8*k)) / 2.0);
	br = max(-1ll, (ll)floor(  ((2*n-one) + sqrtl((one-2*n)*(1-2*n)-8*k)) / 2.0)  );


   	long long cl, cr;
   	cl = max(al, bl);
   	cr = min(ar, br);
   	cr = min(cr, n);
   	long long ansl = cl * (cl-1) / 2 + (n-cl)*(n-cl-1)/2;
   	long long ansr = cr * (cr-1) / 2 + (n-cr)*(n-cr-1)/2;
   	
   	if(cl > cr || (cl == -1 && cr == -1))
   	{
   		cout << "-1";
   		return;
   	}

   	cl = max(0ll, cl);
   	if(ansl > ansr)
   	{
   		//cout << cl << " l  ";
   		cout << ansl;
   	}
   	else{
   	   	//cout << cr << "  ";
   		cout << ansr;
   	}




	
	
	// jnhtpjxrb gthtctxm
}  

int main() {
	

	ios_base::sync_with_stdio(false);
	cin.tie (0);

	load ();
	solve ();

	return 0;
}