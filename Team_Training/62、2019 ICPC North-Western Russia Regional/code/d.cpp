//#pragma GCC optimize(3)
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse2")
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
const int P = 998244353;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int M = 1 << 17 << 1;

int n, k, f[M], g[M], h[M], u[M], F[M];

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> k;
	rep(i, 1, n+1) f[i] = kpow(k, (i + 1) / 2);
	rep(i, 1, n+1) if (i & 1) F[i] = mul(i, kpow(k, (i + 1) / 2));
	else F[i] = mul(mul(kpow(k, i / 2), k + 1), i / 2); 
	rep(i, 1, n+1) {
		h[i] = add(h[i], F[i]);
		for (int j = i + i; j <= n; j += i) h[j] = add(h[j], -mul(j / i, h[i]));
		for (int j = i; j <= n; j += i) g[j] = add(g[j], h[i]);
	}
	int ans = 0;
	rep(i, 1, n+1) ans = add(ans, g[i]);
	cout << ans << endl;
	return 0;
}


