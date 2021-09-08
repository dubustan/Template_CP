const int somod = (119 << 23 | 1);
const int maxn = 1 << 21;
const int LG = 21;

int rts[maxn + 1], rev[maxn], n;

int Add(int a, int b)
{
    a += b;
    if(a >= somod) a -= somod;
    if(a < 0) a += somod;
    return a;
}

int Mul(int a, int b)
{
    return 1ll * a * b % somod;
}

int Pow(int a, int b)
{
    int ans = 1;
    for(; b > 0; b >>= 1)
    {
        if(b & 1) ans = Mul(ans, a);
        a = Mul(a, a);
    }
    return ans;
}

void Prepare()
{
    for(int i = 0; i < maxn; i++)
        for(int j = 0; j < LG; j++)
            if(i >> j & 1) rev[i] |= (1 << LG - j - 1);
    int z = Pow(3, (somod - 1) / maxn);
    rts[0] = 1;
    for(int i = 1; i <= maxn; i++) rts[i] = Mul(rts[i - 1], z);
}

void fft(vector<int> &a, int sgn)
{
    int N = a.size(), u, v;
    int d = LG - __lg(N);
    for(int i = 0; i < N; i++)
        if(i < (rev[i] >> d)) swap(a[i], a[rev[i] >> d]);
    for(int len = 2; len <= N; len <<= 1)
    {
        int delta = maxn / len * sgn;
        for(int i = 0; i < N; i += len)
        {
            int *w = (sgn > 0 ? rts : rts + maxn);
            for(int j = 0; j < len / 2; j++)
            {
                u = a[i + j];
                v = Mul(*w, a[i + j + len / 2]);
                a[i + j] = Add(u, v);
                a[i + j + len / 2] = Add(u, -v);
                w += delta;
            }
        }
    }
    if(sgn == -1)
    {
        int cc = Pow(N, somod - 2);
        for(int i = 0; i < N; i++) a[i] = Mul(a[i], cc);
    }
}

vector<int> Multiply(vector<int> a, vector<int> b)
{
    int na = a.size(), nb = b.size(), cc = 1;
    while(cc < max(a.size(), b.size())) cc <<= 1;
    cc <<= 1;
    a.resize(cc);
    b.resize(cc);
    fft(a, 1);
    fft(b, 1);
    for(int i = 0; i < cc; i++) a[i] = Mul(a[i], b[i]);
    fft(a, -1);
    a.resize(na + nb - 1);
    return a;
}
