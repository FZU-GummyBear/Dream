#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e9;

bool found;
int x, y, x0 = -101;
double r1, r2;

void ans() {
    cout << "A " << x << ' ' << y << endl;
}

int main() {
    
	cout << "Q -101 0" << endl;
	//cout.flush();
	cin >> r1;
	cout << "Q -101 0" << endl;
	//cout.flush();
	cin >> r2;
	if(r1 < r2) { // либо x-1, либо y-1
		x = x0 - 1.0/2 + r2/2 - r1/2;
		y = sqrt(r1 - (x - x0)*(x - x0));

//		clog << x << ' ' << y << '\n';

		if(x >= 0 && x <= 100 && y >= 0 && y <= 100) {
			ans();
			return 0;
		}

		y = - 1.0/2 + r2/2 - r1/2;
		x = sqrt(r1 - y*y) + x0;
		ans();

	} else { // либо x+1, либо y+1
		x = x0 + 1.0/2 - r2/2 + r1/2;
		y = sqrt(r1 - (x - x0)*(x - x0));

//		clog << x << ' ' << y << '\n';

		if(x >= 0 && x <= 100 && y >= 0 && y <= 100) {
			ans();
			return 0;
		}

		y = 1.0/2 - r2/2 + r1/2;
		x = sqrt(r1 - y*y) + x0;
		ans();
	}

	return 0;
}