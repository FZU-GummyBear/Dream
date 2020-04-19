#include<iostream>
#include<string>
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

const int N = 23;

char s[][N] = {
"         _",
"       _/g\\_",
"     _/ \\_/ \\_",
"   _/e\\_/m\\_/ \\_",
" _/ \\_/ \\_/ \\_/ \\_",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/C\\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/C\\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/C\\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/C\\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/C\\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/C\\_/ \\_/ \\_/ \\_/",
"/ \\_/ \\_/ \\_/ \\_/ \\",
"\\_/C\\_/ \\_/ \\_/ \\_/",
"  \\_/ \\_/G\\_/ \\_/",
"    \\_/ \\_/ \\_/",
"      \\_/ \\_/",
"        \\_/"};

int dy[] = {17, 18, 19, 20, 21, 20, 19, 18, 17};
int dx[] = {1, 3, 5, 7, 9, 11, 13, 15, 17};

bool iss(char s) { return 'a' <= s && s <= 'z'; }
bool isb(char s) { return 'A' <= s && s <= 'Z'; }
bool isl(char s) { return iss(s) || isb(s); }

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  while(cin >> n) {
    if(!n) break;
    rep(i, 0, N) rep(j, 0, N) if(isl(s[i][j])) s[i][j] = ' ';
    rep(i, 0, n) {
      string s1, s2; cin >> s2 >> s1;
      int x = s2[0] - 'A', y = 0;
      rep(j, 1, sz(s2)) y = y * 10 + s2[j] - '0';
      s[dy[x] - y * 2][dx[x]] = s1[0];
    }
    rep(i, 0, N) {
      string t = s[i];
      cout << t << endl;
    }
  }
  return 0;
}
