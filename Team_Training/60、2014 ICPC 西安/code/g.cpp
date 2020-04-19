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

const int M = 26, N = 505050;

struct PAM {
	int s[N], len[N], next[N][M], fail[N], cnt[N][3], last, n, p, cur, now, str_cnt, d0; ll ans;
	inline int newnode(int _l) {
		memset(next[p], 0, sizeof(next[p]));
		memset(cnt[p], 0, sizeof(cnt[p]));
		len[p] = _l; return p++;
	}
	inline void init() {
		newnode(p = 0);
		newnode(s[0] = -1);
		fail[last = n = 0] = 1;
		str_cnt = 0; d0 = -1;
	}
	inline int getfail(int x) {
		for( ; s[n - len[x] - 1] != s[n]; x = fail[x]); 
		return x; 
	}
	inline void add(int c) {
		if(c < 0) {
			s[++n] = c;
			last = 1;
			return ;
		}
		c -= 'a', s[++n] = c, cur = getfail(last);
		if(!next[cur][c]) {
			now = newnode(len[cur] + 2);
			fail[now] = next[getfail(fail[cur])][c];
			next[cur][c] = now;
		}
		last = next[cur][c], cnt[last][str_cnt]++; 
	}
	inline void insert(char s[], int _n = 0) {
		if(str_cnt) add(--d0); 
		if(!_n) _n = strlen(s);
		rep(i, 0, _n) add(s[i]);
		++str_cnt;
	}
	ll count() {
		per(i, 0, p) rep(j, 0, str_cnt) cnt[fail[i]][j] += cnt[i][j];
		ll ans = 0;
		rep(i, 2, p) ans += cnt[i][0] * 1ll * cnt[i][1];
		return ans;
	}
}pam;

char s[N], t[N];

ll solve() {
	pam.init();
	cin >> s >> t;
	pam.insert(s);
	pam.insert(t);
	return pam.count();
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) cout << "Case #" << i << ": " << solve() << endl;
	return 0;
}
