/*
lis�ر��
memset���Ǹ���ӣ������ϸ�δ��֮�վ�����Ϊ��
memsetֻ�ܸ���1���ֽڣ�����ĵڶ�������ֻ����һ���ֽڣ�����û��
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

#pragma warning(disable:4996)
#define N 40000+41
#define INF 1e8
using namespace std;

int t, n;
int f[N];

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int k, ma = 0, idx;
		memset(f, 0x3f3f3f3f, sizeof(int) * N);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &k);
			idx = upper_bound(f + 1, f + 1 + i, k) - f;
			ma = max(ma, idx);
			f[idx] = k;
		}

		printf("%d\n", ma);
	}
	return 0;
}