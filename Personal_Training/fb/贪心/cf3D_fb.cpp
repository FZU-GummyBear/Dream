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

const int N = 2e5 + 7;
string s;
int n, m, a[N], b[N], cnt, now, p;
priority_queue<pii> q;
ll ans;
int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> s;
	for (auto v : s) if (v == '?') m++;
	rep(i, 1, m+1) cin >> a[i] >> b[i];
	rep(i, 1, m+1) a[i] = b[i] - a[i], ans += b[i];
	for (auto &&v : s) {
		if (v == '(') cnt++;
		if (v == ')') cnt--;
		if (v == '?') {
			v = ')'; cnt--; ++ now; q.push(mp(a[now], p));  
		}
		if (cnt < 0) {
			if (q.empty()) {
				cout << -1 << endl;
				return 0;
			}
			ans -= q.top().fi; s[q.top().se] = '(';
			cnt += 2; q.pop();
		}
		p++;
	}
	if (cnt != 0) {
		cout << -1 << endl;
		return 0;
	}
	cout << ans << endl;
	cout << s << endl;
	return 0;
}


