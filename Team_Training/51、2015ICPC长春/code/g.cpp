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
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 111;

int sign(ll x) {
	if(x > 0) x = 1;
	if(x < 0) x = -1;
	return x;
}

struct P {
	ll x, y;
	P(ll x = 0, ll y = 0) : x(x), y(y) {}
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	ll len2() {
		return x * x + y * y;
	}
};

ll det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}
ll dot(P a, P b) {
	return a.x * b.x + a.y * b.y;
}
ll dot(P o, P a, P b) {
	return dot(a - o, b - o);
}

vector<P> ch(vector<P> ps) {
	int n = sz(ps); 
	sort(all(ps));
	vector<P> qs;
	for(int i = 0; i < n; qs.pb(ps[i++])) {
		while(sz(qs) > 1 && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
	}
	for(int i = n - 2, t = sz(qs); i >= 0; qs.pb(ps[i--])) {
		while(sz(qs) > t && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
	}
	qs.pop_back();
	return qs;
}

bool solve() {
	int n; cin >> n;
	vector<P> ps(n);
	rep(i, 0, n) cin >> ps[i].x >> ps[i].y;
	ps = ch(ps);
	if(sz(ps) != n) return 0;
	ll dis = (ps[1] - ps[0]).len2();
	rep(i, 0, n) {
		int j = (i + 1) % n;
		if((ps[j] - ps[i]).len2() != dis) return 0;
	}
	ll x = dot(ps[0], ps[1], ps[2]), y = det(ps[0], ps[1], ps[2]);
	rep(i, 0, n) {
		int j = (i + 1) % n;
		int k = (j + 1) % n;
		if(x != dot(ps[i], ps[j], ps[k]) || y != det(ps[i], ps[j], ps[k])) return 0;
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) {
		cout << (solve() ? "YES" : "NO") << endl;
	}
	return 0;
}
