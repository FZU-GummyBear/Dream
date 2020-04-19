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
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(a) a.begin(), a.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e6 + 10;

int r1, r2, n, m, P, c[N], t;

inline int add(int a, int b) {
  if ((a += b) >= P) a -= P;
  return a;
}

inline int mul(int a, int b) {
  return 1ll * a * b % P;
}

struct mat{
  int a[5][5];
  mat() {memset(a, 0, sizeof(a));}
  mat operator * (const mat &c) {
    mat r;
    rep(i, 0, m)
      rep(k, 0, m) 
	rep(j, 0, m) r.a[i][j] = add(r.a[i][j], mul(a[i][k], c.a[k][j]));
    return r;
  }
} A, B, q1[N], q2[N], b[N];

inline void insert(mat &a) {
  if (r1 == -1) q1[++r1] = a;else q1[r1+1] = q1[r1] * a, r1++;
  b[r1] = a;
}

inline void del() {
  if (r2 == -1) {
    per(i, 0, r1+1) {
      if (r2 == -1) q2[++r2] = b[i];
      else q2[r2+1] = b[i] * q2[r2], r2++;
    }
    r1 = -1;
  }
  r2--;
}


int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  while (cin >> n >> m >> P) {
    rep(i, 0, m)
      rep(j, 0, m) cin >> A.a[i][j];
    rep(i, 0, m)
      rep(j, 0, m) cin >> B.a[i][j];
    rep(i, 1, n+1) cin >> c[i]; 
    t = 0; r1 = r2 = -1;
    rep(i, 1, n+1) {
	insert(A);
        while (t < c[i]) del(), t++;
        if (r1 >= 0 && r2 >= 0) A = q2[r2] * q1[r1] * B;
        else if (r1 >= 0) A = q1[r1] * B;
        else if (r2 >= 0) A = q2[r2] * B;
    }
    rep(i, 0, m) rep(j, 0, m) cout << A.a[i][j] << " \n"[j == m - 1];
  }
  return 0;
}
