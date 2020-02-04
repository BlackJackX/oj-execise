#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdio>


#define N 100005

#pragma warning(disable:4996)

using namespace std;

//knd=0为和父相同.为不同
int par[N], knd[N];

int t, n, m, a, b;
char c;

void initSet(int n) {
	for (int i = 0; i <= n; i++) {
		par[i] = i;
		knd[i] = 0;
	}
}

int findSet(int x) {
	if (par[x] == x)
		return x;
	else {
		int px = par[x];
		par[x] = findSet(par[x]);
		knd[x] = (knd[x] + knd[px]) % 2;
		return par[x];
	}
}

void divSet(int x, int y) {
	int px = findSet(x);
	int py = findSet(y);
	
	par[px] = py;
	knd[px] = (knd[x] + 1 + knd[y]) % 2;
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%*c", &n, &m);
		initSet(n);

		for (int i = 0; i < m; i++) {
			scanf("%c%d%d%*c", &c, &a, &b);
			if (c == 'A') {
				int pa = findSet(a);
				int pb = findSet(b);
				if (pa == pb && knd[a] == knd[b]) {
					printf("In the same gang.\n");
				}
				else if (pa == pb && knd[a] != knd[b]) {
					printf("In different gangs.\n");
				}
				else {
					printf("Not sure yet.\n");
				}
			}
			else
				divSet(a, b);
		}
	}
	return 0;
}