// https://ac.nowcoder.com/acm/contest/view-submission?submissionId=41083028
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int MM = 1e9 + 7;
const double eps = 1e-8;
const int MAXN = 5e3 + 10;
const int MAXM = 5e6 + 10;

struct Pt{
	long long x, y;
};

bool operator < (const Pt & a, const Pt & b){
	if (a.x == b.x)
		return a.y < b.y;
	else
		return a.x < b.x;
}

bool operator == (const Pt & a, const Pt & b){
	return a.x == b.x && a.y == b.y;
}

inline long long operator * (const Pt & a, const Pt & b){
	return a.x * b.y - a.y * b.x;
}

inline long long operator % (const Pt & a, const Pt & b){
	return a.x * b.x + a.y * b.y;
}

inline Pt operator - (const Pt & a, const Pt & b){
	return (Pt){a.x - b.x, a.y - b.y};
}

inline Pt operator + (const Pt & a, const Pt & b){
	return (Pt){a.x + b.x, a.y + b.y};
}

long long sqr(long long x){
	return x * x;
}

inline double len(const Pt & a){
	return sqrt(sqr(a.x) + sqr(a.y));
}

long long absll(long long x){
	return x < 0 ? -x : x;
}

struct ppt{
	Pt u;
	int cnt;
};

int n;
vector<Pt> a;
vector<Pt> b, c;
int m;
ppt d[MAXN * 2];
int vis[MAXN];
ll four, three, qaq;

inline ll C4(ll x) { return x * (x - 1) / 2 * (x - 2) / 3 * (x - 3) / 4; }
inline ll C3(ll x) { return x * (x - 1) / 2 * (x - 2) / 3; }
inline ll C2(ll x) { return x * (x - 1) / 2; }

void gao(int idx) {
	b.clear(), c.clear();
	for (int i = 0; i < n; i++) if (i != idx) {
		if (a[i].y > a[idx].y || (a[i].y == a[idx].y && a[i].x > a[idx].x)) b.push_back(a[i] - a[idx]);
		else c.push_back(a[i] - a[idx]);
	}
	sort(b.begin(), b.end(), [](const Pt & a, const Pt & b){
			return a.x * b.y > a.y * b.x;
			});
	sort(c.begin(), c.end(), [](const Pt & a, const Pt & b){
			return a.x * b.y > a.y * b.x;
			});
	m = -1;
	if (b.size()) {
		m++;
		d[m].u = b[m];
		d[m].cnt = 1;
		for (int i = 1; i < b.size(); i++) {
			if (b[i].x * d[m].u.y == b[i].y * d[m].u.x) d[m].cnt++;
			else {
				m++;
				d[m].u = b[i];
				d[m].cnt = 1;
			}
		}
	}
	if (c.size()) {
		m++;
		d[m].u = c[0];
		d[m].cnt = 1;
		for (int i = 1; i < c.size(); i++) {
			if (c[i].x * d[m].u.y == c[i].y * d[m].u.x) d[m].cnt++;
			else {
				m++;
				d[m].u = c[i];
				d[m].cnt = 1;
			}
		}
	}
	m++;
	for (int i = 0; i < m; i++) {
		d[m + i] = d[i];
	}
	// cout << "===========================" << endl;
	// cout << idx << endl << a[idx].x << ' ' << a[idx].y << endl;
	// cout << b.size() << ' ' << c.size() << endl;
	// for (int i = 0; i < m; i++)
	//     cout << d[i].u.x << ' ' << d[i].u.y << ' ' << d[i].cnt << endl;
	for (int i = 0; i < m; i++) vis[i] = 0;
	for (int i = 0, j = 1, cnt = d[i].cnt; i < m; i++) {
		// j -> first equal or large than 180
		cnt -= d[i].cnt;
		if (j < i + 1) {
			cnt += d[j].cnt;
			j++;
		}
		while (j < i + m && (d[i].u * d[j].u) > 0) {
			cnt += d[j].cnt;
			j++;
		}
		int rm = n - 1 - d[i].cnt - cnt;
		if (j != i + m && (d[i].u * d[j].u) == 0) {
			rm -= d[j].cnt;
			if (j < m)
				vis[j] = 1;
		}
		else {
			if (d[i].cnt >= 3) four += C4(d[i].cnt + 1);
			if (d[i].cnt >= 2) three += C3(d[i].cnt + 1) * (n - d[i].cnt - 1);
		}
		// cout << "??? " << i << ' ' << j << ' ' << cnt << ' ' << rm << ' ' << n - 1 - cnt - rm << ' ' << vis[i] << endl;
		if (vis[i] == 0) qaq += 1ll * cnt * rm * (n - 1 - cnt - rm);
	}
	// cout << "!!!! " << four << ' ' << three << ' ' << qaq << endl;
}

void solve(){
	scanf("%d", &n);
	a.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", &a[i].x, &a[i].y);
	}
	four = three = qaq = 0;
	for (int i = 0; i < n; i++) {
		gao(i);
	}
	ll total = C4(n);
	total = total - four / 2  - three / 2;
	qaq -= three;
	ll ans = (qaq - 4 * total) / 2;
	// cout << four << ' ' << three << ' ' << total << ' ' << qaq << endl;
	printf("%lld\n", ans * (n - 4) / 2);
}


int main(){
	int T = 1;
	//  cin >> T;
	while(T--){
		solve();
	}
	return 0;
}
