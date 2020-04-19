#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1010;

int n, m;
int a[N], b[N], p[N];
ll ans;

inline int F(int i) {
	int p = lower_bound(a + 1, a + 1 + m + 1, i) - a;
	return p;
}

inline int lcp(int i, int j) {
	if(i > j) swap(i, j); if(j > n) return 0;
	if(i == j) return n - i + 1;
	int p = F(i), q = F(j);
	int ans = 0;
	while(1) {
		if(i == a[p] && j == a[q]) {
			int h = min(a[p + 1] - i, a[q + 1] - j);
			ans += h;
			i += h, j += h; ++p, ++q;
			if(p > m || q > m) return ans;
		} else if(i != a[p] && j != a[q]) {
			int h = min(a[p] - i, a[q] - j);
			ans += h;
			i += h, j += h;
			if(p > m || q > m) return ans;
		} else {
			return ans;
		}
	}
}
bool cmp(int i, int j) {
	int h = lcp(i, j);
	int x = i + h, y = j + h;
	int o = (x > n ? -1 : (x == a[F(x)]));
	int t = (y > n ? -1 : (y == a[F(y)]));
	return o < t;
}

bool cmp2(int i, int j) {
	return b[i] > b[j];
}

struct Node {
	int i, len;
	Node() {}
	Node(int i) : i(i) { len = n - i + 1; }
	bool operator < (const Node &c) const {
		return cmp(i, c.i) > 0;
	}
};

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) cin >> a[i], b[i] = a[i] - a[i - 1] - 1, p[i] = i;
	b[m + 1] = n - a[m];
	a[m + 1] = n + 1;

	sort(p + 1, p + 1 + m, cmp2);

	ans = b[m + 1];
	set<Node> st;
	ll sum = 0;
	bool flag = 0;
	rep(i, 1, m + 1) {
		int k = b[p[i]];
		if(i < m) k -= b[p[i + 1]];
		else k -= -1;
		if(i == 1) {
			st.insert(Node(a[p[i]]));
		} else {
			auto pos = st.lower_bound(Node(a[p[i]]));
			if(pos == st.end()) {
				--pos;
				sum += n - a[p[i]] + 1 - lcp(a[p[i]], pos -> i);
			} else if(pos == st.begin()) {
				sum += pos -> len - lcp(pos -> i, a[p[i]]);
			} else {
				sum += pos -> len - lcp(pos -> i, a[p[i]]);
				auto tt = pos; --pos;
				sum += n - a[p[i]] + 1 - lcp(pos -> i, a[p[i]]);
				sum -= tt -> len - lcp(pos -> i, tt -> i);
			}
			st.insert(Node(a[p[i]]));
		}
		if(!k) continue;
		int t = n - (st.begin() -> i) + 1;
		ans += k * (t + sum);
		if(!flag) {
			flag = 1;
			ans -= t;
			ans += t + b[p[i]] - lcp(st.begin() -> i - b[p[i]], a[m] + 1);
		}
	}
	cout << ans << endl;
	return 0;
}
