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
    vector<int> tags;
};

struct problem{
    int N;
    int T;
    vector<photo> photos;
};

problem read_problem(){
    problem result;
    int N;
    cin >> N;
    result.N = N;
    map<string,int> M;
    int sts = 0;
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
            if(M.find(s) == M.end()){
                M[s] = sts;
                sts++;
            }
            ph.tags.push_back(M[s]);
        }
        sort(all(ph.tags));
        result.photos.push_back(ph);
    }
    result.T = sts;
    return result;
}

void print_solution(vector<pair<int,int> > &solution){
    cout << sz(solution) << "\n";
    for(int c1 = 0; c1 < sz(solution); c1++){
        cout << solution[c1].first;
        if(solution[c1].second != -1){
            cout <<" "<< solution[c1].second;
        }
        cout << "\n";
    }
}