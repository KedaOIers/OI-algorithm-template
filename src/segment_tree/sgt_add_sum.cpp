#include <iostream>
#include <memory>
#include <tuple>
#include <utility>
using namespace std;

namespace SegTree
{
    struct SegTree {
        struct Node {
            long long sum;
            long long add;
            int l, r;
            int len() const { return r - l + 1; }
        };
        unique_ptr<Node[]> a;
        int n;

        SegTree(int n, long long arr[]) : n(n)
        {
            a = make_unique<Node[]>(4 * n);
            build(arr, 1, n);
        }

        void build(long long arr[], int l, int r, int id = 1)
        {
            tie(a[id].l, a[id].r) = make_pair(l, r);
            if (l == r) {
                a[id].sum = arr[l];
            } else {
                int mid = (l + r) >> 1;
                build(arr, l, mid, id << 1);
                build(arr, mid + 1, r, id << 1 | 1);
                push_up(id);
            }
        }

        void push_down(int i)
        {
            if (a[i].l == a[i].r) return;
            a[i << 1].sum += a[i << 1].len() * a[i].add;
            a[i << 1].add += a[i].add;
            a[i << 1 | 1].sum += a[i << 1 | 1].len() * a[i].add;
            a[i << 1 | 1].add += a[i].add;
            a[i].add = 0;
        }

        void push_up(int i)
        {
            if (a[i].l == a[i].r) return;
            a[i].sum = a[i << 1].sum + a[i << 1 | 1].sum;
        }

        void update(int l, int r, long long v, int id = 1)
        {
            if (l <= a[id].l && a[id].r <= r) {
                a[id].sum += v * a[id].len();
                a[id].add += v;
            } else {
                int mid = (a[id].l + a[id].r) >> 1;
                push_down(id);
                if (l <= mid) update(l, r, v, id << 1);
                if (mid < r) update(l, r, v, id << 1 | 1);
                push_up(id);
            }
        }

        long long query(int l, int r, int id = 1)
        {
            if (l <= a[id].l && a[id].r <= r) {
                return a[id].sum;
            } else {
                long long sum = 0;
                int mid = (a[id].l + a[id].r) >> 1;
                push_down(id);
                if (l <= mid) sum += query(l, r, id << 1);
                if (mid < r) sum += query(l, r, id << 1 | 1);
                return sum;
            }
        }
    };
}  // namespace SegTree

namespace solve
{
    constexpr int N = 1e5;
    long long a[N], n, q;
    void solve()
    {
        cin >> n >> q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        SegTree::SegTree sgt(n, a);
        while (q--) {
            int op;
            cin >> op;
            if (op == 1) {
                int l, r;
                long long v;
                cin >> l >> r >> v;
                sgt.update(l, r, v);
            } else {
                int l, r;
                cin >> l >> r;
                cout << sgt.query(l, r) << '\n';
            }
        }
    }
}  // namespace solve

int main() { solve::solve(); }
