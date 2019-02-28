#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#ifndef TMAX
#error Pass -DTMAX=num tags
#endif
typedef bitset<TMAX> BS;

int N;
vector<bool> used;

struct photo {
	bool horisontal;
	vector<int> tags;
	BS bs;
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
        result.photos.push_back(ph);
    }
	result.T = sz(tagmap);

	rep(i,0,N) {
		trav(t, result.photos[i].tags) {
			assert(t < TMAX);
			result.photos[i].bs[t] = 1;
		}
	}

    return result;
}

int score(const BS& a, const BS& b) {
	int is = (int)(a & b).count();
	int as = (int)a.count() - is;
	int bs = (int)b.count() - is;
	return min({is, as, bs});
}

BS tomask(problem& pr, pii pa) {
	BS ret = pr.photos[pa.first].bs;
	if (pa.second != -1)
		ret |= pr.photos[pa.second].bs;
	return ret;
}

pii pickBest(problem& pr, BS cur) {
	int bestHs = -1, bestVe = -1;
	int bestHsi = -1, bestVei = -1;
	rep(i,0,N) if (!used[i]) {
		int sc = score(cur, pr.photos[i].bs);
		if (pr.photos[i].horisontal && sc > bestHs) bestHs = sc, bestHsi = i;
		if (!pr.photos[i].horisontal && sc > bestVe) bestVe = sc, bestVei = i;
	}
	int bestVe2 = -1, bestVei2 = -1;
	if (bestVei != -1) {
		BS bestvbs = pr.photos[bestVei].bs;
		rep(i,0,N) if (!used[i] && !pr.photos[i].horisontal) {
			int sc = score(cur, pr.photos[i].bs | bestvbs);
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

	pii cur = pickBest(pr, BS());
	vector<pii> res = {cur};
	markUsed(cur);
	int it = 0;
	for (;;) {
		++it;
		if (it % 100 == 0) cerr << it << endl;
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
