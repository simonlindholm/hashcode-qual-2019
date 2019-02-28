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
// For C: -DTMAX=2500
// For D: -DTMAX=220
// For E: -DTMAX=500
#error Pass -DTMAX=num tags
#endif

typedef bitset<TMAX> BS;

int N;
vector<bool> used;

vector<vi> photosForTag;
vector<vi> orders;

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

	photosForTag.resize(result.T);

	rep(i,0,N) {
		trav(t, result.photos[i].tags) {
			assert(t < TMAX);
			result.photos[i].bs[t] = 1;
			photosForTag[t].push_back(i);
		}
	}

    return result;
}

int score(const BS& a, int as, const BS& b, int bs) {
	int is = (int)(a & b).count();
	as -= is;
	bs -= is;
	return min({is, as, bs});
}

int score(const BS& a, int as, const BS& b) {
	return score(a, as, b, (int)b.count());
}

int score(const BS& a, const BS& b) {
	return score(a, (int)a.count(), b);
}

BS tomask(problem& pr, pii pa) {
	BS ret{};
	if (pa.first != -1)
		ret |= pr.photos[pa.first].bs;
	if (pa.second != -1)
		ret |= pr.photos[pa.second].bs;
	return ret;
}

pii pickBest(problem& pr, pii curv, const vi& ord) {
	BS cur = tomask(pr, curv);
	const int NUM_V = 4;
	int bestVe[NUM_V];
	int bestVei[NUM_V];
	rep(i,0,NUM_V) bestVe[i] = -1, bestVei[i] = -1;
	int bestHs = -1;
	int bestHsi = -1;
	int curs = (int)cur.count();

	auto addVert = [&](int sc, int i) {
		if (sc <= bestVe[NUM_V - 1]) return;
		bestVe[NUM_V - 1] = sc;
		bestVei[NUM_V - 1] = i;
		for (int j = NUM_V-1; j > 0; --j) {
			if (bestVe[j] > bestVe[j-1]) {
				swap(bestVe[j], bestVe[j-1]);
				swap(bestVei[j], bestVei[j-1]);
			} else break;
		}
	};

	rep(i,0,N) if (!used[i]) {
		int sc = score(cur, curs, pr.photos[i].bs, sz(pr.photos[i].tags));
		if (pr.photos[i].horisontal && sc > bestHs) bestHs = sc, bestHsi = i;
		if (!pr.photos[i].horisontal) addVert(sc, i);
	}

	int bestVe2 = -1, bestVei2 = -1, bestVei3 = -1;
	rep(ind,0,NUM_V) if (bestVei[ind] != -1) {
		BS bestvbs = pr.photos[bestVei[ind]].bs;
		rep(i,0,N) if (!used[i] && !pr.photos[i].horisontal) {
			int sc = score(cur, curs, pr.photos[i].bs | bestvbs);
			if (sc > bestVe2 && i != bestVei[ind]) bestVe2 = sc, bestVei2 = i, bestVei3 = bestVei[ind];
		}
	}

	if (bestVe2 > bestHs) { // (not the best heuristic?)
		return {bestVei3, bestVei2};
	} else {
		return {bestHsi, -1};
	}
}



int main() {
	problem pr = read_problem();
	N = pr.N;

	ll bestscore = -1;
	rep(i,0,1000) {
		vi ord(N);
		iota(all(ord), 0);
		random_shuffle(all(ord));
		orders.push_back(ord);
	}

	if (1) {
	// rep(seed,1,1000) { srand(seed);
	used.assign(N, false);
	vi ord(N);
	iota(all(ord), 0);

	auto markUsed = [&](pii pa) {
		used[pa.first] = 1;
		if (pa.second != -1) used[pa.second] = 1;
	};

	pii cur = pickBest(pr, pii(-1, -1), ord);
	vector<pii> res = {cur};
	markUsed(cur);
	int it = 0;
	ll myscore = 0;
	for (;;) {
		++it;
		if (it % 100 == 0) cerr << it << endl;
		pii next = pickBest(pr, cur, ord); // orders[rand() % sz(orders)]);
		if (next.first == -1) break;
		res.push_back(next);

		myscore += score(tomask(pr, cur), tomask(pr, next));

		cur = next;
		markUsed(cur);
	}

	cout << res.size() << endl;
	trav(pa, res) {
		cout << pa.first;
		if (pa.second != -1) cout << ' ' << pa.second;
		cout << endl;
	}

	if (myscore > bestscore) {
		cerr << "score = " << myscore << endl;
		bestscore = myscore;
	}
	}
}
