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

const int N = 22;

string str[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};

struct Node { 
	string a, b;
	int c;
	void read() {
		cin >> a >> b;
		rep(i, 0, 12) if(str[i] == a) c = i * 40;
		int d = 0;
		rep(i, 0, sz(b)) {
			if('0' <= b[i] && b[i] <= '9') d = d * 10 + b[i] - '0';
		}
		c += d;
	}
	bool operator < (const Node &k) const {
		return c < k.c;
	}
};

int n;
Node nd[N], x;

void solve() {
	cin >> n;
	rep(i, 0, n) nd[i].read();
	x.read();
	sort(nd, nd + n);
	int p = n;
	rep(i, 0, n) if(x < nd[i]) {
		p = i; break;
	}
	if(p == n) {
		cout << "See you next year" << endl;
	} else {
		cout << nd[p].a << " " << nd[p].b << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}
