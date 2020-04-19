#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 333;

int n, len, ca, cb;
char s[N], ans[N];

int print() {
	s[len] = '\0';
	printf("%s\n", s);
	fflush(stdout);
	int x; scanf("%d", &x);
	assert(x >= 0);
	if(x == 0) exit(0);
	return x;
}

int main() {
	len = 300; rep(i, 0, len) s[i] = 'a'; 
	int a = 300 - print();
	len = 300; rep(i, 0, len) s[i] = 'b'; 
	int b = 300 - print();
	n = a + b;
	len = n; rep(i, 0, len) s[i] = 'a';
	rep(i, 0, n - 1) {
		s[i] = 'b';
		if(print() >= b) ans[i] = 'a', ++ca;
		else ans[i] = 'b', ++cb;
		s[i] = 'a';
	}
	if(ca != a) ans[n - 1] = 'a';
	else ans[n - 1] = 'b';
	rep(i, 0, n) s[i] = ans[i];
	print();
	return 0;
}
