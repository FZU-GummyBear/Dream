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

const int N = 1 << 24, inf = pw(30);
int a[50], b[10], ans[N], c[N], n, k, S, jc[50], an, ma;
bool vis[N];

int main() {
	//FI(a);
	de(pow(3, 12) * 24 * 24);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	jc[0] = 1; rep(i, 1, n+1) jc[i] = mul(jc[i-1], i); 
	rep(i, 0, n) cin >> a[i];
	cin >> k;
	rep(i, 0, k) cin >> b[i], ma = max(ma, b[i]);
	S = pw(n) - 1;
	rep(i, 1, S+1) {
		int t = i & -i;
		c[i] = c[i ^ t] + a[__builtin_ctz(t)];
		if (c[i] > inf) c[i] = inf;
		rep(j, 0, k) if (c[i] == b[j]) vis[i] = 1;
	}
	ans[0] = 1;
	rep(i, 0, S) if (!vis[i]) {
		if (c[i] > ma) {
			an = add(an, mul(ans[i], jc[n - __builtin_popcount(i)]));
			continue;
		}
		for (int x = S ^ i, t = x & -x; x; x &= x - 1, t = x & -x) {
			//if (!vis[i + t]) ans[i + t] = add(ans[i + t], ans[i]);
			if ((ans[i + t] += ans[i]) >= P) ans[i + t] -= P; 
		}
	}
	cout << add(an, vis[S] ? 0 : ans[S]) << endl;
	return 0;
}


