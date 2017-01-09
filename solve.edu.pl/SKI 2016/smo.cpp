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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int z;
	scanf("%i", &z);
	while (z--) {
		E("==============================");
		int n, m;
		scanf("%i%i", &n, &m);
		LOGN(n);
		LOGN(m);

		VVI G(n + 1);
		int a, b;
		REP (i, m - 1) {
			scanf("%i%i", &a, &b);
			G[a].EB(b);
			G[b].EB(a);
		}

		VI unvis(n - 1), tovis = {1}; // unvisited, to visit
		iota(ALL(unvis), 2);
		LOGN(unvis);

		vector<bool> reachable(n + 1, true);
		while (tovis.size() && unvis.size()) { // second condition speeds up
			int x = tovis.back();
			tovis.pop_back();

			// Mark unreachable vertexes
			for (int v : G[x])
				reachable[v] = false;

			FORD (i, unvis.size() - 1, 0)
				if (reachable[unvis[i]]) {
					tovis.EB(unvis[i]);
					// Remove unvis[i]
					swap(unvis[i], unvis.back());
					unvis.pop_back();
				}

			// Restore state
			for (int v : G[x])
				reachable[v] = true;
		}

		puts(unvis.empty() ? "TAK" : "NIE");
	}
	return 0;
}
