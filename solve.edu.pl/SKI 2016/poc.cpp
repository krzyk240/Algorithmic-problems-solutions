// Krzysztof Małysa
#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,n) for (int i = (a), i##__ = (n); i <= i##__; ++i)
#define REP(i,n) FOR(i,0,n)
#define FORD(i,a,n) for (int i = (a), i##__ = (n); i >= i##__; --i)
#define ALL(x) x.begin(), x.end()
#define EB emplace_back
#define ST first
#define ND second
#define OO(A) template<class... T> ostream& operator<<(ostream& os, const A<T...>& x) { return __o(os, ALL(x)); }
#define SZ(x) ((int)x.size())

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<PII> VPII;

template<class A, class B> ostream& operator<<(ostream&, const pair<A, B>&);
template<class I> ostream& __o(ostream&, I, I);
OO(vector) OO(deque) OO(set) OO(multiset) OO(map) OO(multimap)
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p) {
	return os << "(" << p.ST << ", " << p.ND << ")";
}
template<class I> ostream& __o(ostream& os, I a, I b) {
	os << "{";
	for (; a != b;)
		os << *a++, cerr << (a == b ? "" : " ");
	return os << "}";
}
template<class I> ostream& __d(ostream& os, I a, I b) {
	os << "{\n";
	for (I c = a; a != b; ++a)
		os << "  " << distance(c, a) << ": " << *a << endl;
	return os << "}";
}
template<class... T> void __e(T&&... a) {
	int t[] = {(cerr << forward<T>(a), 0)...}; (void)t;
	cerr << endl;
}

template<class A, class B> void mini(A& a, B&& b) { if (b < a) a = b; }
template<class A, class B> void maxi(A& a, B&& b) { if (b > a) a = b; }
int ceil2(int x) { return 1 << (sizeof(x) * 8 - __builtin_clz(x - 1)); }

#ifdef DEBUG
# define D(...) __VA_ARGS__
#else
# define D(...)
#endif

#define LOG(x) D(cerr << #x ": " << x)
#define LOGN(x) D(LOG(x) << endl)
#define DUMP(x) D(cerr << #x ": ", __d(cerr, ALL(x)) << endl)
#define E(...) D(__e(__VA_ARGS__))
#define endl '\n'
// End of templates

VI dsu;

inline int Find(int x) { return (x == dsu[x] ? x : dsu[x] = Find(dsu[x])); }
// a --> b
inline void Union(int a, int b) { dsu[Find(a)] = Find(b); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	int z;
	scanf("%i", &z);
	while (z--) {
		E("==============================");
		int n, k, c;
		scanf("%i%i%i", &n, &k, &c);
		E("n, k, c -> ", n, ", ", k, ", ", c);
		char in[k + 2][c + 1];
		VI pos(k + 2);

		// Begin guard
		pos[0] = 0;
		fill(in[0], in[0] + c, '0');
		in[0][c] = '\0';
		// End guard
		pos[k + 1] = n + 1;
		fill(in[k + 1], in[k + 1] + c, '0');
		in[k + 1][c] = '\0';

		FOR (i, 1, k) {
			in[i][0] = '0';
			scanf("%i %s", &pos[i], in[i] + 1);
		}

		D(REP (i, k + 1)
			E(pos[i], ' ', (char*)in[i]);
		)

		// Init DSU
		dsu.resize(k + 2);
		iota(ALL(dsu), 0);

		// Do the work
		REP (i, c - 1) {
			VI vis(n + 3, -1); // vis[i] = id of an arbitrary conductor containing it, -1 if there is none
			E("++++++++++ -> i: ", i);
			// Move conductors by one moment
			REP (j, k + 1) {
				switch (in[j][i]) {
					case '+': ++pos[j]; break;
					case '-': --pos[j]; break;
				}
				vis[pos[j]] = j; // Mark place
			}

			LOGN(pos);
			LOGN(vis);

			REP (j, k + 1) {
				int p = pos[j];
				Union(j, vis[p]); // Merge conductors standing at one place

				if (vis[p + 1] != -1)
					Union(j, vis[p + 1]); // Merge conductors standing at adjacent places
			}
		}

		puts(Find(0) != Find(k + 1) ? "TAK" : "NIE");
	}
	return 0;
}
