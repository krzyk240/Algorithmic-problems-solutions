// Krzysztof Małysa
#include <bits/stdc++.h>
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

	int sum, diff;
	PII v[2];
	for (PII& p : v) {
		char c;
		int t[4];
		cin >> t[0] >> c >> t[1] >> t[2] >> c >> t[3];
		p = {t[0] * 60 + t[1], t[2] * 60 + t[3]};
		if (p.ND < p.ST)
			p.ND += 24 * 60;
	}
	sum = v[0].ND - v[0].ST;
	diff = v[1].ND - v[1].ST;
	bool do_swap = false;
	if (sum > 11 * 60 + 11) {
		sum = 24 * 60 - sum;
		do_swap = true;
	}
	if (diff > 11 * 60 + 11)
		diff = 24 * 60 - diff;
	int l = (sum + diff) / 2;
	int d = sum - l;

	LOGN(sum/60.0);
	LOGN(diff/60.0);
	LOGN(l/60.0);
	LOGN(d/60.0);

	if (do_swap)
		swap(l, d);

	cout << fixed << setprecision(0) << abs(d/60.0) << endl;
	return 0;
}
