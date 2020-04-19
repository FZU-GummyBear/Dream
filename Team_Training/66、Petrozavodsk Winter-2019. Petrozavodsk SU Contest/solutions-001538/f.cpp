#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double dbl;
typedef pair<int, int> pii;

#define mp make_pair
#define pb push_back

const dbl EPS = 1e-8;
const dbl INF = 1e18;
const int p1 = 795449;
const int p2 = 818569;
const int MAXN = 100;

bool doubleLess (dbl a, dbl b) {
	return (b - a) > EPS;
}
bool doubleEqual (dbl a, dbl b) {
	return abs (b - a) < EPS;
}
dbl sqr (dbl a) {
	return a * a;
}

struct Point {
	dbl x, y;
	Point () {}
	Point (dbl x, dbl y) : x (x), y (y) {}

	dbl dist (Point P) {
		return sqrt (sqr (x - P.x) + sqr (y - P.y));
	}
	dbl sqrDist (Point P) {
		return sqr (x - P.x) + sqr (y - P.y);
	}

	bool operator < (const Point &P) const {
		if (!doubleEqual (x, P.x))
			return doubleLess (x, P.x);
		return doubleLess (y, P.y);
	}
	bool operator == (const Point &P) const {
		return doubleEqual (x, P.x) && doubleEqual (y, P.y);
	}
	bool operator <= (const Point &P) const {
		return (*this) < P || (*this) == P;
	}
	Point operator + (const Point &P) const {
		return Point (x + P.x, y + P.y);
	}
	Point operator - (const Point &P) const {
		return Point (x - P.x, y - P.y);
	}
	Point operator * (const dbl &t) const {
		return Point (x * t, y * t);
	}
	dbl operator * (const Point &P) const {
		return x * P.x + y * P.y;
	}
	dbl operator ^ (const Point &P) const {
		return x * P.y - y * P.x;
	}

	friend istream & operator >> (istream &is, Point &P) {
		is >> P.x >> P.y;
		return is;
	}
	friend ostream & operator << (ostream &os, const Point &P) {
		os << P.x << ' ' << P.y;
		return os;
	}
};

struct Line {
	dbl A, B, C;
	Line () {}
	Line (dbl A, dbl B, dbl C) : A (A), B (B), C (C) {}
	Line (Point P, Point Q) : A (Q.y - P.y), B (P.x - Q.x), C (Q.x * P.y - P.x * Q.y) {}

	bool isCross (Line l) {
		return !doubleEqual (A * l.B, l.A * B);
	}
	Point cross (Line l) {
		return Point ((B * l.C - l.B * C) / (A * l.B - l.A * B), (l.A * C - A * l.C) / (A * l.B - l.A * B));
	}
	bool onLine (Point P) {
		return doubleEqual (A * P.x + B * P.y + C, 0);
	}
	int sign (Point P) {
		dbl res = A * P.x + B * P.y + C;
		if (doubleLess (res, 0)) return -1;
		if (doubleLess (0, res)) return 1;
		return 0;
	}

	bool operator == (const Line &l) const {
		return doubleEqual (A * l.B, B * l.B) && doubleEqual (A * l.C, C * l.A) && doubleEqual (B * l.C, C * l.B);
	}
};

struct Ray {
	Point O, v;
	Ray () {}
	Ray (Point O, Point v) : O (O), v (v) {}
	bool onRay (Point P) {
		Line l (O, O + v);
		if (!l.onLine (P))
			return false;
		return !doubleLess ((P.x - O.x) / v.x, 0) && !doubleLess ((P.y - O.y) / v.y, 0);
	}
};

struct Segment {
	Point A, B;
	Segment () {}
	Segment (Point A, Point B) : A (min (A, B)), B (max (A, B)) {}

	bool cross (Ray r, Point &P) {
		Line l1 (A, B), l2 (r.O, r.O + r.v);
		if (!l1.isCross (l2))
			return false;
		P = l1.cross (l2);
		return onSegment (P) && r.onRay (P);
	}
	bool onSegment (Point P) {
		Line l (A, B);
		if (!l.onLine (P))
			return false;
		return A <= P && P <= B;
	}
};

struct Comp {
	Point start;
	Comp () {}
	Comp (Point start) : start (start) {}
	bool operator () (const Point &A, const Point &B) const {
		return doubleLess (0, (A - start) ^ (B - start));
	}
};

struct Polygon {
	vector <Point> p;

	Polygon () {}
	Polygon (vector <Point> tmp) {
		p = tmp;
		sort (p.begin (), p.end ());
		sort (p.begin () + 1, p.end (), Comp (p[0]));
		p.pb (p[0]);
	}

	bool inPolygon (Point P) {
		for (int i = 1; i < (int)p.size (); i++)
			if (Segment (p[i - 1], p[i]).onSegment (P))
				return false;
		Ray r (P, Point (p1, p2));
		Point tt;
		int cnt = 0;
		for (int i = 1; i < (int)p.size (); i++)
			cnt += Segment (p[i - 1], p[i]).cross (r, tt);
		return cnt & 1;
	}

	dbl cross (Ray r) {
		Line l (r.O, r.O + r.v);
		vector <Point> pp;
		Point tt;

		for (int i = 1; i < (int)p.size (); i++) {
			if (Line (p[i - 1], p[i]) == l)
				return INF;
			if (Segment (p[i - 1], p[i]).cross (r, tt))
				pp.pb (tt);
		}
		sort (pp.begin (), pp.end ());
		pp.erase (unique (pp.begin (), pp.end ()), pp.end ());

		if ((int)pp.size () == 1)
			return INF;

		dbl res = INF;
		for (auto P : pp) {
			res = min (res, P.dist (r.O));
			//		cerr << P << '\n';
		}
		//cerr << endl;
		return res;
	}

	size_t size () {
		return p.size ();
	}
	Point & operator [] (int pos) {
		return p[pos];
	}
	friend istream & operator >> (istream &is, Polygon &p) {
		int n;
		vector <Point> pp;
		is >> n;
		pp.resize (n);
		for (int i = 0; i < n; i++)
			is >> pp[i];
		p = Polygon (pp);
		return is;
	}
};

int n, k;
Polygon p[MAXN];
Ray r[2];
dbl d[MAXN];

void load () {
	Point n;
	cin >> k;
	cin >> r[0].O >> r[1].O >> n >> n;
	n = r[0].O - r[1].O;
	n = Point (-n.y, n.x);
	r[0].v = r[1].v = n;
	cin >> ::n;
	for (int i = 0; i < ::n; i++) {
		vector <Point> P;
		int m;
		cin >> m;
		for (int i = 0; i < m; i++) {
			dbl x, y, z;
			cin >> x >> y >> z;
			if (doubleEqual (z, 0)) {
				P.pb (Point (x, y));
			}
		}
		p[i] = Polygon (P);
	}
	/*	for (int i = 0; i < ::n; i++) {
			cerr << p[i].size () << ":\n";
			for (int j = 0; j < (int) p[i].size (); j++) {
				cerr << p[i][j] << '\n';
			}
			cerr << endl;
		}
		cerr << "n == " << n << endl;    */
}

int id[MAXN];

bool cmp (int a, int b) {
	if (!doubleEqual (d[a], d[b]))
		return doubleLess (d[a], d[b]);
	return a < b;
}

void solve () {
	//cerr << "solve\n";
	fill (d, d + MAXN, INF);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++)
			d[i] = min (d[i], p[i].cross (r[j]));
	}
	for (int i = 0; i <= n; i++)
		id[i] = i;
	sort (id, id + n, cmp);
	/*cerr << "after sort\n";
	for (int i = 0; i < n; i++) {
		cerr << d[id[i]] << ' ';
	} */
	dbl ans = d[id[k]];
	if (doubleEqual (ans, INF))
		cout << "oo";
	else cout << ans;
}

int main () {
	ios_base::sync_with_stdio (false);
	cin.tie (NULL);
#ifdef LOCAL                        
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cout.precision (8);
	cout << fixed << showpoint;
	cerr.precision (8);
	cerr << fixed << showpoint;

	load ();
	solve ();
	return 0;
}