#include <bits/stdc++.h>
#define lsb(x) (x & (-x))
#define ll long long
#define ull unsigned long long
#define uint unsigned int
 
using namespace std;
 
int main() {
#ifdef HOME
    ifstream cin("A.in");
    ofstream cout("A.out");
#endif
    int t;
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
 
    cin >> t;
 
    while(t--) {
        int i, n, m1, m2;
        cin >> n >> m1 >> m2;
 
        struct edge {
            int x, y, k;
        };
        struct Edge {
            int nod, k;
            bool type;
        };
 
        vector < vector <Edge> > g(n + 1);
        vector <edge> e1, e2;
 
        for(i = 1; i <= m1; i++) {
            int l, r, k;
            cin >> l >> r >> k;
            e1.push_back({l, r, k});
        }
        for(i = 1; i <= m2; i++) {
            int l, r, k;
            cin >> l >> r >> k;
            e2.push_back({l, r, k});
        }
 
        vector <int> l(n + 1), r(n + 1);
        vector <bool> inq(n + 1);
        queue <int> Q;
 
        auto walk = [&](int x, Edge &y, int sz) {
            int yl = l[y.nod], yr = r[y.nod];
 
            if(y.type == 1) {
                if(x < y.nod) {
                    yl = max(yl, l[x]);
                    yr = min(yr, r[x] + y.k);
                }
                else {
                    yl = max(yl, l[x] - y.k);
                    yr = min(r[x], yr);
                }
            }
            else {
                if(x < y.nod) {
                    yl = max(yl, l[x] + y.k);
                }
                else {
                    yr = min(yr, r[x] - y.k);
                }
            }
 
            if(yl != l[y.nod] || yr != r[y.nod]) {
                l[y.nod] = yl;
                r[y.nod] = yr;
                if(inq[y.nod] == 0) {
                    inq[y.nod] = 1;
                    Q.push(y.nod);
                }
            }
 
            if(l[y.nod] > r[y.nod]) return 0;
            return 1;
        };
 
        auto check = [&](int sz) -> bool {
            for(int i = 0; i < n; i++) {
                l[i] = 0, r[i] = min(i, sz);
                g[i].clear();
            }
            l[n] = r[n] = sz;
            g[n].clear();
 
            for(auto &it : e1) {
                g[it.x - 1].push_back({it.y, it.k, 0});
                g[it.y].push_back({it.x - 1, it.k, 0});
            }
            for(auto &it : e2) {
                if(sz < it.k) return 1;
 
                g[it.x - 1].push_back({it.y, sz - it.k, 1});
                g[it.y].push_back({it.x - 1, sz - it.k, 1});
            }
            for(int i = 0; i < n; i++) {
                g[i].push_back({i + 1, 1, 1});
                g[i + 1].push_back({i, 1, 1});
            }
 
            while(Q.size()) {
                Q.pop();
            }
            for(i = n; i >= 0; i--) {
                Q.push(i);
                inq[i] = 1;
            }
 
            while(Q.size()) {
                int nod = Q.front();
                Q.pop(), inq[nod] = 0;
 
                for(auto &it : g[nod]) {
                    if(!walk(nod, it, sz)) {
                        return 1;
                    }
                }
            }
 
            bool ans = 0;
            for(i = 0; i < n && ans == 0; i++) {
                for(auto it : g[i]) {
                    if(it.nod > i) {
                        if(it.type == 0) {
                            if(l[it.nod] - l[i] < it.k) ans = 1;
                        }
                        else {
                            if(l[it.nod] - l[i] > it.k) ans = 1;
                        }
                    }
                }
            }
            return ans;
        };
 
        int res = -1;
        for(int step = 1 << 11; step; step >>= 1) {
            if(res + step <= n && check(res + step)) {
                res += step;
            }
        }
 
        cout << res + 1 << "\n";
    }
 
    return 0;
}
