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
typedef unsigned int uint;
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

unordered_map<uint, int> M, tmp;

int T, n, p[20], ans[100];
string s[20];

uint encry(vi t) {
	uint res = 0;
	rep(i, 0, n+2) res = res * (n + 1) + t[i];
	return res;
}

vi decry(uint t) {
	vi res;
	rep(i, 0, n+2) res.pb(t % (n + 1)), t /= (n + 1);
	reverse(all(res));
	return res;
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n;
		p[0] = 1; rep(i, 1, n+1) p[i] = p[i - 1] * (n + 1);
		rep(i, 0, n) cin >> s[i];
		M.clear(); tmp.clear();
		M[0] = 1;
		int ma = 0;
		rep(i, 0, n) rep(j, 0, n) {
			for (auto u : M) {
				vi t = decry(u.fi);
				rep(i, 0, n) t[i] = t[i+1]; t[n] = 0;
				(tmp[encry(t)] += u.se) %= P;
				if (s[i][j] == 'o') {
					vi t = decry(u.fi);
					int v = min({j == 0 ? 0 : t[0], j == 0 ? 0 : t[n], t[1]}) + 1;
					rep(i, 0, n) t[i] = t[i+1]; t[n] = v; t[n + 1] = max(t[n + 1], v);
					(tmp[encry(t)] += u.se) %= P;
				}
			}
			M.swap(tmp);
			tmp.clear();
		}
		rep(i, 0, n+1) ans[i] = 0;
		for (auto u : M) {
			vi t = decry(u.fi);
			(ans[t[n+1]] += u.se) %= P;
		}
		rep(i, 0, n+1) cout << ans[i] << endl;
	} 
	return 0;
}


