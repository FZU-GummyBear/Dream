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
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

vector<ll> tmp;
ll ans, l, r, k, n, S, cnt, t, mask, ok, R, L;
vi t1, t2;
int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> l >> r >> k; ans = pw(60);
	if (r - l + 1 <= 7) {
		n = r - l + 1;
		S = pw(n) - 1;
		rep(i, 1, S+1) {
			cnt = 0; t = 0;
			rep(j, 0, n) if (pw(j) & i) cnt++, t ^= l + j; 
			if (cnt <= k && ans > t) {
				ans = t;
				mask = i;
			} 
		} 
		rep(j, 0, n) if (pw(j) & mask) tmp.pb(j);
		cout << ans << endl;
		cout << sz(tmp) << endl;
		for (auto u : tmp) cout << u + l << " ";
	}else {
		if (k == 1) ans = l, tmp.pb(l);
		if (k == 2) {
			ans = 1;
			if (l & 1) l++;
			tmp.pb(l);
			tmp.pb(l + 1);
		}
		if (k >= 4) {
			ans = 0;
			if (l & 1) l++;
			tmp.pb(l);
			tmp.pb(l + 1);
			tmp.pb(l + 2);
			tmp.pb(l + 3);
		}
		if (k == 3) {
			R = r; L = l;
			while (R > 0) t1.pb(R & 1), R >>= 1;
			while (L > 0) t2.pb(L & 1), L >>= 1;
			t2.resize(sz(t1), 0);
			n = sz(t1) - 1;
			if (t1[n] == t2[n]) ok = 0;
			else if (t1[n-1] == 0 && t2[n-1] == 1) ok = 0;
			else {
				ok = 1;
				ll i, j;
				if (t1[n-1] == 1 && t2[n-1] == 1) i = r, j = l;
				else i = pw(n) - 1, j = l;
				ans = 0;
				tmp.pb(i);
				tmp.pb(j);
				tmp.pb(i ^ j);
			}
			if (!ok) {
				ans = 1;
				if (l & 1) l++;
				tmp.pb(l);
				tmp.pb(l + 1);
			}
		}
		cout << ans << endl;
		cout << sz(tmp) << endl;
		for (auto u : tmp) cout << u << " "; 
	}
 	return 0;
}


