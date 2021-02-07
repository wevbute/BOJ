#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;
typedef complex<double> cpx;

const double pi = acos(-1);

int _N;
deque<int> _X, _Y;

vector<cpx> operator*(vector<cpx> a, vector<cpx> b);
void fft(vector<cpx> &f, cpx w);

int main(void)
{
    scanf("%d", &_N);
    _X.assign(2 * _N, 0), _Y.assign(_N, 0);
    for (int i = 0; i < _N; i++) scanf("%d", &_X[i]), _X[i + _N] = _X[i];
    for (int i = _N - 1; i >= 0; i--) scanf("%d", &_Y[i]);

    vector<cpx> a, b;
    for (auto it : _X) a.push_back(cpx(it, 0));
    for (auto it : _Y) b.push_back(cpx(it, 0));

    vector<cpx> c = a * b;

    lli ans = 0;
    for (auto it : c) ans = max(ans, (lli)round(it.real()));
    printf("%d", ans);
    return 0;
}

vector<cpx> operator*(vector<cpx> a, vector<cpx> b)
{
    int n;
    for (n = 1; n <= a.size() || n <= b.size(); n <<= 1);
    n <<= 1;
    a.resize(n), b.resize(n);

    vector<cpx> ret(n);
    cpx w(cos(2 * pi / n), sin(2 * pi / n));
    fft(a, w), fft(b, w);
    for (int i = 0; i < n; i++) ret[i] = a[i] * b[i];
    fft(ret, cpx(1, 0) / w);
    for (int i = 0; i < n; i++)
    {
        ret[i] /= cpx(n, 0);
        ret[i] = cpx(round(ret[i].real()), round(ret[i].imag()));
    }
    return ret;
}

void fft(vector<cpx> &f, cpx w)
{
    int n = f.size();
    if (n == 1) return;
    vector<cpx> ev(n >> 1), od(n >> 1);
    for (int i = 0; i < n; i++)
    {
        if (i & 1) od[i >> 1] = f[i];
        else ev[i >> 1] = f[i];
    }
    fft(ev, w * w), fft(od, w * w);
    cpx wp(1, 0);
    for (int i = 0; i < n / 2; i++)
    {
        f[i] = ev[i] + wp * od[i];
        f[i + n / 2] = ev[i] - wp * od[i];
        wp *= w;
    }
}