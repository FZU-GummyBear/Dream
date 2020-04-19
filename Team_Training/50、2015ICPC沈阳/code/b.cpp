#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 505, M = 2020;

int n;
bool vis[N];
char t[N][M];
int nt[N][M];
int ns[M];

void kmp(char *s, int *ns, char *t, int *nt) {
	int lens = strlen(s);
	int lent = strlen(t);
	nt[0] = -1;
	for(int i = 0, j = -1; i < lens; ++i) {
		while(j >= 0 && s[i] != t[j + 1]) j = nt[j];
		if(s[i] == t[j + 1]) ++j;
		ns[i] = j;
		if(j + 1 == lent) j = nt[j];
	}
}

bool check(int i, int j) {
	kmp(t[j], ns, t[i], nt[i]);
	int leni = strlen(t[i]);
	int lenj = strlen(t[j]);
	bool ans = 0;
	rep(k, 0, lenj) if(ns[k] == leni - 1) ans = 1;
	return ans;
}

int solve() {
	cin >> n;
	rep(i, 1, n + 1) {
		cin >> t[i];
		kmp(t[i] + 1, nt[i] + 1, t[i], nt[i]);
	}
	int ans = -1;
	rep(i, 1, n + 1) {
		rep(j, 1, i) if(!vis[j]) {
			if(check(j, i)) {
				vis[j] = 1;
			} else {
				ans = i;
				break;
			}
		}
	}
	return ans;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(ca, 1, T + 1) {
		memset(vis, 0, sizeof(vis));
		cout << "Case #" << ca << ": " << solve() << endl;
	}
	return 0;
}
