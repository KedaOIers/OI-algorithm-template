#include <bits/stdc++.h>

#define int long long
using namespace std;

const int N = 2e5 + 2, M = 5e5 + 2, INF = 0x3f3f3f3f;
int fa[N];   // fa_i 表示第i号节点的父节点编号
int n, m;    // n个点，m条边

int find(int x)          // 查询x号节点的父节点，并压缩路径
{
    if (x != fa[x]) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

struct Edge {
    int a, b, w;
    bool operator<(const Edge& W) const { return w < W.w; }
} edges[M];
// 边集数组

int kruskal()
{
    sort(edges + 1, edges + m + 1);      // 对边排序
    for (int i = 1; i <= n; i++) {       // 初始化并查集
        fa[i] = i;
    }
    int res = 0, cnt = 0;
    for (int i = 1; i <= m; i++) {
        // auto [a, b, w] = edges[i];    C++17新特性----结构化绑定
        // 等同于下一行
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        a = find(a), b = find(b);
        if (a != b) {          // 查重
            fa[a] = b;         // 只有当a，b不在同一集中时才能加边
            res += w;
            cnt += 1;
        }
    }
    // 判断边的数量----一棵树恒有n个点，n-1条边
    // 如果没有n-1条边，则说明图不连通，没有MST
    if (cnt < n - 1) return INF;
    return res;
}

signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }
    int t = kruskal();
    cout << t << "\n";
    return 0;
}
