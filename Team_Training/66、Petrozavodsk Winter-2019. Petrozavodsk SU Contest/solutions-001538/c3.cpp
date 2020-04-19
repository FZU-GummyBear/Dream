#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define N 1000 + 5
#define D 200000 + 5
#define M 1000000 + 5
#define Q 2000000 + 5
#define SZ 4194304 + 5
#define ls(x) x << 1
#define rs(x) x << 1 | 1

const int Fx[4][2] = {{0, -1}, {0, 1}, {1, -1}, {1, 1}};
int n, d, e, sz, ans, Id[N][N], _Id[N][N], L[N], R[N], S[3], T[3], E[M][2], q[Q][2];
int Last[M], Fa[D], Height[D];
char s[N][N];
vector<int> Vec[SZ];

inline bool In(int x, int y)
{
	return (1 <= x && x < 4 * n && L[x] < y && y < R[x]);
}

inline bool Hit(int x, int y)
{
	if (x == 2 && y == 2 * n)
		return true;
	return In(x, y) && Id[x][y] != 0;
}

inline bool IsQuery(int x, int y)
{
	return In(x, y) && _Id[x][y] != 0;
}

void Read()
{
	// freopen("C.in", "r", stdin);
	scanf("%d\n", &n);
	for (int i = 1; i <= n; i ++)
		L[i] = 2 * (n - i + 1);
	for (int i = n + 1; i <= 3 * n; i ++)
		L[i] = 1;
	for (int i = 3 * n + 1; i < 4 * n; i ++)
		L[i] = 1 + 2 * (i - 3 * n);
	for (int i = 1; i < 4 * n; i ++)
		R[i] = 4 * n - L[i];
	for (int i = 1; i < 4 * n; i ++)
		fgets(s[i] + 1, N, stdin);
	for (int i = 2; i < 4 * n; i ++)
		for (int j = L[i] + 1; j < R[i]; j ++)
			if (Hit(i, j) || Hit(i - 1, j - 2) || Hit(i - 1, j + 2))
			{
				Id[i][j] = ++ d;
				if (s[i][j] != ' ')
				{
					int type = (s[i][j] >= 'a' ? 1 : 0);
					int x = s[i][j] - (type ? 'a' : 'A');
					type ? (S[x] = d) : (T[x] = d);
				}
			}
	for (int i = 2; i < 4 * n; i ++)
		for (int j = L[i] + 1; j < R[i]; j ++)
			if (!Hit(i, j) && s[i][j] != '@')
			{
				if ((j + 1 & 1) && Hit(i - 1, j) &&  Hit(i + 1, j))
				{
					_Id[i][j] = ++ e;
					E[e][0] = Id[i - 1][j], E[e][1] = Id[i + 1][j];
				}
				else if (j & 1)
				{
					bool flag = Hit(i, j - 1);
					if (flag && Hit(i - 1, j + 1))
					{
						_Id[i][j] = ++ e;
						E[e][0] = Id[i][j - 1], E[e][1] = Id[i - 1][j + 1];
					}
					else if (!flag && Hit(i - 1, j - 1))
					{
						_Id[i][j] = ++ e;
						E[e][0] = Id[i][j + 1], E[e][1] = Id[i - 1][j - 1];
					}
				}
			}
	for (int j = 2; j < 4 * n; j += 2)
		for (int i = 1; i < 4 * n; i ++)
			if (IsQuery(i, j))
			{
				for (int k = 0; k < 4; k ++)
				{
					int x = i + Fx[k][0], y = j + Fx[k][1];
					if (IsQuery(x, y))
					{
						sz ++;
						q[sz][0] = _Id[i][j], q[sz][1] = _Id[x][y];
					}
				}
			}
	for (int j = 1; j < 4 * n; j += 2)
		for (int i = 1; i < 4 * n; i ++)
			if (IsQuery(i, j) && IsQuery(i + 1, j))
			{
				sz ++;
				q[sz][0] = _Id[i][j], q[sz][1] = _Id[i + 1][j];
			}
}

void Add(int x, int l, int r, int s, int t, int id)
{
	if (l == s && r == t)
	{
		Vec[x].push_back(id);
		return ;
	}
	int mid = l + r >> 1;
	if (t <= mid)
		Add(ls(x), l, mid, s, t, id);
	else if (s > mid)
		Add(rs(x), mid + 1, r, s, t, id);
	else Add(ls(x), l, mid, s, mid, id), Add(rs(x), mid + 1, r, mid + 1, t, id);
}

void Build()
{
	for (int i = 1; i <= sz; i ++)
	{
		if (Last[q[i][0]] + 1 < i)
			Add(1, 1, sz, Last[q[i][0]] + 1, i - 1, q[i][0]);
		if (Last[q[i][1]] + 1 < i)
			Add(1, 1, sz, Last[q[i][1]] + 1, i - 1, q[i][1]);
		Last[q[i][0]] = Last[q[i][1]] = i;
	}
	for (int i = 1; i <= e; i ++)
		if (Last[i] + 1 <= sz)
			Add(1, 1, sz, Last[i] + 1, sz, i);
	for (int i = 1; i <= d; i ++)
		Fa[i] = i, Height[i] = 1;
}

inline int Find(int x)
{
	for (; x != Fa[x]; x = Fa[x]) ;
	return x;
}

void dfs(int x, int l, int r)
{
	struct RecordInfo
	{
		int u, v, h_v;
		RecordInfo(int u, int v, int h_v) : u(u), v(v), h_v(h_v) {}
	};
	vector<RecordInfo> records;
	for (int edge : Vec[x])
	{
		int u = Find(E[edge][0]), v = Find(E[edge][1]);
		if (u == v) continue ;
		if (Height[u] > Height[v])
			swap(u, v);
		records.emplace_back(u, v, Height[v]);
		Fa[u] = v, Height[v] = max(Height[v], Height[u] + 1);
	}
	if (l == r)
	{
		bool ok = true;
		for (int i = 0; i < 3 && ok; i ++)
			ok = Find(S[i]) == Find(T[i]);
		ans += ok;
	}
	else
	{
		int mid = l + r >> 1;
		dfs(ls(x), l, mid);
		dfs(rs(x), mid + 1, r);
	}
	for (int i = int(records.size()) - 1; i >= 0; i --)
	{
		Height[records[i].v] = records[i].h_v;
		Fa[records[i].u] = records[i].u;
	}
}

int main()
{
	Read();
	Build();
	dfs(1, 1, sz);
	printf("%d\n", ans);
	return 0;
}
