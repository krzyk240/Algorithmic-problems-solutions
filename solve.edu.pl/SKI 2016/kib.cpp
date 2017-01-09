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

VI dsu;

inline int Find(int x) { return (dsu[x] == x ? x : dsu[x] = Find(dsu[x])); }
// Links a to b
inline void Union(int a, int b) { dsu[Find(a)] = Find(b); }

VVI G;
vector<VPII> Q; // (node, query_id)
VI lca;
vector<bool> vis;

void LCA(int x) {
	vis[x] = true;
	for (auto& i : Q[x])
		if (vis[i.ST])
			lca[i.ND] = Find(i.ST);
	for (int i : G[x])
		if (!vis[i]) {
			LCA(i);
			Union(i, x);
		}
}

using Set = multiset<int, greater<int>>;
vector<VI> in, out; // for each node: values to add / remove from state

// Merge sets
void mergeToFirst(Set& a, Set& b) {
	// Always smaller to the bigger
	if (b.size() > a.size())
		a.swap(b);

	// b <<<--- a
	a.insert(ALL(b));
	b.clear();
}

VI max_val;

// Return aggressions on the way
Set DFS(int x, int p) {
	Set res(ALL(in[x]));
	for (int i : G[x])
		if (i != p) {
			auto o = DFS(i, x);
			mergeToFirst(res, o);
		}

	max_val[x] = (res.empty() ? 0 : *res.begin());

	E(x, " -> ", res);

	// Remove outdated elements from res
	for (int i : out[x]) {
		res.erase(res.find(i));
		res.erase(res.find(i));
	}

	return res;
}

// #include <unistd.h>
int main() {
	int z;
	scanf("%i", &z);
	while (z--) {
		int n, a, b, m;
		scanf("%i%i", &n, &m);

		G.assign(n + 1, VI());
		Q.assign(n + 1, VPII());
		vis.assign(n + 1, false);
		dsu.resize(n + 1);
		iota(ALL(dsu), 0);
		lca.assign(m, 0);

		REP (i, n - 2) {
			scanf("%i%i", &a, &b);
			G[a].EB(b);
			G[b].EB(a);
		}

		// Queries
		struct Queries {
			int a, b, aggression;
		};
		vector<Queries> QQ(m);
		REP (i, m - 1) {
			auto& q = QQ[i];
			scanf("%i%i%i", &q.a, &q.b, &q.aggression);
			Q[q.a].EB(q.b, i);
			Q[q.b].EB(q.a, i);
		}
		LCA(1);
		LOGN(lca);
		// LCAs has been computed
		// Clean
		// vector<VPII>().swap(Q);
		// VI().swap(dsu);

		// Now the task
		in.assign(n + 1, VI());
		out.assign(n + 1, VI());
		max_val.assign(n + 1, 0);
		REP (i, m - 1) {
			auto& q = QQ[i];
			out[lca[i]].EB(q.aggression);
			in[q.a].EB(q.aggression);
			in[q.b].EB(q.aggression);
		}

		DFS(1, 1);
		// Clean
		// vector<VI>().swap(in);
		// vector<VI>().swap(out);

		// Print results
		FOR (i, 1, n)
			printf("%i%c", max_val[i], " \n"[i == n]);
	}

	// system(("cat /proc/" + to_string(getpid()) + "/status >&2").c_str());
	return 0;
}
