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
		char t[1000001];
		scanf(" %s", t);
		LOGN(t);
		int sum = 0;
		array<bool, 10> isp = {{0,0,0,0,0,0,0,0,0,0}}; // 0 ... 9; +
		array<bool, 10> ism = {{0,0,0,0,0,0,0,0,0,0}}; // 0 ... 9; -
		for (int i = 0; t[i]; ++i) {
			int c = t[i] - '0';
			if (i & 1) {
				ism[c] = true;
				sum -= c;
			} else {
				isp[c] = true;
				sum += c;
			}
		}

		LOGN(sum);
		DUMP(isp);
		DUMP(ism);

		/*
		b - a  -->  a - b
		sum  -->  sum - b + a + a - b = sum - 2(b - a)  iff. sum == 2(b - a)
		Hence: b = (s + 2a)/2
		 */

		if (sum == 0) {
			puts("TAK");
			continue;
		}
		if (sum & 1) {
			puts("NIE");
			continue;
		}

		FOR (a, 0, 9)
			if (ism[a]) {
				int b = sum / 2 + a;
				if (b >= 0 && b <= 9 && isp[b]) {
					E("a = ", a, "  b = ", b);
					goto yes;
				}
			}

		puts("NIE");
		continue;

	yes:
		puts("TAK");
	}
	return 0;
}
