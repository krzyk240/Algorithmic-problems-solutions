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

string bin(int i) {
	string s;
	while (i) {
		s += "01"[i & 1];
		i >>= 1;
	}
	reverse(ALL(s));
	return s;
}

string four(int i) {
	string s;
	while (i) {
		s += "0123"[i & 3];
		i >>= 2;
	}
	reverse(ALL(s));
	return s;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	map<int, int> M = { {1, 1}, {3, 2}, {5, 3}, {9, 4}, {11, 5}, {19, 7},
		{21, 8}, {35, 9}, {37, 11}, {43, 13}, {69, 14}, {73, 15}, {75, 18},
		{83, 19}, {85, 21}, {139, 23}, {147, 26}, {149, 29}, {165, 30},
		{171, 34}, {277, 37}, {293, 41}, {299, 47}, {331, 49}, {339, 50},
		{341, 55}, {555, 60}, {587, 67}, {595, 69}, {597, 76}, {661, 79},
		{683, 89}, {1109, 97}, {1173, 108}, {1189, 109}, {1195, 123},
		{1323, 128}, {1355, 129}, {1363, 131}, {1365, 144}, {2219, 157},
		{2347, 175}, {2379, 178}, {2387, 181}, {2389, 199}, {2645, 207},
		{2709, 208}, {2731, 233}, {4437, 254}, {4691, 257}, {4693, 283},
		{4757, 287}, {4779, 322}, {5291, 335}, {5419, 337}, {5451, 338},
		{5459, 343}, {5461, 377}, {8875, 411}, {9387, 458}, {9515, 465},
		{9547, 467}, {9555, 474}, {9557, 521}, {10581, 542}, {10837, 545},
		{10923, 610}, {17749, 665}, {18771, 674}, {18773, 741}, {19029, 752},
		{19093, 753}, {19115, 843}, {21163, 877}, {21675, 882}, {21803, 883},
		{21835, 885}, {21843, 898}, {21845, 987}, {35499, 1076}, {37547, 1199},
		{38059, 1217}, {38187, 1220}, {38219, 1223}, {38227, 1241},
		{38229, 1364}, {42325, 1419}, {43349, 1427}, {43605, 1428},
		{43691, 1597}, {70997, 1741}, {75091, 1765}, {75093, 1940},
		{76117, 1969}, {76373, 1973}, {76459, 2207}, {84651, 2296},
		{86699, 2309}, {87211, 2311}, {87339, 2312}, {87371, 2317},
		{87379, 2351}, {87381, 2584},
	};

	int n;
	cin >> n;
	while (n) {
		cout << (--M.upper_bound(n))->ND << endl;
		cin >> n;
	}
	return 0;
}
