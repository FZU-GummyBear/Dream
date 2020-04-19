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

const int N = 10101;

int n, a[N];
bool vis[N];
void print() {
	rep(i, 1, n + 1) printf("%d", a[i]); printf("\n");
	fflush(stdout);
	char s[3]; scanf("%s", s);
	if(s[0] == '+') exit(0);
}

int main() {
	srand(time(0));
	scanf("%d", &n);
	if(n <= 200) {
		rep(i, 1, n + 1) {
			a[i - 1] = 0;
			a[i] = 1;
			print();
		}
	} else {
		int t = 180;
		per(i, 1, t+1) {
			a[1] = 1; 
			while (1) {
				bool ok = 1; int p;
				random_shuffle(a + 1, a + 1 + n);
				rep(i, 1, n+1) if (a[i]) {
					if (vis[i]) ok = 0; p = i;
					break;
				} 
				if (ok) {vis[p] = 1; break;}
			}
			print();
		}

		per(i, t+1, 201) {
			rep(j, 1, n + 1) a[j] = j <= 300;
			random_shuffle(a + 1, a + 1 + n);
			print();
		}
	}
	return 0;
}
