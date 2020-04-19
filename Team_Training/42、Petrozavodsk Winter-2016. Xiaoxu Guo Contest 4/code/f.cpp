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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 202020, P = 1e9 + 7, B = 1024;

inline int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}

int n, d, a[N], s[pw(16)], f[N], st[N], ed[N], kuai[N], sum[pw(16)];

void gao(int b) {
	for(register int i = st[b]; i <= ed[b]; ++i) sum[a[i]] = add(sum[a[i]], f[i]);
	//rep(i, 0, pw(d)) dd(i), de(sum[i]);
	for(register int i = 0; i < d; ++i) {
		for(register int j = 0; j < (1 << d); ++j) if(j >> i & 1) {
			sum[j] = add(sum[j], sum[j ^ (1 << i)]);
		}
	}
	//rep(i, 0, pw(d)) dd(i), de(sum[i]);
	for(register int j = 0; j < (1 << d); ++j) s[j] = add(s[j], sum[j]), sum[j] = 0;
}
int qry(int l, int r, int msk) {
	if(l > r) return 0;
	ll ans = 0;
	for(register int i = l; i <= r; ++i) if((a[i] & msk) == a[i]) ans += f[i];
	return ans % P;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> d;
	rep(i, 0, n) {
		string s; cin >> s;
		int &x = a[i] = 0;
		rep(j, 0, d) x = (x << 1) + (s[j] - '0');
	}
	rep(i, 0, pw(d)) s[i] = 1;
	rep(i, 0, n) { int &b = kuai[i] = i / B; ed[b] = i; }
	per(i, 0, n) st[kuai[i]] = i;
//	rep(i, 0, kuai[n - 1] + 1) dd(i), dd(st[i]), de(ed[i]);
	rep(i, 0, n) {
		int b = kuai[i];
		f[i] = add(s[a[i]], qry(st[b], i - 1, a[i]));
		if(i == ed[b] && i != n - 1) gao(b);
		//dd(i), de(f[i]);
	}
	int ans = 0;
	rep(i, 0, n) ans = add(ans, f[i]);
	cout << ans << endl;
	return 0;
}
