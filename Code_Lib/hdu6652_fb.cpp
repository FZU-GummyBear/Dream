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

const int N = 3e5 + 7;
int T, len, L, R, a, b, l, r, mid;
ll f[N], g[N];

int main() {
	FI(a);
	FO(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> L >> R >> a >> b; len = R - L + 2;
		rep(i, 1, len+1) {
			l = 1; r = i;
			while (l + 1 < r) {
				mid = (l + r) / 2;
				if (f[mid - 1] + b < f[i - mid] + a) l = mid; else r = mid;
			}
			f[i] = pw(60);
			rep(k, l, r+1) f[i] = min(f[i], max(f[k-1] + b, f[i - k] + a));
		}
		g[0] = a - b;
		rep(i, 1, len+1) {
			l = 1; r = i;
			while (l + 10 < r) {
				mid = (l + r) / 2;
				if (g[mid - 1] + b < f[i - mid] + a) l = mid; else r = mid;
			}
			g[i] = pw(60);
			rep(k, l, r+1) g[i] = min(g[i], max(g[k-1] + b, f[i - k] + a));
		}
		if (L == 0) cout << f[R] << endl;
		else cout << g[R - L + 1] << endl;
	}
	return 0;
}


