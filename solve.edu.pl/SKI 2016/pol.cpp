#include<bits/stdc++.h>

using namespace std;

int dycha[10];

inline int len(int x) {
	int r = 0;
	while(x) {x/=10; r++;}
	return r;
}

int n,w;
int wlen;

const int N = 8;
int a[N], l[N];

int stos[N*2];
int stoslen[N*2];

int stossize;

#define PLUS -1
#define CONC -2

bool wyb[N];

//int at = 0;

/*void wypisz_aktualny(int aktt) {
	cout << "Jestem w " << aktt << " : ";
	for(int i=0;i<stossize;i++)
		cout << stos[i] << " "; 
	cout << " lens:  ";

	for(int i=0;i<stossize;i++)
		cout << stoslen[i] << " "; 

	cout << endl;

}*/

typedef long long ll;
ll val;
inline bool solve() {
	//int aktt = at++;
	//wypisz_aktualny(aktt);
	if(stossize == 1 and stos[0] == w) {
		return true;
	}

	for(int i=0;i<n;i++) {
		if(!wyb[i]) {
			stos[stossize++] = a[i];
			stoslen[stossize-1] = l[i];
			wyb[i] = true;

			if(solve()) return true;
			//cout << "wracam do " << aktt << endl;

			wyb[i] = false;
			stossize--;

			//wypisz_aktualny(aktt);
		}
	}

	if(stossize >= 2) {
		// CONCATENATION

		if(stoslen[stossize-2] + stoslen[stossize-1] <= wlen) {
			int oldb = stos[stossize-1];
			int blen = stoslen[stossize-1];
			
			val = stos[stossize-2];
			val = val * dycha[stoslen[stossize-1]];
			val += stos[stossize-1];

			if(val <= w) {
				
				/*stos[stossize-2] *= dycha[stoslen[stossize-1]];
				stos[stossize-2] += stos[stossize-1];*/
				stos[stossize-2] = val;
				
				//assert(val <= (int)1e9);
				stoslen[stossize-2] += stoslen[stossize-1];

				stossize--;
				
				if(solve()) return true;
				//cout << "wracam do " << aktt << endl;

				stossize++;
				
				stos[stossize-1] = oldb;
				stoslen[stossize-1] = blen;
				stos[stossize-2] -= oldb;
				stos[stossize-2] /= dycha[blen];
				stoslen[stossize-2] -= blen;

				//wypisz_aktualny(aktt);
			}
		}
		
		// SUM
				
		if(stos[stossize-2] + stos[stossize-1] <= w) {
			int oldb = stos[stossize-1];

			int l = max(stoslen[stossize-1], stoslen[stossize-2]);
			int oldlena = stoslen[stossize-2], oldlenb = stoslen[stossize-1];

			if(stos[stossize-1] + stos[stossize-2] >= dycha[l])
				l++;

			stos[stossize-2] += oldb;

			stoslen[stossize-2] = l;
			
			stossize--;

			if(solve()) return true;
			//cout << "wracam do " << aktt << endl;

			stossize++;

			stos[stossize-1] = oldb;
			stos[stossize-2] -= oldb;

			stoslen[stossize-1] = oldlenb;
			stoslen[stossize-2] = oldlena;

			//`wypisz_aktualny(aktt);
		}
	}
	return false;
}

inline bool one_case() {
	cin >> n;
	for(int i=0;i<n;i++) {
		cin >> a[i];
		l[i] = len(a[i]);
	}
	
	bool dasie = false;
	cin >> w;

	for(int i=0;i<(1<<n);i++) {
		ll suma = 0;
		for(int j=0;j<n;j++) if(i&(1<<j))
			suma += a[j];	
		if(suma == (ll)w)
			dasie = true;
	}
	wlen = len(w);

	stossize = 0;
	for(int i=0;i<n;i++) 
		wyb[i] = false;

	//cout << "dasie: " << dasie << endl;
	return solve() == dasie;
}

int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	dycha[0] = 1;
	for(int i=1;i<10;i++) dycha[i] = dycha[i-1]*10;
	
	int t;
	cin >> t;

	while(t--)
		cout << (one_case() ? "TAK" : "NIE") << "\n";

}
