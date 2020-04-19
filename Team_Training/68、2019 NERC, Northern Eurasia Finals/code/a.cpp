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
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 2e5 + 10;

struct node{
	ll t, r;
	node(ll t = 0, ll r = 0) :t(t), r(r){}
	bool operator < (const node & b) const {
		if (t != b.t) return t > b.t;
		return r < b.r;
	}
};

priority_queue<node> A;
set<pair<ll, ll> > S;
int n;
pair<pair<ll, ll>, ll> a[N];
ll now, ans, r1, r2, t1, l, r, t;
int p;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) cin >> a[i].fi.fi >> a[i].fi.se >> a[i].se;
	sort(a+1, a+n+1);
	rep(i, 1, n+1) {
		l = a[i].fi.fi; r = a[i].fi.se; t = a[i].se;
		S.insert(mp(l + t, i));
	} 
	now = 0; p = 1;
	while (1) {
		//dd(now);
		while (p <= n && a[p].fi.fi <= now) {
			S.erase(mp(a[p].fi.fi + a[p].se, p));
			A.push(node(a[p].se, a[p].fi.se));
			p++;
		}
		while (!A.empty() && now + A.top().t > A.top().r) A.pop();
		if (A.empty() && S.empty()) break;
		if (A.empty()) t1 = r1 = pw(61); else t1 = A.top().t, r1 = A.top().r;
		if (S.empty()) r2 = pw(61); else r2 = (*S.begin()).fi;
		if (now + t1 >= r2) now = r2, ans++;
		else {
			//dd(t1), dd(r1), dd(r2), de(now);
			ll x = (min(r1, r2) - now) / t1;
			ans += x;
			now += t1 * x;
		}
	}
	cout << ans << endl;
	return 0;
}
