#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <string>
 
typedef unsigned long long ull;
 
int m1=1e7+123;
int mxPow; // set to max of the length of all the strings that are hashed for comparisons of substrings of 2 diff strings
// Generate random base in (before, after) open interval:
int gen_base(const int before, const int after) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt_rand(seed);
    int base = std::uniform_int_distribution<int>(before+1, after)(mt_rand);
    return base % 2 == 0 ? base-1 : base;
}
 
struct PolyHash {
    // -------- Static variables --------
    static const int mod = (int)1e9+123; // prime mod of polynomial hashing
    static std::vector<int> pow1;        // powers of base modulo mod
    static std::vector<ull> pow2;        // powers of base modulo 2^64
    static int base;                     // base (point of hashing)
    // --------- Static functons --------
    static inline int diff(int a, int b) { 
        // Diff between `a` and `b` modulo mod (0 <= a < mod, 0 <= b < mod)
        return (a -= b) < 0 ? a + mod : a;
    }
    // -------------- Variables of class -------------
    std::vector<int> pref1; // Hash on prefix modulo mod
    std::vector<ull> pref2; // Hash on prefix modulo 2^64
    // Cunstructor from string:
    PolyHash(const std::string& s, int mxPow)
        : pref1(s.size()+1u, 0)
        , pref2(s.size()+1u, 0)
    {
        assert(base < mod);
        const int n = s.size(); // Firstly calculated needed power of base:
        while ((int)pow1.size() <= mxPow) {
            pow1.push_back(1LL * pow1.back() * base % mod);
            pow2.push_back(pow2.back() * base);
        }
        for (int i = 0; i < n; ++i) { // Fill arrays with polynomial hashes on prefix
            assert(base > s[i]);
            pref1[i+1] = (pref1[i] + 1LL * s[i] * pow1[i]) % mod;
            pref2[i+1] = pref2[i] + s[i] * pow2[i];
        }
    }
 
    // Polynomial hash of subsequence [pos, pos+len)
    // If mxPow != 0, value automatically multiply on base in needed power. Finally base ^ mxPow
    inline std::pair<int, ull> operator()(const int pos, const int len, const int mxPow = 0) const {
        int hash1 = pref1[pos+len] - pref1[pos];
        ull hash2 = pref2[pos+len] - pref2[pos];
        if (hash1 < 0) hash1 += mod;
        if (mxPow != 0) {
            hash1 = 1LL * hash1 * pow1[mxPow-(pos+len-1)] % mod;
            hash2 *= pow2[mxPow-(pos+len-1)];
        }
        return std::make_pair(hash1, hash2);
    }
};
 
// Init static variables of PolyHash class:
int PolyHash::base((int)1e9+7);
std::vector<int> PolyHash::pow1{1};
std::vector<ull> PolyHash::pow2{1};

//CAN BE USED TO HASH A STRING WITHOUT USING THE ABOVE STRUCTURE BUT MUST BE CALLED ONLY AFTER THE ABOVE STRUCTURE HAS BEEN CALLED ATLEAST ONCE.
// SO THAT POW ARRAY CONTAINS THE CORRECT VALUES.
pair<int,ull> hashThis(string gg) {
    int h1=0,k=gg.length();
    ull h2=0;
    for(int i = 0; i < gg.length(); i++) {
        h1 = (h1+gg[i]*PolyHash::pow1[i]);
        if(h1>=m1) h1%=m1;
    }
    for(int i = 0; i < gg.length(); i++) {
        h2=(h2+gg[i]*PolyHash::pow2[i]);
    }
    return {(PolyHash::pow1[mxPow-k+1]*h1)%m1,PolyHash::pow2[mxPow-k+1]*h2};
}


int main() {
    // Input:
    string s1 = "dsdas";
    string s2 = "rewzfdgs"
    // Max needed power:
    mxPow = max(s1.length(),s2.length());
 
    // Gen random base:
    PolyHash::base = gen_base(256, PolyHash::mod);
 
    // Create hashing object:
    PolyHash hash1(s1,mxPow);
    PolyHash hahs2(s2,mxPow);
    // access hash
    pair<int,ull> h1=hash1(1,3,mxPow);
    pair<int,ull> h2=hash2(2,4,mxPow);
    pair<iny,ull> h3=hashThis("dsafsdf");
    if(h1==h2) {
        cout<<"the strings are equal"<<endl;
    }


    // Put all start positions in vector:
    std::vector<int> pos;
    for (int i = 0; i < n; ++i) {
        pos.push_back(i);
    }
 
    // Linear search of min algorithm:
    auto p = *std::min_element(pos.begin(), pos.end(), [&](const int p1, const int p2) {
        // Binary search by equal subsequences length:
        int low = 0, high = n+1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (hash(p1, mid, mxPow) == hash(p2, mid, mxPow)) {
                low = mid;
            } else {
                high = mid;
            }
        }
        return low < n && a[p1+low] < a[p2+low];
    });
 
    // Output answer:
    printf("%s", a.substr(p, n).c_str());
    return 0;
}