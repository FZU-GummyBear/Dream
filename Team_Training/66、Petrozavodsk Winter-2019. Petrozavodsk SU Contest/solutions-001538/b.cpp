#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;

int n, m, a[1003];
int ans[1003][1003];

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) {
    	cin >> a[i];
    }
	m = 2*n-1;
    for(int i = 0; i < m; i++) {
    	for(int j = 0; j < n; j++) {
    		if(n-1+j-i >= 0)
	    		ans[i][n-1+j-i] = a[j];
	    	if(2*n-1+j-i < m)
	    		ans[i][2*n-1+j-i] = a[j];
    	}
    }
    
    cout << m << '\n';

    for(int i = 0; i < m; i++) {
    	for(int j = 0; j < m; j++)
			cout << (ans[i][j] > 0 ? ans[i][j] : 1) << ' ';
		cout << '\n';
	}
	
	return 0;
}