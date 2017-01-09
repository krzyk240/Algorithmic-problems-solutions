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

constexpr int mod = 1e9 + 7;

LL power(LL a, int k) {
	LL res = 1;
	while (k) {
		if (k & 1)
			res = res * a % mod;
		k >>= 1;
		a = a * a % mod;
	}
	return res;
}

int main() {
	constexpr int MAXF = 4000;
	array<LL, MAXF + 1> factorial, rev_factorial;
	factorial[0] = rev_factorial[0] = 1;
	FOR (i, 1, MAXF) {
		factorial[i] = factorial[i - 1] * i % mod;
		rev_factorial[i] = power(factorial[i], mod - 2);
	}

	vector<vector<LL>> binomt(MAXF + 1);
	REP (n, MAXF) {
		binomt[n].resize(n + 1);
		REP (k, n)
			binomt[n][k] = (factorial[n] * rev_factorial[k] % mod) * rev_factorial[n - k] % mod;
	}
	auto binom = [&](int n, int k) {
		return binomt[n][k];
		// return (factorial[n] * rev_factorial[k] % mod) * rev_factorial[n - k] % mod;
	};

	int z;
	scanf("%i", &z);
	while (z--) {
		char aa[4], s[MAXF + 1];
		scanf("%s%s", aa, s);
		int a[3] = {aa[0], aa[1], aa[2]};

		int n = strlen(s);
		int t[150] = {};
		REP (i, n - 1)
			++t[(int)s[i]];

		LL others = 0, others_res = 1;
		REP (i, 149)
			if (i != a[0] && i != a[1] && i != a[2]) {
				others += t[i];
				others_res = others_res * binom(others, t[i]) % mod;
			}

		E(t[a[0]], ' ', t[a[1]], ' ', t[a[2]]);

		// Check whether we have enough characters
		if (--t[a[0]] < 0 || --t[a[1]] < 0 || --t[a[2]] < 0) {
			puts("0");
			continue;
		}


		// Restore state
		++t[a[0]];
		++t[a[1]];
		++t[a[2]];

		// 000
		if (a[0] == a[1] && a[1] == a[2]) {
			printf("%lli\n", others_res * binom(n, others) % mod);
			continue;
		}

		// 001 -> // 011
		if (a[0] == a[1] && a[1] != a[2])
			swap(a[0], a[2]);

		// 010
		if (a[0] == a[2] && a[0] != a[1]) {
			int ta0 = t[a[0]];
			int ta1 = t[a[1]];
			LL res = binom(ta0 + ta1, ta0);
			// Remove cases: B..BA..AB..B
			res -= binom(ta1 + 1, 1);

			res %= mod;
			if (res < 0)
				res += mod;

			printf("%lli\n", (others_res * res % mod) *
				binom(n, others) % mod);
			continue;
		}

		// 011
		if (a[0] != a[1] && a[1] == a[2]) {
			int ta0 = t[a[0]];
			int ta1 = t[a[1]];
			LL res = binom(ta0 + ta1, ta0);
			// Remove cases: B..BA..ABA..A
			res -= binom(ta0 + 1, 1);

			res %= mod;
			if (res < 0)
				res += mod;

			printf("%lli\n", (others_res * res % mod) *
				binom(n, others) % mod);
			continue;
		}

		// 012
		if (a[0] != a[1] && a[1] != a[2] && a[0] != a[2]) {
			int ta0 = t[a[0]];
			int ta1 = t[a[1]];
			int ta2 = t[a[2]];
			LL res = binom(ta0 + ta1, ta0) * binom(ta0 + ta1 + ta2, ta2); // here % is not needed

			REP (i, ta0)
				REP (j, ta1) {
					/*
					B...BA...A merge with C...C, append C and append all A...A
					^ j ^^ i ^              ^ta2-1                         ^ta0-i
					  mixed with B...B
					               ^ta1-j
					 */
					res -= binom(i + j + ta2 - 1, ta2 - 1) * binom(ta0 - i + ta1 - j, ta0 - i) % mod;
				}

			res %= mod;
			if (res < 0)
				res += mod;

			printf("%lli\n", (others_res * res % mod) *
				binom(n, others) % mod);

			continue;
		}

		assert(false);
	}

	// system(("cat /proc/" + to_string(getpid()) + "/status >&2").c_str());
	return 0;
}
