#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
//----


const int N = 1005;
vi g[N];
int m, u, v, n, match[N], q[N], L, R;
int pred[N], b[N], s, t, newb;
bool inq[N], inb[N], inp[N];

void push(int u) { q[R++] = u; inq[u] = 1;}

int pop() { return q[L++]; }

int LCA(int u,int v) {
	rep(i, 0, n) inp[i]=0;
	while(1) {
		u = b[u];
		inp[u] = 1;
		if (u == s) break;
		u = pred[match[u]];
	}
	while(1) {
		v = b[v];
		if (inp[v]) break;
		v = pred[match[v]];
	}
	return v;
}

void ResetTrace(int u) {
	int v;
	while(b[u] != newb) {
		v = match[u];
		inb[b[u]] = inb[b[v]] = 1;
		u = pred[v];
		if(b[u] != newb) pred[u] = v;
	}
}

void Blossom(int u,int v) {
	newb = LCA(u,v);
	rep(i, 0, n) inb[i] = 0;
	ResetTrace(u);
	ResetTrace(v);
	if(b[u] != newb) pred[u] = v;
	if(b[v] != newb) pred[v] = u;
	rep(i, 0, n) if (inb[b[i]]) {
		b[i] = newb;
		if (!inq[i]) push(i);
	}
}

bool Find(int u) {
	bool found = 0;
	rep(i, 0, n) pred[i] = -1, b[i] = i, inq[i] = 0;
	s = u, t=-1;
	L = R = 0;
	push(s);
	while(L < R) {
		int u = pop();
		per(i, 0, sz(g[u])) { 
			int v = g[u][i];
			if (b[u] != b[v] && match[u] != v)
				if(v == s || (match[v] >= 0 && pred[match[v]] >= 0))
					Blossom(u, v);
				else if(pred[v] == -1) {
					pred[v]=u;
					if (match[v] >= 0) push(match[v]);
					else return t = v, 1;
				}
		}
	}
	return found;
}
void AugmentPath() {
	int u = t, v, w;
	while(u >= 0) {
		v = pred[u];
		w = match[v];
		match[v] = u;
		match[u] = v;
		u = w;
	}
}

void Match() {
	rep(i, 0, n) match[i] = -1;
	rep(i, 0, n) if (match[i] == -1) if (Find(i)) AugmentPath();
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 0, m) {
		cin >> u >> v;
		u--; v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	Match();
	int cnt = 0;
	rep(i, 0, n) if (match[i] != -1) cnt++;
	cout << cnt / 2 << endl;
	rep(i, 0, n) cout << match[i] + 1 << " \n"[i == n-1];
	return 0;
}


