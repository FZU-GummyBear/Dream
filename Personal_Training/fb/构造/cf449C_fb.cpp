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

const int N = 1e5 + 7;
vi tmp, tmp2;
vector<pii> ans;
int n, vis[N], f[N];

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	
	rep(i, 2, n+1) if (!f[i]){
		for (int j = i + i; j <= n; j += i) f[j] = 1;
	}
	
	per(i, 2, n+1) if (!f[i]){
		tmp.clear();
		for (int j = i; j <= n; j += i) if (!vis[j]) {
			vis[j] = 1;
			tmp.pb(j);
		}
		int t = sz(tmp) / 2;
		if (sz(tmp) == 1) continue;
		if (sz(tmp) & 1) {
			int u = tmp[1];
			tmp.erase(tmp.begin() + 1);
			vis[u] = 0;
		}
		rep(i, 0, t) ans.pb(mp(tmp[i*2], tmp[i*2+1]));	
	}
	cout << sz(ans) << endl;
	for (auto u : ans) cout << u.fi << " " << u.se  << endl;
	return 0;
}


