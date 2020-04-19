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
typedef uniform_int_distribution<ll> RR;
mt19937 gen(998244353);
ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 998244353;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

int T;
ll a, b, x, y;

ll solve(ll x, ll y) {
	if (b * 2 <= a) return (y + max(x - 1, 0ll)) * b;
	if (b > a) return max(x - 1, y) * a;
	ll t = min(max(x - 1, 0ll), y);
	return t * a + max(x - 1 - t, y - t) * b; 
}

ll solve2(ll x, ll y) {
	if (b * 2 <= a) return (y + x) * b;
	if (b > a) return max(x, y) * a;
	ll t = min(x, y);
	return t * a + max(x - t, y - t) * b; 
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> a >> b >> x >> y;
		if (x >= 0 && y >= 0) cout << solve(x, y) << endl;
		else if (x <= 0 && y <= 0) cout << solve(-y, -x) << endl;
		else if (x < 0) cout << solve2(-x, y) << endl;
		else cout << solve2(x - 1, -y - 1) << endl;
	}
	return 0;
}


