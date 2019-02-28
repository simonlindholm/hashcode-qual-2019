#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

const ll big = 1000000007;

struct photo{
    bool horisontal;
    vector<string> tags;
};

struct problem{
    int N;
    vector<photo> photos;
};

problem read_problem(){
    problem result;
    int N;
    cin >> N;
    result.N = N;
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
            ph.tags.push_back(s);
        }
        result.photos.push_back(ph);
    }
    return result;
}

void print_solution(vector<int> &solution){
    cout << sz(solution) << "\n";
    for(int c1 = 0; c1 < sz(solution); c1++){
        cout << solution[c1] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    problem p = read_problem();
    vi s;
    for(int c1 = 0; c1 < p.N; c1++){
        s.push_back(c1);
    }
    print_solution(s);

    return 0;
}
