#include <bits/stdc++.h>
using namespace std;
// BE CAREFUL AS HERE LONG LONG IS USED EVERYWHERE SO CHANGE ACCORDINGLY IF
// #DEFINE INT LONG LONG IS USED IN TEMPLATE.  
// USE FFTCONV FOR FINDING PRODUCT OF POLYNOMIALS.
// If polynomial is of the form a_0+a_1x+a_2x^2+...+a_nx^n then its poly array is of 
// the form poly={a_0,a_1,a_2,..a_n} poly[0]=a_0.
// While multiplying polynomials p1,p2 of deg n1,n2 after fft if the polynomial obtained 
// is p then resize the p array so that its degree is 
// n1+n2 i.e p.resize((int)p1.size()+(int)p2.size()) on the final result.
// If there are many polynomials that we have to multiply then try to use divide and 
// conquer to do it.

struct cmplx{
    double x, y;
    cmplx() : x(0), y(0) {}
    cmplx(double x, double y) : x(x), y(y) {}
    inline cmplx operator+(const cmplx &r) const { return cmplx(x + r.x, y + r.y); }
    inline cmplx operator-(const cmplx &r) const { return cmplx(x - r.x, y - r.y); }
    inline cmplx operator*(const cmplx &r) const { return cmplx(x * r.x - y * r.y, x * r.y + y * r.x); }
    inline cmplx conj() const { return cmplx(x, -y); }
};
int fftbase = 1;
vector<cmplx> fftrts = {{0, 0}, {1, 0}};
vector<int> fftrev = {0, 1};
void ensure_base(int nbase) {
    if (nbase <= fftbase) return;
    fftrev.resize(1 << nbase);
    fftrts.resize(1 << nbase);
    for (int i = 0; i < (1 << nbase); i++) {
        fftrev[i] = (fftrev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    while (fftbase < nbase) {
        double angle = M_PI * 2.0 / (1 << (fftbase + 1));
        for (int i = 1 << (fftbase - 1); i < (1 << fftbase); i++) {
            fftrts[i << 1] = fftrts[i];
            double angle_i = angle * (2 * i + 1 - (1 << fftbase));
            fftrts[(i << 1) + 1] = {cos(angle_i), sin(angle_i)};
        }
        ++fftbase;
    }
}
void fft(int n, vector<cmplx> &a) {
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = fftbase - zeros;
    for (int i = 0; i < n; i++) {
        if (i < (fftrev[i] >> shift)) {
            swap(a[i], a[fftrev[i] >> shift]);
        }
    }
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                cmplx z = a[i + j + k] * fftrts[j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] = a[i + j] + z;
            }
        }
    }
}
template<typename T>
std::vector<cmplx> conv_cmplx(const std::vector<T> &a, const std::vector<T> &b)
{
    int N = 1;
    while (N < (int)a.size() + (int)b.size()) N *= 2;
    std::vector<cmplx> a_(N), b_(N);
    for (int i = 0; i < (int)a.size(); i++) a_[i] = {double(a[i]), 0};
    fft(N, a_);
    if (a == b) b_ = a_;
    else {
        for (int i = 0; i < (int)b.size(); i++) b_[i] = {double(b[i]), 0};
        fft(N, b_);
    }
    for (int i = 0; i < N; i++) a_[i] = a_[i] * b_[i];
    reverse(a_.begin() + 1, a_.end());
    fft(N, a_);
    for (int i = 0; i < N; i++) a_[i].x /= N, a_[i].y /= N;
    return a_;
}
template<typename T>
std::vector<long long int> fftconv(const std::vector<T> &a, const std::vector<T> &b)
{
    std::vector<cmplx> ans = conv_cmplx(a, b);
    std::vector<long long int> ret(ans.size());
    for (int i = 0; i < (int)ans.size(); i++) ret[i] = llround(ans[i].x);
    return ret;
}

signed main(void)
{
    vector<long long> poly1(4);
    poly1[3]=1; poly1[2]=1; poly1[1]=1; poly1[0]=1;
    vector<long long> ans=fftconv(poly1,poly1);
    // ans stores the product.
    return 0;
}