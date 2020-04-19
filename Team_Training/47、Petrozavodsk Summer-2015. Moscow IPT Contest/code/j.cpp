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

deque<int> q;
string s;
int n;
int ask(int u, int v) {
	cout << "? " << u << " " << v << endl;
	fflush(stdout);
	cin >> s;
	return s[0] == 'A';
}

int main() {
	cin >> n;
	q.push_back(1);
	rep(i, 2, n+1) {
		int o1 = ask(q.back(), i);
		if (o1) {
			q.push_back(i);
			int o2 = ask(q.front(), i);
			if (o2) q.push_back(q.front()), q.pop_front();
		}else {
			q.push_front(q.back()); q.pop_back();
			int o2 = ask(q.back(), i);
			if (o2) q.push_back(i);
			else q.push_front(i);
		}
	}
	cout << "!";
	q.push_front(q.back()); q.pop_back();
	rep(i, 0, sz(q)) cout << " " << q[i];
	cout << endl;
	fflush(stdout);
	return 0;
}
