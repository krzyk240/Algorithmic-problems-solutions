//Krzysztof Małysa
#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,n) for (int i = (a), i##__e = (n); i <= i##__e; ++i)
#define REP(i,n) FOR(i,0,n)
#define FORD(i,a,n) for (int i = (a), i##__e = (n); i >= i##__e; --i)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
#define ST first
#define ND second
#define EB emplace_back
#define OO(...) ostream& operator<<(ostream& os, const __VA_ARGS__& x) { return __o(os, ALL(x)); }

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<PII> VPII;

template<class Iter> ostream& __o(ostream& os, Iter a, Iter b);
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p);

template<class A, int N> OO(array<A, N>)
template<class A> OO(vector<A>)
template<class A> OO(deque<A>)
template<class A, class B> OO(set<A, B>)
template<class A, class B> OO(multiset<A, B>)
template<class A, class B, class C> OO(map<A, B, C>)
template<class A, class B, class C> OO(multimap<A, B, C>)

ostream& operator<<(ostream& os, const array<char, 3>& x) {
	return os << string(ALL(x));
}

template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p) {
	return os << "(" << p.ST << ", " << p.ND << ")";
}

template<class Iter> ostream& __o(ostream& os, Iter a, Iter b) {
	os << "{";
	if (a != b) {
		os << *a;
		while (++a != b)
			os << ", " << *a;
	}
	return os << "}";
}

template<class Iter> ostream& __d(ostream& os, Iter a, Iter b) {
	os << "{\n";
	Iter beg = a;
	for (; a != b; ++a)
		os << distance(beg, a) << ": " << *a << endl;
	return os << "}\n";
}

template<class... Args>
void __e(Args&&... args) {
	int t[] = {(cerr << forward<Args>(args), 0)...};(void)t;
	cerr << endl;
}

template<class A, class B> void mini(A& a, B&& b) { if (b < a) a = b; }
template<class A, class B> void maxi(A& a, B&& b) { if (b > a) a = b; }

int ceil2(int x) { return 1 << (sizeof(x) * 8 - __builtin_clz(x - 1)); }

#define endl '\n'

#ifdef DEBUG
# define D(...) __VA_ARGS__
#else
# define D(...)
#endif

#define LOG(x) D(cerr << #x ": " << x)
#define LOGN(x) D(LOG(x) << endl)
#define DUMP(x) D(cerr << #x ": ", __d(cerr, ALL(x)))
#define E(...) D(__e(__VA_ARGS__))
/// End of templates

class Aho {
public:
	typedef unsigned uint;

	struct Node {
		uint patt_id = 0; // pattern id which ends in this node or zero if such
		             // does not exist
		uint fail = 0; // fail edge
		uint next_pattern = 0; // id of the longest pattern which is prefix of
		                       // one ending in this node or zero if such
		                       // does not exist
		std::vector<std::pair<char, uint>> sons; // sons (sorted array - for
		                                        // small alphabets it's the most
		                                        // efficient option)

		// Returns id of son @p c or 0 if such does not exist
		uint operator[](char c) const {
			uint beg = 0, end = sons.size();
			while (beg < end) {
				uint mid = (beg + end) >> 1;
				if (c < sons[mid].first)
					end = mid;
				else if (c == sons[mid].first)
					return sons[mid].second;
				else
					beg = mid + 1;
			}

			if (beg == sons.size() || sons[beg].first != c)
				return 0;

			return sons[beg].second;
		}
	};

private:
	std::vector<Node> nodes = {Node{}}; // root

	// Returns id of son @p c (creates one if such does not exist)
	uint son(uint id, char c) {
		uint beg = 0, end = nodes[id].sons.size();
		while (beg < end) {
			uint mid = (beg + end) >> 1;
			if (c < nodes[id].sons[mid].first)
				end = mid;
			else if (c == nodes[id].sons[mid].first)
				return nodes[id].sons[mid].second;
			else
				beg = mid + 1;
		}

		if (beg == nodes[id].sons.size() || nodes[id].sons[beg].first != c) {
			nodes.emplace_back();
			return nodes[id].sons.emplace(nodes[id].sons.begin() + beg,
				c, nodes.size() - 1)->second;
		}

		return nodes[id].sons[beg].second;
	}

public:
	Aho() = default;

	const Node& node(int i) const { return nodes[i]; }

	// Adds pattern s to structure and sets (override if such pattern has
	// already existed) its id to @p id, @p id equal to 0 disables the pattern,
	// pattern cannot be empty
	void addPattern(const std::string& patt, uint id) {
		uint curr = 0;
		for (char c : patt)
			curr = son(curr, c);
		nodes[curr].patt_id = id;
	}

	uint findNode(const std::string& str) const {
		uint x = 0;
		for (char c : str)
			if ((x = nodes[x][c]) == 0)
				return 0;

		return x;
	}

	// Returns pattern id which ends in node @p node_id
	uint pattId(uint node_id) const { return nodes[node_id].patt_id; }

	// Returns id of next pattern node for pattern which ends in node @p node_id
	uint nextPatt(uint node_id) const { return nodes[node_id].next_pattern; }

	void buildFails() {
		std::deque<uint> queue;
		for (auto&& p : nodes[0].sons)
			queue.emplace_back(p.second);

		while (queue.size()) {
			uint curr = queue.front();
			queue.pop_front();
			for (auto&& p : nodes[curr].sons) {
				uint v = nodes[curr].fail, x;
				while ((x = nodes[v][p.first]) == 0 && v)
					v = nodes[v].fail;
				nodes[p.second].fail = x;
				nodes[p.second].next_pattern = (nodes[x].patt_id ? x
					: nodes[x].next_pattern);
				queue.emplace_back(p.second);
			}
		}
	}

	// Returns set of ids of nodes in which longest matching pattern ends
	std::vector<uint> searchIn(const std::string& text) {
		std::vector<uint> res(text.size());
		uint curr = 0, x;
		for (size_t i = 0; i < text.size(); ++i) {
			char c = text[i];
			while ((x = nodes[curr][c]) == 0 && curr)
				curr = nodes[curr].fail;
			curr = x;
			res[i] = (nodes[curr].patt_id ? curr : nodes[curr].next_pattern);
		}
		return res;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int z, n;
	cin >> z;
	while (z--) {
		Aho aho;
		string text, s;
		cin >> text >> n;
		VI id(n);
		iota(ALL(id), 0);
		FOR (i, 1, n) {
			cin >> s;
			uint x = aho.findNode(s);
			if (x && (x = aho.pattId(x)) > 0)
				id[i - 1] = x - 1;
			else
				aho.addPattern(s, i);
		}

		aho.buildFails();
		auto t = aho.searchIn(text);

		vector<bool> vis(n);
		for (uint x : t)
			while (x) {
				int y = aho.pattId(x) - 1;
				if (vis[y])
					break;
				vis[y] = true;
				x = aho.nextPatt(x);
			}

		REP (i, n - 1)
			vis[i] = vis[id[i]];

		for (bool b : vis)
			cout << "ny"[b] << endl;
	}
	return 0;
}

/*
1
abcdabc
4
abc
bc
ab
d

*/
