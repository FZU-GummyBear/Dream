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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 6030, P = 1e9 + 7;

int s[N][N], C[N], in[N];

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

void tes(int n, int k) {
	s[0][0] = s[2][1] = 1;
	rep(i, 2, N) rep(j, 1, N) if(!s[i][j]) {
		s[i][j] = mul(i - 1, add(s[i - 2][j - 1], s[i - 1][j]));
	}
	int ans = 0;
	rep(i, 0, 2 * k + 1) rep(j, max(0, i - k), k + 1) {
		ans = add(ans, mul(C[i], s[i][j]));
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 0, N) in[i] = kpow(i, P - 2);
	int n, k; cin >> n >> k;
	rep(i, 0, 2 * k + 1) {
		int &t = C[i] = 1;
		rep(j, 1, i + 1) t = mul(t, n - j + 1), t = mul(t, in[j]);
	}
	tes(n, k);
	return 0;
}
