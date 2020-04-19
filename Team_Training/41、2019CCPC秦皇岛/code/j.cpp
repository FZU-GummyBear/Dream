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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

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

const int N = 1e7 + 8;

int a, b, ns[N];
char str[N], s[N];

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> a >> b >> str;
	int len = strlen(str);
	int m = 0;
	per(i, 0, len) {
		if(str[i] == '.') break;
		s[m++] = str[i];
	}
	s[m] = '\0';
	kmp(s + 1, ns + 1, s, ns);
	ll ans = -9e18;
	rep(p, 0, m) {
		int l = p - ns[p];
		ans = max(ans, a * 1ll * (p + 1) - b * 1ll * l);
	}
	cout << ans << endl;
	return 0;
}
