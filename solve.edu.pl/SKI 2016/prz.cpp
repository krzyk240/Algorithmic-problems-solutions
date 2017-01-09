// Krzysztof MaĹ‚ysa
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
template<class T, size_t N> ostream& operator<<(ostream& os, const array<T, N>& x) { return __o(os, ALL(x)); }
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

vector<VI> G;
VI conn_comp_id;

void DFS(int x, int ccid) {
	conn_comp_id[x] = ccid;
	for (int i : G[x])
		if (conn_comp_id[i] == -1)
			DFS(i, ccid);
}

int main() {
	int z;
	scanf("%i", &z);
	while (z--) {
		int n, k, m;
		scanf("%i%i%i", &n, &k, &m);
		G.assign(n + 1, VI());
		conn_comp_id.assign(n + 1, -1);

		int a, b;
		while (k--) {
			scanf("%i%i", &a, &b);
			G[a].EB(b);
			G[b].EB(a);
		}

		VI t(n + 1);
		FOR (i, 1, n) {
			scanf("%i", &t[i]);
			t[i] %= m;
			if (t[i] == 0)
				t[i] = m;
		}

		// Decompose to connected components
		int ccs = 0; // Number of CCs found
		FOR (i, 1, n)
			if (conn_comp_id[i] == -1 && G[i].size()) // Omit orphaned vertexes
				DFS(i, ccs++);

		VI orphaned_vals;
		FOR (i, 1, n)
			if (G[i].empty())
				orphaned_vals.EB(t[i]);

		LOGN(ccs);
		LOGN(conn_comp_id);
		LOGN(orphaned_vals);

		// For each component compute GCD of m and every t[v], where v is in the same CC
		VI GCD(ccs, m);
		FOR (i, 1, n)
			if (G[i].size())
				GCD[conn_comp_id[i]] = __gcd(GCD[conn_comp_id[i]], t[i]);

		LOGN(GCD);

		// Iff all the GCDs and orphaned_vals are equal, the solution exist
		for (int g : GCD)
			if (g != GCD.front())
				goto no;

		for (int x : orphaned_vals)
			if (x != orphaned_vals.front())
				goto no;

		if (GCD.size() && orphaned_vals.size() && GCD[0] != __gcd(m, orphaned_vals[0]))
			goto no;

		puts("TAK");
		continue;
	no:
		puts("NIE");
	}
	// system(("cat /proc/" + to_string(getpid()) + "/status >&2").c_str());
	return 0;
}