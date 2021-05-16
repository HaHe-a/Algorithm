#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 1e6 + 10;

struct Edge {
    int to, flow, nxt;

    Edge() {}

    Edge(int to, int nxt, int flow) : to(to), nxt(nxt), flow(flow) {}
} edge[maxn << 1];

int head[maxn], dep[maxn];
int S, T;
int N, n, m, tot;

void Init(int n) {  //n为点的总个数+1
    N = n;
    memset(head, -1, sizeof head);
    tot = 0;
}

void addedge(int u, int v, int w, int rw = 0) {
    edge[tot] = Edge(v, head[u], w);
    head[u] = tot++;
    edge[tot] = Edge(u, head[v], rw);
    head[v] = tot++;
}

bool BFS() {
    for (int i = 0; i < N; ++i) {
        dep[i] = -1;
    }
    queue<int> q;
    q.push(S);
    dep[S] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; ~i; i = edge[i].nxt) {
            if (edge[i].flow && dep[edge[i].to] == -1) {
                dep[edge[i].to] = dep[u] + 1;
                q.push(edge[i].to);
            }
        }
    }
    return dep[T] != -1;
}

int DFS(int u, int f) {
    if (u == T || f == 0) return f;
    int w, used = 0;
    for (int i = head[u]; ~i; i = edge[i].nxt) {
        if (edge[i].flow && dep[edge[i].to] == dep[u] + 1) {
            w = DFS(edge[i].to, min(f - used, edge[i].flow));
            edge[i].flow -= w;
            edge[i ^ 1].flow += w;
            used += w;
            if (used == f) return f;
        }
    }
    if (!used) dep[u] = -1;
    return used;
}

int Dicnic() {
    int ans = 0;
    while (BFS()) {
        ans += DFS(S, INF);
    }
    return ans;
}

int main() {
    scanf("%d %d", &m, &n);
    S = 0, T = n + 1;
    Init(T + 1);
    int u, v;
    for (int i = 1; i <= m; ++i) {
        addedge(S, i, 1);
    }
    for (int i = m + 1; i <= n; ++i) {
        addedge(i, T, 1);
    }
    while (~scanf("%d %d", &u, &v)) {
        if (u == -1 && v == -1) break;
        addedge(u, v, 1);
    }
    int res = Dicnic();
    printf("%d\n", res);
    for (int i = 0; i < tot; i += 2) {
        if (edge[i].to == S || edge[i ^ 1].to == S) continue;
        if (edge[i].to == T || edge[i ^ 1].to == T) continue;
        if (edge[i].flow == 0) {
            printf("%d %d\n", edge[i].to, edge[i ^ 1].to);
        }
    }
    return 0;
}