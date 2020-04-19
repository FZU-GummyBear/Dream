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

const int N = 5e5 + 7;
int T, n, q, r[N], s[N], x[N], a[N], d[N], sum[N], L, R;

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> q;
		rep(i, 1, n+1) {
			cin >> r[i] >> s[i] >> x[i] >> a[i];
			d[i] = mul(mul(s[i] - r[i], kpow(s[i], P - 2)), add(sum[i-1], -sum[x[i]-1]));
			d[i] = mul(add(d[i], a[i]), mul(s[i], kpow(r[i], P - 2)));
			sum[i] = add(sum[i-1], d[i]);
		}
		rep(i, 1, q+1) {
			cin >> L >> R;
			cout << add(sum[R-1], -sum[L-1]) << endl;
		}
	}
	return 0;
}


