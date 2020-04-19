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
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

// [0,n)
struct ST{
	static const int N = 101010;
	pii a[20][N]; int lg[N];
	void build(pii *v, int n){
		rep(i, 2, n + 1) lg[i] = lg[i >> 1] + 1;
		rep(i, 0, n) a[0][i] = v[i];
		rep(i, 1, lg[n] + 1) rep(j, 0, n - (1 << i) + 1) {
			a[i][j] = max(a[i - 1][j], a[i - 1][j + (1 << i >> 1)]);
		}
	}
	pii qry(int l, int r){
		if(l > r) swap(l, r);
		int i = lg[r - l + 1];
		return max(a[i][l] , a[i][r + 1 - (1 << i)]);
	}
} st;

const int N = 1e5 + 7;
int n;
ll dp[N];
ll ans;
pii a[N];

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n) cin >> a[i].fi, a[i].se = i;
	st.build(a+1, n-1);
	per(i, 1, n) {
		if(a[i].fi >= n) {
			dp[i] = n - i;
			ans += dp[i];
			continue;
		} 
		pii t = st.qry(i, a[i].fi-1);
		dp[i] = dp[t.se] + n - a[i].fi + t.se - i; 
		ans += dp[i];
	}
	cout << ans << endl;
	return 0;
}


