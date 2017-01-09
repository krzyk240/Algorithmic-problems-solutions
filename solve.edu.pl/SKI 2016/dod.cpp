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

int n, w;
LL pow10pow[18] = {
	1LL,
	10LL,
	100LL,
	1000LL,
	10000LL,
	100000LL,
	1000000LL,
	10000000LL,
	100000000LL,
	1000000000LL,
	10000000000LL,
	100000000000LL,
	1000000000000LL,
	10000000000000LL,
	100000000000000LL,
	1000000000000000LL,
	10000000000000000LL,
	100000000000000000LL,
};

constexpr int MAX = 1e9;

LL oddPlus(LL a, LL b) {
	LL x = a * *upper_bound(pow10pow, pow10pow + 10, b) + b;
	E("odd(", a, ", ", b, ") -> ", x);
	// assert(x == a * pow10pow[LL(log10(b)) + 1] + b);
	return x;
}

struct VectorHash {
    size_t operator()(const std::vector<LL>& v) const {
        std::hash<LL> hasher;
        size_t seed = 0;
        for (LL i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

unordered_set<vector<LL>, VectorHash> S;

bool possibleOdd(vector<LL> v) {
	sort(ALL(v));
	if (!S.insert(v).second)
		return false;

	E(string((n - v.size()) << 2, ' '), v);
	REP (i, SZ(v) - 1)
		REP (j, SZ(v) - 1)
			if (i != j) {
				vector<LL> x;
				REP (k, SZ(v) - 1)
					if (k != i && k != j)
						x.EB(v[k]);

				// Normal plus
				x.EB(v[i] + v[j]);
				if (i < j) { // v[i] + v[j] == v[j] + v[i]
					if (x.back() == w)
						return true;

					if (x.back() < w && possibleOdd(x))
						return true;
				}

				// Odd plus
				x.back() = oddPlus(v[i], v[j]);
				if (x.back() == w)
					return true;

				if (x.back() < w && possibleOdd(x))
					return true;
			}

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int z;
	scanf("%i", &z);
	while (z--) {
		scanf("%i", &n);
		int t[6];
		REP (i, n - 1)
			scanf("%i", &t[i]);
		scanf("%i", &w);

		auto possibleNormal = [&] {
			FOR (mask, 1, (1 << n) - 1) {
				LL sum = 0;
				REP (i, n - 1)
					if (mask & (1 << i))
						sum += t[i];
				if (sum == w)
					return true;
			}
			return false;
		};

		if (possibleNormal()) {
			puts("TAK");
			continue;
		}

		puts(possibleOdd({t, t + n}) ? "NIE" : "TAK");
		S.clear();
	}
	return 0;
}
