
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
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

//int a[2][2], b[2][2], e;
uint n;

struct mat {
	ull a[2][2];
	mat () {memset(a, 0, sizeof(a)); }
	mat operator * (const mat &c) const {
		mat r;
		rep(i, 0, 2) rep(j, 0, 2) rep(k, 0, 2) r.a[i][j] = (r.a[i][j] + a[i][k] * c.a[k][j]) % n;
		return r;
	}
	bool operator == (const mat &c) const{
		rep(i, 0, 2) rep(j, 0, 2) if (a[i][j] != c.a[i][j]) return 0;
		return 1;
	}
	bool operator < (const mat &c) const{
		rep(i, 0, 2) rep(j, 0, 2) if (a[i][j] != c.a[i][j]) return a[i][j] < c.a[i][j];
		return 0;
	}
} e, b, invb;

mat kpow(mat a, ll b) {
	mat res = e;
	while (b) {
		if (b & 1) res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

struct Bsgs{
	map<mat, int> M;
	ll bsgs(ll n) {
		mat t = b;
		rep(i, 1, 51) {
			if (t == e) return i;
			t = t * b;
		}
		ll sq = sqrt(n); t = b; M.clear();
		rep(i, 1, sq+1) {
			if (M.count(t)) break;
			M[t] = i;
			t = t * b;
		}
		mat res = e;
		ll len = n / sq; mat sa = kpow(invb, sq);
		rep(i, 0, len+1) {
			if (i > 0 && res == e) return i * sq;
			if (M.count(res)) return i * sq + M[res]; else res = res * sa;
		}
	}
} B;

ll solve(int P) {
	int a[2][2], b[2][2];
	rep(i, 0, 2) rep(j, 0, 2) a[i][j] = 1; a[1][1] = 2 % P;
	rep(i, 0, 2) rep(j, 0, 2) b[i][j] = (i == j);
	for(int k = 1; ; k++) {
		int c[2][2] = {0};
		rep(i, 0, 2) rep(j, 0, 2) rep(t, 0, 2) c[i][j] = (c[i][j] + b[i][t] * a[t][j]) % P;
		bool ok = 1;
		rep(i, 0, 2) rep(j, 0, 2) if(c[i][j] != (i == j)) ok = 0;
		rep(i, 0, 2) rep(j, 0, 2) b[i][j] = c[i][j];
		if(ok) return k;
	}
}

void tes() {
	//rep(n, 2, 10) dd(n), de(solve(n));
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	tes();
	e.a[0][0] = e.a[1][1] = 1;
	b.a[0][0] = b.a[0][1] = b.a[1][0] = 1; b.a[1][1] = 2;


	//while (cin >> n) {
	for(int i = 2; i <= 1000; i++) {
		n = i;
		if (n == 2) {
			cout << 3 << endl;
			continue;
		}
		invb.a[0][0] = 2;
		invb.a[0][1] = invb.a[1][0] = n-1;
		invb.a[1][1] = 1;
		//assert(B.bsgs(n) == solve(n));
		if (B.bsgs(3 * n) != solve(n)) dd(n), dd(B.bsgs(n)), de(solve(n));
		//cout << B.bsgs(n) << endl;
	}
	return 0;
}
