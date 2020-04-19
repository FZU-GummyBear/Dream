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

struct Node {
	int i;
	bool operator < (const Node &c) const {
		printf("? %d %d\n", i, c.i);
		fflush(stdout);
		char s[4]; scanf("%s", s);
		return s[0] == '>';
	}
};

const int N = 222;

Node nd[N];

void solve() {
	int n; scanf("%d", &n);
	rep(i, 1, n * 2 + 1) nd[i].i = i;
	srand(time(0));
	random_shuffle(nd + 1, nd + 1 + 2 * n);
	nth_element(nd + 1, nd + n, nd + 1 + 2 * n);
	printf("!\n"); fflush(stdout);
}

int main() {
	int T; scanf("%d", &T);
	while(T--) solve();
	return 0;
}
