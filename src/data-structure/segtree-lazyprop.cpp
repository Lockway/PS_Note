using ll = long long;
struct segment {
#ifdef ONLINE_JUDGE
  const int TSIZE = 1 << 20;  // always 2^k form && n <= TSIZE
#else
  const int TSIZE = 1 << 3;  // always 2^k form && n <= TSIZE
#endif
  vector<ll> segtree, prop, dat;
  segment(ll n) {
    segtree.resize(TSIZE * 2);
    prop.resize(TSIZE * 2);
    dat.resize(n);
  }
  void seg_init(int nod, int l, int r) {
    if (l == r) {
      segtree[nod] = dat[l];
    } else {
      int m = (l + r) >> 1;
      seg_init(nod << 1, l, m);
      seg_init(nod << 1 | 1, m + 1, r);
      segtree[nod] = segtree[nod << 1] + segtree[nod << 1 | 1];
    }
  }

  void seg_relax(int nod, int l, int r) {
    if (prop[nod] == 0) return;
    if (l < r) {
      int m = (l + r) >> 1;
      segtree[nod << 1] += (m - l + 1) * prop[nod];
      prop[nod << 1] += prop[nod];
      segtree[nod << 1 | 1] += (r - m) * prop[nod];
      prop[nod << 1 | 1] += prop[nod];
    }
    prop[nod] = 0;
  }

  ll seg_query(int nod, int l, int r, int s, int e) {
    if (r < s || e < l) return 0;
    if (s <= l && r <= e) return segtree[nod];
    seg_relax(nod, l, r);
    int m = (l + r) >> 1;
    return seg_query(nod << 1, l, m, s, e) +
           seg_query(nod << 1 | 1, m + 1, r, s, e);
  }

  void seg_update(int nod, int l, int r, int s, int e, int val) {
    if (r < s || e < l) return;
    if (s <= l && r <= e) {
      segtree[nod] += (r - l + 1) * val;
      prop[nod] += val;
      return;
    }
    seg_relax(nod, l, r);
    int m = (l + r) >> 1;
    seg_update(nod << 1, l, m, s, e, val);
    seg_update(nod << 1 | 1, m + 1, r, s, e, val);
    segtree[nod] = segtree[nod << 1] + segtree[nod << 1 | 1];
  }
  // usage:
  // seg_update(1, 0, n ‐ 1, qs, qe, val);
  // seg_query(1, 0, n ‐ 1, qs, qe);
};