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

const int N = 3e5 + 7;
int n, m, pos[N];
ll t, sum;
string s;
pair<pair<ll, int>, int> a[N];

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m >> t;
	rep(i, 0, n) {
		cin >> a[i].fi.fi >> s;
		if (s == "L") a[i].fi.se = -1;else a[i].fi.se = 1;
		a[i].se = i;
	}
	sort(a, a+n);
	rep(i, 0, n) pos[a[i].se] = i;
	rep(i, 0, n) {
		int p = a[i].fi.fi, dir = a[i].fi.se;
		if (dir == 1) sum += (p - 1 + t) / m % n;
		else sum -= (m - p  + t) / m % n;
		if (dir == 1) ((a[i].fi.fi += t-1) %= m) += 1; 
		else ((a[i].fi.fi += (m - t % m)-1) %= m) += 1; 
		sum %= n;
	}
	if(sum < 0) sum += n;
	sort(a, a+n);
	rep(i, 0, n) cout << a[(pos[i] + sum) % n].fi.fi << " \n"[i == n - 1];
	return 0;
}


