#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 2e7 + 7;
int L, n, a[20], m;
ll s, l, r, ans;
bool f[N];

void solve(ll x) {
	per(i, 0, m+1) {
		if (i - x < 0) break;
		f[i] |= f[i - x];
	}
}

void work() {
	f[0] = 1; rep(i, 1, m+1) f[i] = 0;
	rep(i, 1, n+1) {
		int now = 1;
		while (a[i] - now >= 0) {
			a[i] -= now;
			solve(1ll * now * i);
			now <<= 1;
		}
		if (a[i]) solve(1ll * a[i] * i);
	}
}

int main() {
//	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	while (cin >> n) {
		L = 1;
		rep(i, 1, n+1) L = L / __gcd(L, i) * i; s = 0; ans = 0;
		rep(i, 1, n+1) cin >> a[i], s += 1ll * i * a[i];
		m = n * L; l = m + 1; r = s - m - 1;
		if (l <= r) {
			work();
			rep(i, 0, m+1) if (f[i]) ans += 2;
			per(i, l - L, l) if (f[i]) {
				ans += (r - i) / L;
			}
		}else {
			m = s;
			work();
			rep(i, 0, m+1) if (f[i]) ans++; 
		}
		cout << ans << endl;
	} 
	return 0;
}


