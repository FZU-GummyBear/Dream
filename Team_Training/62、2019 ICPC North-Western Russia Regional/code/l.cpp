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

const int N = 202020;

int sa[N], h[N];
int fz = 0, fm = 1;

void upd(int a, int b) {
	if(a * 1ll * fm > b * 1ll * fz) fz = a, fm = b;
}

void solve(int l, int r) {
	if(l >= r) return ;
	int m = l + r >> 1;
	solve(l, m); solve(m + 1, r);
	int ml = N, mr = N, j = m;
	multiset<int> st;
	per(i, l, m + 1) {
		while(j + 1 <= r && min(mr, h[j + 1]) >= ml) ++j, st.insert(sa[j]), mr = min(mr, h[j]);
		if(sz(st)) {
			auto p = st.lower_bound(sa[i]);
			if(p != st.end()) {
				upd(min(ml, mr), abs(sa[i] - *p));
			}
			if(p != st.begin()) {
				--p;
				upd(min(ml, mr), abs(sa[i] - *p));
			}
		}
		ml = min(ml, h[i]);
	}
	ml = mr = N; int i = m + 1, tml = ml;
	st.clear();
	rep(j, m + 1, r + 1) {
		mr = min(mr, h[j]);
		while(l <= i - 1 && ml >= mr) --i, st.insert(sa[i]), tml = ml, ml = min(ml, h[i]);
		if(sz(st)) {
			auto p = st.lower_bound(sa[j]);
			if(p != st.end()) {
				upd(min(tml, mr), abs(sa[j] - *p));
			}
			if(p != st.begin()) {
				--p;
				upd(min(tml, mr), abs(sa[j] - *p));
			}
		}
	}
}

namespace Doubling {
	int t[N], wa[N], wb[N];
	void sort(int *x, int *y, int n, int m) {
		rep(i, 0, m) t[i] = 0;
		rep(i, 0, n) t[x[y[i]]]++;
		rep(i, 1, m) t[i] += t[i - 1];
		per(i, 0, n) sa[--t[x[y[i]]]] = y[i];
	}
	bool cmp(int *x, int a, int b, int d) { return x[a] == x[b] && x[a + d] == x[b + d]; }
	void da(int *s, int n, int m) {
		int *x = wa, *y = wb;
		rep(i, 0, n) x[i] = s[i], y[i] = i;
		sort(x, y, n, m);
		for(int j = 1, p = 1; p < n; m = p, j <<= 1) {
			p = 0; rep(i, n - j, n) y[p++] = i;
			rep(i, 0, n) if(sa[i] >= j) y[p++] = sa[i] - j;
			sort(x, y, n, m);
			swap(x, y); p = 1; x[sa[0]] = 0;
			rep(i, 1, n) x[sa[i]] = cmp(y, sa[i], sa[i - 1], j) ? p - 1 : p++;
		}
	}
	void cal_h(int *s, int n, int *rk) {
		int j, k = 0;
		for(int i = 1; i <= n; ++i) rk[sa[i]] = i;
		for(int i = 0; i < n; h[rk[i++]] = k) for(k && --k, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k); 
	}
};
struct DA {
	static const int N = ::N;
	int p[19][N], rk[N], in[N], Log[N], n;
	void build() {
		Doubling::da(in, n + 1, 300);
		Doubling::cal_h(in, n, rk);
	}
}da;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	string s; cin >> s;
	rep(i, 0, sz(s)) da.in[i] = s[i] - 'a' + 1;
	da.in[sz(s)] = 0;
	da.n = sz(s);
	da.build();
	/*
	rep(i, 1, sz(s) + 1) {
		dd(i), dd(h[i]), dd(sa[i]);
		rep(j, sa[i], sz(s)) cout << s[j]; cout << endl;
	}*/
//	solve(1, 6);
	solve(1, sz(s));
	fz += fm;
	int d = __gcd(fz, fm);
	fz /= d, fm /= d;
	cout << fz << "/" << fm << endl;
	return 0;
}
