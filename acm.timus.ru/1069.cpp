// Krzysztof Małysa
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

#define FOR(i,a,n) for (int i = (a), i##__ = (n); i <= i##__; ++i)
#define REP(i,n) FOR(i,0,n)
#define FORD(i,a,n) for (int i = (a), i##__ = (n); i >= i##__; --i)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
#define ST first
#define ND second
#define OO(...) ostream& operator<<(ostream& os, const __VA_ARGS__& x) { return __o(os, ALL(x)); }
#define EB emplace_back

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<PII> VPII;

template<class Iter> ostream& __o(ostream& os, Iter a, Iter b);
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p);

template<class... Args> OO(vector<Args...>)
template<class... Args> OO(deque<Args...>)
template<class... Args> OO(set<Args...>)
template<class... Args> OO(multiset<Args...>)
template<class... Args> OO(map<Args...>)
template<class... Args> OO(multimap<Args...>)

template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << "(" << p.ST << ", " << p.ND << ")"; }
template<class Iter> ostream& __o(ostream& os, Iter a, Iter b) {
	os << "{";
	string t[] = {", ", ""};
	for (; a != b;)
		os << *a, os << t[++a == b];
	return os << "}";
}
template<class Iter> ostream& __d(ostream& os, Iter a, Iter b) {
	os << "{\n";
	for (Iter beg = a; a != b; ++a)
		os << "   " << distance(beg, a) << ": " << *a << endl;
	return os << "}";
}
template<class... Args> void __p(Args&&... args) {
	int t[] = {(cerr << args, 0)...}; (void)t;
	cerr << endl;
}
template<class A> A abs(A a) { return (a < A() ? -a : a); }
template<class A, class B> void mini(A& a, B&& b) { if (b < a) a = b; }
template<class A, class B> void maxi(A& a, B&& b) { if (b > a) a = b; }

inline int ceil2(int x) { return 1 << (sizeof(x) * 8 - __builtin_clz(x - 1)); }

#ifdef DEBUG
# define D(...) __VA_ARGS__
#else
# define D(...)
#endif

#define LOG(x) D(cerr << #x ": " << x)
#define LOGN(x) D(LOG(x) << endl)
#define DUMP(x) D(cerr << #x ": ", __d(cerr, ALL(x)) << endl)
#define E(...) D(__p(__VA_ARGS__))
#define endl '\n'
// End of templates

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n = 1, a, b;
	VI t;
	while (cin >> a) {
		++n;
		t.EB(a);
	}

	VI deg(n + 1);
	for (int i : t)
		++deg[i];

	DUMP(deg);

	priority_queue<int, VI, greater<int>> leafs;
	FOR (i, 1, n)
		if (deg[i] == 0)
			leafs.emplace(i);

	VVI G(n + 1);
	reverse(ALL(t));
	while (t.size()) {
		a = leafs.top();
		b = t.back();
		leafs.pop();
		t.pop_back();
		E("-> ", a, " ", b);

		G[a].EB(b);
		G[b].EB(a);
		if (--deg[b] == 0)
			leafs.push(b);
	}

	FOR (i, 1, n) {
		sort(ALL(G[i]));
		cout << i << ":";
		for (int j : G[i])
			cout << ' ' << j;
		cout << endl;
	}
	return 0;
}

