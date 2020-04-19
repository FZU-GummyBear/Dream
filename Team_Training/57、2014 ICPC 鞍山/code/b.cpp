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

const int N = 5050;

struct Node {
	int u; ll ans;
	Node(int u = 0, ll ans = 0) : u(u), ans(ans) {}
}nd[N];

int n, top, at;

int calc(string &s) {
	if(s[0] == 'A') return 1;
	if(s[0] == 'R') return 4;
	if(s[0] == 'P') return 5;
	if(s[0] == 'T') return 7;
	if(s[0] == 'U') return 8;
	if(s[1] == 'l') return 2;
	if(s[2] == 'a') return 3;
	return 6;
}

void solve() {
	cin >> n; top = at = 0;
	rep(i, 0, N) nd[i].ans = 0;
	int ca = 0;
	while(n--) {
		string str; cin >> str; int o = calc(str);
		ll x = 0; if(o != 5 && o != 8) cin >> x;
		cout << "Operation #" << ++ca << ": ";
		if(o == 1) {
			bool ok = 1;
			rep(i, 1, top + 1) if(nd[i].u == x) ok = 0;
			if(ok) {
				nd[++top] = Node(x, 0);
				cout << "success." << endl;
			} else {
				cout << "same priority." << endl;
			}
		} else if(o == 2) {
			bool ok = 0; ll ans; int ind;
			rep(i, 1, top + 1) if(nd[i].u == x) ok = 1, ans = nd[i].ans, ind = i;
			if(ok) {
				cout << "close " << x << " with " << ans << "." << endl;
				if(at) {
					if(at == ind) {
						at = 0;
					} else if(at > ind) --at;
				}
				int k = 0;
				rep(i, 1, top + 1) if(nd[i].u != x) nd[++k] = nd[i];
				top = k;
			} else {
				cout << "invalid priority." << endl;
			}
		} else if(o == 3) {
			if(at || top) {
				cout << "success." << endl;
				if(at) { nd[at].ans += x;
				} else { nd[1].ans += x; }
			} else {
				cout << "empty." << endl;
			}
		} else if(o == 4) {
			if(1 <= x && x <= top) {
				cout << "success." << endl;
				if(at) {
					if(at == x) { at = 1;
					} else if(at < x) ++at;
				}
				Node t = nd[x];
				per(i, 1, x) nd[i + 1] = nd[i];
				nd[1] = t;
			} else {
				cout << "out of range." << endl;
			}
		} else if(o == 5) {
			if(top) {
				cout << "success." << endl;
				int x = 0;
				rep(i, 1, top + 1) if(!x || nd[i].u > nd[x].u) x = i;
				if(at) {
					if(at == x) at = 1;
					else if(at < x) ++at;
				}
				Node t = nd[x];
				per(i, 1, x) nd[i + 1] = nd[i];
				nd[1] = t;
			} else {
				cout << "empty." << endl;
			}
		} else if(o == 6) {
			int t = 0;
			rep(i, 1, top + 1) if(nd[i].u == x) t = i;
			if(t) {
				cout << "success." << endl;
				if(at) {
					if(at == t) { at = 1;
					} else if(at < t) ++at;
				}
				Node tt = nd[t];
				per(i, 1, t) nd[i + 1] = nd[i];
				nd[1] = tt;
			} else {
				cout << "invalid priority." << endl;
			}
		} else if(o == 7) {
			int t = 0;
			rep(i, 1, top + 1) if(nd[i].u == x) t = i;
			if(t) {
				cout << "success." << endl;
				at = t;
			} else {
				cout << "invalid priority." << endl;
			}
		} else {
			if(at) {
				cout << "success." << endl;
				at = 0;
			} else {
				cout << "no such person." << endl;
			}
		}
		/*
		dd(str), de(x);
		de(at);
		rep(i, 1, top + 1) dd(nd[i].u), de(nd[i].ans);
		cout << endl;
		*/
	}
	if(at) {
		int i = at;
		if(nd[i].ans) 
			cout << "Bye " << nd[i].u << ": " << nd[i].ans << endl;
	}
	rep(i, 1, top + 1) if(nd[i].ans && i != at) 
		cout << "Bye " << nd[i].u << ": " << nd[i].ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
