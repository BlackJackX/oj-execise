/*
 * Dinic algo for max flow
 *
 * This implementation assumes that #nodes, #edges, and capacity on each edge <= INT_MAX,
 * which means INT_MAX is the best approximation of INF on edge capacity.
 * The total amount of max flow computed can be up to LLONG_MAX (not defined in this file),
 * but each 'dfs' call in 'dinic' can return <= INT_MAX flow value.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>

#define N (5000+2)
#define M (N*N+4*N)
#define INF 0x3f3f3f3f

typedef long long LL;

using namespace std;

struct edge {
	int v, cap, next;
};
edge e[M];

int head[N], level[N], cur[N];
int num_of_edges;

/*
 * When there are multiple test sets, you need to re-initialize before each
 */
void dinic_init(void) {
	num_of_edges = 0;
	memset(head, -1, sizeof(head));
	return;
}

int add_edge(int u, int v, int c1, int c2) {
	int& i = num_of_edges;

	assert(c1 >= 0 && c2 >= 0 && c1 + c2 >= 0); // check for possibility of overflow
	e[i].v = v;
	e[i].cap = c1;
	e[i].next = head[u];
	head[u] = i++;

	e[i].v = u;
	e[i].cap = c2;
	e[i].next = head[v];
	head[v] = i++;
	return i;
}

void print_graph(int n) {
	for (int u = 0; u < n; u++) {
		printf("%d: ", u);
		for (int i = head[u]; i >= 0; i = e[i].next) {
			printf("%d(%d)", e[i].v, e[i].cap);
		}
		printf("\n");
	}
	return;
}

/*
 * Find all augmentation paths in the current level graph
 * This is the recursive version
 */
int dfs(int u, int t, int bn) {
	if (u == t) return bn;
	int left = bn;
	for (int& i = cur[u]; i >= 0; i = e[i].next) {
		int v = e[i].v;
		int c = e[i].cap;
		if (c > 0 && level[u] + 1 == level[v]) {
			int flow = dfs(v, t, min(left, c));
			if (flow > 0) {
				e[i].cap -= flow;
				e[i ^ 1].cap += flow;
				cur[u] = i;
				left -= flow;
				if (!left) break;
			}
		}
	}
	if (left > 0) level[u] = 0;
	return bn - left;
}

bool bfs(int s, int t) {
	memset(level, 0, sizeof(level));
	level[s] = 1;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == t) return true;
		for (int i = head[u]; i >= 0; i = e[i].next) {
			int v = e[i].v;
			if (!level[v] && e[i].cap > 0) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return false;
}

LL dinic(int s, int t) {
	LL max_flow = 0;

	while (bfs(s, t)) {
		memcpy(cur, head, sizeof(head));
		max_flow += dfs(s, t, INT_MAX);
	}
	return max_flow;
}

int upstream(int s, int n) {
	int cnt = 0;
	vector<bool> visited(n);
	queue<int> q;
	visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i >= 0; i = e[i].next) {
			int v = e[i].v;
			if (e[i].cap > 0 && !visited[v]) {
				visited[v] = true;
				q.push(v);
				cnt++;
			}
		}
	}
	return cnt; // excluding s
}

int n, m;

int main() {
	cin >> n >> m;
	dinic_init();
	int a, b, sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		if (a > 0) {
			add_edge(0, i, a, 0);
			sum += a;
		}
		else
			add_edge(i, n + 1, -1 * a, 0);
	}
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		add_edge(a, b, INF, 0);
	}
	int mincut = dinic(0, n + 1);
	int num = 0;
	for (int i = head[0]; i >= 0; i = e[i].next) {
		if (e[i].cap != 0)
			num++;
	}
	for (int i = head[n + 1]; i >= 0; i = e[i].next) {
		if(e[i].cap != )
	}
	cout << sum - mincut << endl;


	return 0;
}