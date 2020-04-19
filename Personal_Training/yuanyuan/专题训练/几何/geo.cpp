#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<iomanip>
#include<assert.h>
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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 202020;
const db eps = 1e-6, pi = acos(-1.);

int sign(db x) { return (x > eps) - (x < -eps); }
struct P {
  db x, y;
  P() {}
  P(db x, db y) : x(x), y(y) {}
  void read() { cin >> x >> y; }
  void print() { cout << x << " " << y << endl; }
  P operator + (const P &c) const { return P(x + c.x, y + c.y); }
  P operator - (const P &c) const { return P(x - c.x, y - c.y); }
  P operator * (const db &c) const { return P(x * c, y * c); }
  P operator / (const db &c) const { return P(x / c, y / c); }
  bool operator < (const P &c) const {
    if(x != c.x) return x < c.x;
    return y < c.y;
  }
  int quad() const { return sign(y) > 0 || (sign(y) == 0 && sign(x) >= 0); }
  P rot90() { return P(-y, x); }
  P rot(db a) { return P(cos(a) * x - sin(a) * y, cos(a) * y + sin(a) * x); }
  db len2() { return x * x + y * y; }
  db len() { return sqrt(len2()); }
  P norm() { return *this / len(); }
};
struct P3 {
  db x, y, z;
  P3() {}
  P3(db x, db y, db z) : x(x), y(y), z(z) {}
  void read() { cin >> x >> y >> z; }
  P3 operator + (const P3 &c) const { return P3(x + c.x, y + c.y, z + c.z); }
  P3 operator - (const P3 &c) const { return P3(x - c.x, y - c.y, z - c.z); }
  P3 operator * (const db &c) const { return P3(x * c, y * c, z * c); }
  P3 operator / (const db &c) const { return P3(x / c, y / c, z / c); }
  db len2() { return x * x + y * y + z * z; }
  db len() { return sqrt(len2()); }
};
db det(P a, P b) { return a.x * b.y - a.y * b.x; }
db dot(P a, P b) { return a.x * b.x + a.y * b.y; }
db det(P o, P a, P b) { return det(a - o, b - o); }
db dot(P o, P a, P b) { return dot(a - o, b - o); }
db rad(P p1, P p2) { return atan2l(det(p1, p2), dot(p1, p2)); }
struct O {
  P o; db r;
  O() {}
  O(P o, db r) : o(o), r(r) {}
  void read() {
    o.read(); cin >> r;
  }
};
struct L {
  P a, b;
  L() {}
  L(P a, P b) : a(a), b(b) {}
  L(db a, db b, db c) {
    if(sign(a)==0) {
      this->a=P(0,-c/b);this->b=P(sign(b),-c/b);
    } else if(sign(b)==0) {
      this->a=P(-c/a,0);this->b=P(-c/a,-sign(a));
    } else {
      if(sign(c)!=0) {
	int x=sign(c)*sign(det(P(-c/a,0), P(0,-c/b)));
	if(x==1) this->a=P(-c/a,0),this->b=P(0,-c/b);
	else this->a=P(0,-c/b),this->b=P(-c/a,0);
      } else {
	//    y>=-a/b*x    b>0    (0,0)->(1,-a/b)
	//    y<=-a/b*x    b<0    (0,0)->(-1,a/b)
	this->a=P(0,0);this->b=P(sign(b),sign(b)*(-a/b));
      }
    }
  }
  bool includer(const P &p) const { return sign(det(b - a, p - a)) > 0; }
  // 向内（右手方向）推
  L push(db len) {
    P det = (b - a).rot90().norm() * len;
    return L(a + det, b + det);
  }
};
bool tanCP(O &c, P &p0, P &p1, P &p2) {
  db x = (p0 - c.o).len2(), d = x - c.r * c.r;
  if(d < eps) return 0;
  P p = (p0 - c.o) * (c.r * c.r / x);
  P det = ((p0 - c.o) * (-c.r * sqrt(d) / x)).rot90();
  p1 = c.o + p + det;
  p2 = c.o + p - det;
  return 1;
}
db disToL(L l, P p) {
  return fabs(det(l.a, p, l.b) / (l.b - l.a).len());
}
db disToS(L l, P p) {
  return sign(dot(l.a, p, l.b)) * sign(dot(l.b, p, l.a)) == 1 ? disToL(l, p) : min((p - l.a).len(), (p - l.b).len());
}
P isLL(L l1, L l2) {
  db s1 = det(l2.b - l2.a, l1.a - l2.a);
  db s2 = -det(l2.b - l2.a, l1.b - l2.a);
  return (l1.a * s2 + l1.b * s1) / (s1 + s2);
}
// ax + by + c = 0
P isLL(L l, db a, db b, db c) {
  db u = a * l.a.x + b * l.a.y + c;
  db v = -(a * l.b.x + b * l.b.y + c);
  return (l.a * v + l.b * u) / (u + v);
}
P isLL(db a0, db b0, db c0, db a1, db b1, db c1) {
  db d = a0 * b1 - a1 * b0;
  return P(b0 * c1 - b1 * c0, a1 * c0 - a0 * c1) / d;
}
bool isCL(O a, L l, P &p1, P &p2) {
  db x = dot(l.a - a.o, l.b - l.a);
  db y = (l.b - l.a).len2();
  db d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
  if(sign(d) < 0) return 0;
  d = max(d, 0.);
  P p = l.a - ((l.b - l.a) * (x / y)), det = (l.b - l.a) * (sqrt(d) / y);
  p1 = p - det, p2 = p + det; // dir : l.a -> l.b
  return 1;
}
db areaCT(db r,P s,P t) { // 求圆与三角形交面积，需要除2
  P p1, p2;
  bool f = isCL(O(P(0, 0), r), L(s, t), p1, p2);
  if(!f) return r * r * rad(s, t);
  bool b1 = sign(s.len2() - r * r) == 1 , b2 = sign(t.len2() - r * r) == 1;
  if(b1 && b2) {
    if(sign(dot(s - p1, t - p1)) <= 0 && sign(dot(s - p2, t - p2) <= 0))
      return r * r * (rad(s, p1) + rad(p2, t)) + det(p1, p2);
    else return r * r * rad(s, t);
  } else if(b1) return r * r * rad(s, p1) + det(p1, t);
  else if(b2) return r * r * rad(p2, t) + det(s, p2);
  return det(s, t);
}
db areaCPoly(O c, vector<P> p) { // 求圆与多边形交面积
  int n = sz(p);
  db ans = 0;
  rep(i, 0, n) {
    P u = p[i], v = p[(i + 1) % n];
    ans += areaCT(c.r, u - c.o, v - c.o);
  }
  return fabs(ans) / 2;
}
vector<P> convexHull(vector<P> ps) {
  int n = sz(ps); if(n <= 1) return ps;
  sort(all(ps));
  vector<P> qs;
  for(int i = 0; i < n; qs.pb(ps[i++])) {
    while(sz(qs) > 1 && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
  }
  for(int i = n - 2, t = sz(qs); i >= 0; qs.pb(ps[i--])) {
    while(sz(qs) > t && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
  }
  qs.pop_back(); return qs;
}
// sqrt((a ^ 2 + b ^ 2 + c ^ 2 + 4 * sqrt(3) * area) / 2)
// 如果有重点，大于 2 的直接用模拟退火法
P fermat(vector<P> p) {
  int n = sz(p); assert(n);
  if(n == 1) return p[0];
  if(n == 2) return (p[0] + p[1]) / 2;
  if(n == 3) {
    db a[3];
    rep(i, 0, 3) a[i] = (p[(i + 2) % 3] - p[(i + 1) % 3]).len();
    rep(i, 0, 3) {
      int j = (i + 1) % 3, k = (i + 2) % 3;
      if(sign(a[i] * a[i] - a[j] * a[j] - a[k] * a[k] - a[j] * a[k]) >= 0) return p[i];
    }
    if(det(p[0], p[1], p[2]) < 0) swap(p[1], p[2]);
    P q1 = (p[2] - p[0]).rot(pi / 3) + p[0]; 
    P q2 = (p[0] - p[1]).rot(pi / 3) + p[1];
    return isLL(L(q1, p[1]), L(q2, p[2]));
  }
  auto Rand = [&] () { return rand() % 10000 / 5000 * pi; };
  P ans(0, 0); rep(i, 0, n) ans = ans + p[i]; ans = ans / n;
  db len = 0; rep(i, 0, n) len += (ans - p[i]).len();
  db t = 10000; // modify
  while(t > eps) {
    db ang = Rand();
    P np(ans.x + t * sin(ang), ans.y + t * cos(ang));
    db k = 0; rep(i, 0, n) k += (np - p[i]).len();
    if(sign(len - k) > 0) ans = np, len = k;
    t *= 0.999;
  }
  return ans;
}
P3 MinSphere(vector<P3> p) {
  int n = sz(p); assert(n);
  db t = 1; P3 ans(0, 0, 0);
  rep(i, 0, n) ans = ans + p[i]; ans = ans / n;
  while(t > eps) {
    int j = -1; db ret = -1;
    rep(i, 0, n) {
      db tmp = (p[i] - ans).len();
      if(ret < tmp) ret = tmp, j = i;
    }
    ans = ans + (p[j] - ans) * t;
    t *= 0.999;
  }
  return ans;
}
struct Mat {
  db a[4][4];
  void set() { rep(i, 0, 4) rep(j, 0, 4) a[i][j] = 0; }
  void e() { rep(i, 0, 4) a[i][i] = 1; }
  Mat operator * (const Mat &c) {
    Mat r; r.set();
    rep(i, 0, 4) rep(j, 0, 4) rep(k, 0, 4) r.a[i][j] += a[i][k] * c.a[k][j];
    return r;
  }
};
Mat kpow(Mat a, int b) {
  Mat r; r.set(); r.e();
  while(b) {
    if(b & 1) r = r * a;
    a = a * a;
    b >>= 1;
  }
  return r;
}
// 平移，以下矩阵均为左乘
Mat translate(db tx, db ty, db tz) {
  db p[4][4] = {
    1, 0, 0, tx, 
    0, 1, 0, ty,
    0, 0, 1, tz,
    0, 0, 0, 1};
  Mat r; rep(i, 0, 4) rep(j, 0, 4) r.a[i][j] = p[i][j]; return r;
}
// 缩放
Mat scale(db a, db b, db c) {
  db p[4][4] = {
    a, 0, 0, 0,
    0, b, 0, 0,
    0, 0, c, 0,
    0, 0, 0, 1};
  Mat r; rep(i, 0, 4) rep(j, 0, 4) r.a[i][j] = p[i][j]; return r;
}
// 绕 s 为轴旋转 a 度，右手方向
Mat rotate(P3 s, db a) {
  db l = s.len(), x = s.x / l, y = s.y / l, z = s.z / l, si = sin(a), co = cos(a);
  db p[4][4] = {
    co + (1 - co) * x * x, (1 - co) * x * y - si * z, (1 - co) * x * z + si * y, 0,
    (1 - co) * y * x + si * z, co + (1 - co) * y * y, (1 - co) * y * z - si * x, 0,
    (1 - co) * z * x - si * y, (1 - co) * z * y + si * x, co + (1 - co) * z * z, 0,
    0, 0, 0, 1};
  Mat r; rep(i, 0, 4) rep(j, 0, 4) r.a[i][j] = p[i][j]; return r;
}

void solve() {
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  cout << setiosflags(ios::fixed);
  cout << setprecision(10);
  solve();
  return 0;
}
