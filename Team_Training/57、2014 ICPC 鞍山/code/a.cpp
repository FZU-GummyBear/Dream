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
typedef long double db;
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

const int N = 55;
db jc[N], ans[1 << 13], f[N], g[N];
int cnt[N], T, n, m, x, S, sum, st;

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(13);
	cin >> T;
	jc[0] = 1; rep(i, 1, 50) jc[i] = jc[i-1] * i;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) cnt[i] = 4;
		rep(i, 1, m+1) cin >> x, cnt[x]--;
		S = pw(n);
		rep(i, 0, S) ans[i] = 0;
		if (cnt[1] == 0) {
			int s = 1;
			rep(i, 2, n+1) if (cnt[i] == 0) s += pw(i - 1);
			ans[(~s) & (pw(n) - 1)] = 1;
		}else {
			cnt[1]--; sum = 0;
			rep(i, 1, n+1) sum += cnt[i];
			rep(i, 0, S) if (!(i & 1)) {
				rep(i, 0, sum+1) f[i] = 0; f[0] = 1;
				rep(j, 1, n+1) if (cnt[j] > 0) {
					if (pw(j - 1) & i) st = 0; else st = cnt[j];
					rep(k, 0, sum+1) g[k] = 0;
					rep(k, st, cnt[j] + 1) {
						rep(l, 0, sum+1) if (l + k <= sum) g[l + k] += f[l] / jc[k] * jc[cnt[j]] / jc[cnt[j] - k];
					}
					rep(k, 0, sum+1) f[k] = g[k]; 
				}
				rep(k, 0, sum+1) f[k] = f[k] * jc[k] * jc[sum - k], ans[i] += f[k];
				ans[i] /= jc[sum + 1] / (cnt[1] + 1);
			} 
			rep(i, 0, S) if (i & 1) ans[i] = ans[i - 1];
			per(i, 0, n) rep(j, 0, S) if (pw(i) & j) ans[j] -= ans[j ^ pw(i)];
		}
		rep(i, 0, pw(n - 1)) cout << ans[(~(i << 1 | 1)) & (pw(n) - 1)] << endl;
	}
	return 0;
}


