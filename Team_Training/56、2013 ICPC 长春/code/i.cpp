#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int P = 1e9 + 7, N = 101010;

inline int upd(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
inline int mul(int a, int b) {
	return 1ll * a * b % P;
}
struct Int {
	int a, b; 
	Int(int a = 0, int b = 0) : a(a), b(b) {}
	inline Int operator + (const Int &c) const {
		return Int(upd(a, c.a), upd(b, c.b));
	}
	inline Int operator - (const Int &c) const {
		return Int(upd(a, -c.a), upd(b, -c.b));
	}
	inline Int operator * (const Int &c) const {
		return Int(mul(a, c.a), mul(b, c.b));
	}
	inline bool operator == (const Int &c) const { return a == c.a && b == c.b; }
}_0 = Int(), _1 = Int(1, 1), B[N];

void init(int n) {
	B[0] = _1; B[1] = Int(233, 241);
	rep(i, 2, n + 1) B[i] = B[i - 1] * B[1];
}
struct Str {
	Int a; int len; ll val;
	Str(Int a = _0, int len = 0) : a(a), len(len) { val = a.a * P + a.b; }
	Str(int x) { a = Int(x, x); len = 1; }
	inline Str operator + (const Str &c) const {
		return Str(a * B[c.len] + c.a, len + c.len);
	}
	inline Str operator - (const Str &c) const {
		return Str(a - c.a * B[len - c.len], len - c.len); 
	}
	inline bool operator == (const Str &c) const { return a == c.a && len == c.len; }
	inline bool operator < (const Str &c) const { return val < c.val; }
}ha[N];
void init(vi &s, Str *ha) {
	rep(i, 0, sz(s)) ha[i] = i > 0 ? ha[i - 1] + Str(s[i] + 1) : Str(s[0] + 1);
}
Str sub(Str *ha, int l, int r) {
	if(l > r) return Str();
	return l > 0 ? ha[r] - ha[l - 1] : ha[r];
}

int m, l, top;
string s;
Str val[N];

int solve() {
	if(top < m) return 0;
	int l = 1, r = 0;
	map<Str, int> cnt;
	int ans = 0;
	while(r + 1 <= top) {
		++r;
		++cnt[val[r]];
		if(r - l + 1 > m) {
			int k = cnt[val[l]];
			if(k == 1) cnt.erase(val[l]);
			else --cnt[val[l]];
			l++; 
		}
		if(r - l + 1 == m && sz(cnt) == m) ++ans;
	}
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	init(N - 1);
	while(cin >> m >> l >> s) {
		int ans = 0;
		vi v; for(auto u : s) v.pb(u - 'a');
		init(v, ha);
		rep(i, 0, l) {
			top = 0;
			for(int j = i + l - 1; j < sz(s); j += l) val[++top] = sub(ha, j - l + 1, j);
			ans += solve();
		}
		cout << ans << endl;
	}
	return 0;
}
