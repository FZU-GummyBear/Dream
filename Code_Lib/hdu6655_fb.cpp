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
int T, n, a[N], b[N], op, m, mod, cnt1[N * 2], cnt2[N * 2], ans1, ans2, o;
vi V;
vector<pii> tmp;

unsigned long long k1, k2;
unsigned long long rng() {
    unsigned long long k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= k3 << 23;
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m >> op;
		if (op == 1) {
			rep(i, 1, n+1) cin >> a[i];
			rep(i, 1, m+1) cin >> b[i];
		}else {
			cin >> k1 >> k2 >> mod;
			rep(i, 1, n+1) a[i] = rng() % mod;
			cin >> k1 >> k2 >> mod;
			rep(i, 1, m+1) b[i] = rng() % mod;
		}
		V.clear();
		rep(i, 1, n+1) V.pb(a[i]);
		rep(i, 1, m+1) V.pb(b[i]);
		sort(all(V));
		V.erase(unique(all(V)), V.end());
		per(i, 0, sz(V)) cnt1[i] = cnt2[i] = 0;
		rep(i, 1, n+1) a[i] = lower_bound(all(V), a[i]) - V.begin(), cnt1[a[i]]++;
		rep(i, 1, m+1) b[i] = lower_bound(all(V), b[i]) - V.begin(), cnt2[b[i]]++;
		per(i, 0, sz(V)) if (cnt1[i] && cnt2[i]) tmp.pb(mp(cnt1[i] + cnt2[i], i));
		else ans1 += cnt1[i], ans2 += cnt2[i];
		sort(all(tmp)); o = 1;
		per(i, 0, sz(tmp)) {
			if (o) ans1 += cnt1[tmp[i].se];
			else ans2 += cnt2[tmp[i].se];
			o ^= 1;
		} 
		if (ans1 <= ans2) cout << "Quber CC" << endl;
		else cout << "Cuber QQ" << endl;
		tmp.clear(); ans1 = ans2 = 0;
	}
	return 0;
}


