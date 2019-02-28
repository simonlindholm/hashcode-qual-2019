#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/*
#ifndef TMAX
#error Pass -DTMAX=num tags
#endif
typedef bitset<TMAX> BS;
*/
int N;
vector<bool> used;

struct photo {
	bool horisontal;
	vector<int> tags;
};

struct problem {
	int N;
	int T;
	vector<photo> photos;
};

problem read_problem() {
    problem result;
    int N;
    cin >> N;
    result.N = N;

	map<string, int> tagmap;
	auto tagtoi = [&](string& s) {
		int& res = tagmap[s];
		if (res) return res - 1;
		res = sz(tagmap);
		return res - 1;
	};

    for(int c1 = 0; c1 < N; c1++){
        char ch;
        cin >> ch;
        photo ph;
        ph.horisontal = (ch == 'H');
        int a;
        cin >> a;
        for(int c2 = 0; c2 < a; c2++){
            string s;
            cin >> s;
            ph.tags.push_back(tagtoi(s));
        }
		sort(all(ph.tags));
        result.photos.push_back(ph);
    }
	result.T = sz(tagmap);
/*
	rep(i,0,N) {
		trav(t, result.photos[i].tags) {
			assert(t < TMAX);
			result.photos[i].bs[t] = 1;
		}
	}
*/
    return result;
}

vi merg_slow(vi &p1, vi &p2){ // assumes sorted
     vi res;
     ll r2 = 0;
     for(int c1 = 0; c1 < sz(p1); c1++){
        while(r2 < sz(p2) && p2[r2] < p1[c1]){
            res.push_back(p2[r2]);
            r2++;
        }

        if(r2 < sz(p2) && p2[r2] == p1[c1]){
            r2++;
        }
        res.push_back(p1[c1]);

     }
     return res;
}

int intersection_slow(vi const &p1, vi const &p2){ // assumes sorted
    ll r2 = 0;
    ll ans = 0;
    for(int c1 = 0; c1 < sz(p1); c1++){
        while(r2 < sz(p2) && p2[r2] < p1[c1]){
            r2++;
        }
        if(r2 >= sz(p2))break;
        if(p1[c1] == p2[r2])ans++;
    }
    return ans;
}

int score(const vi & a, const vi & b) {
	int is = intersection_slow(a,b);
	int as = sz(a) - is;
	int bs = sz(b) - is;
	return min({is, as, bs});
}

vi tomask(problem& pr, pii pa) {
	vi ret = pr.photos[pa.first].tags;
	if (pa.second != -1)
		ret = merg_slow(ret, pr.photos[pa.second].tags);
	return ret;
}

pii pickBest(problem& pr, vi cur) {
	int bestHs = -1, bestVe = -1;
	int bestHsi = -1, bestVei = -1;
	rep(i,0,N) if (!used[i]) {
		int sc = score(cur, pr.photos[i].tags);
		if (pr.photos[i].horisontal && sc > bestHs) bestHs = sc, bestHsi = i;
		if (!pr.photos[i].horisontal && sc > bestVe) bestVe = sc, bestVei = i;
	}
	int bestVe2 = -1, bestVei2 = -1;
	if (bestVei != -1) {
		vi bestvbs = pr.photos[bestVei].tags;
		rep(i,0,N) if (!used[i] && !pr.photos[i].horisontal) {
			int sc = score(cur, merg_slow(pr.photos[i].tags, bestvbs));
			if (sc > bestVe2 && i != bestVei) bestVe2 = sc, bestVei2 = i;
		}
		if (bestVei2 == -1) bestVei = -1;
	}

	if (bestVe2 > bestHs) { // (not the best heuristic)
		return {bestVei, bestVei2};
	} else {
		return {bestHsi, -1};
	}
}



int main() {
	problem pr = read_problem();
	N = pr.N;

	used.resize(N);

	auto markUsed = [&](pii pa) {
		used[pa.first] = 1;
		if (pa.second != -1) used[pa.second] = 1;
	};

	pii cur = pickBest(pr, vi());
	vector<pii> res = {cur};
	markUsed(cur);
	int it = 0;
	for (;;) {
		++it;
		if (it % 100 == 0) cerr << it << endl;
		if(it == 500)break;
		pii next = pickBest(pr, tomask(pr, cur));
		if (next.first == -1) break;
		res.push_back(next);
		cur = next;
		markUsed(cur);
		// score(mask(cur), mask(next));
	}

	cout << res.size() << endl;
	trav(pa, res) {
		cout << pa.first;
		if (pa.second != -1) cout << ' ' << pa.second;
		cout << endl;
	}
}
