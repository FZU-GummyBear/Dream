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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int P = 1e6 + 3, N = 101010;

int n, a[10][N], in[N], jc[N];

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	jc[0] = 1; rep(i, 1, N) jc[i] = mul(jc[i - 1], i);
	rep(i, 1, N) in[i] = kpow(i, P - 2);
	// a[0][i] = 1 / i
	rep(i, 1, N) a[0][i] = add(a[0][i - 1], in[i]);
	rep(i, 1, 10) rep(j, 1, N) {
		a[i][j] = add(a[i][j - 1], mul(a[i - 1][j], in[j]));
	}
	int n, k; 
	while(cin >> n >> k) {
		if(!n && !k) break;
		int ans = a[k][n];
		ans = mul(ans, kpow(n, k + 1));
		ans = mul(ans, kpow(jc[n], 10));
		cout << ans << endl;
	}
	return 0;
}
