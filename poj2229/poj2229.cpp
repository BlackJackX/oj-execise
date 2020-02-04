/*
��ȫ����
��Ʒ����Ϊ1��2��4��8
����ֵ��Ϊ������
��ȫ�����ĺ����ǣ�
n����Ʒ�������ޣ�����ã���һ���������ƣ�
��dp[i][j]������dp[i-1][j]��dp[i-1][j-w[i]]

���Ƶķ�ʽ�Լ��ú����룡����
û����ô����
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

#define N 1000010
#define INF 0x3f3f3f3f
#define MOD 1000000000
#pragma warning(disable:4996)

using namespace std;

int n, k;
int dp[N];
int a[N];

int main() {
	/*
	cin >> n;
	for (k = 0; 1 << k <= n; k++) {
		a[k] = 1 << k;
	}
	dp[0] = 1;
	for (int i = 0; i < k; i++) {
		for (int j = a[i]; j <= n; j++) {
			dp[j] = (dp[j] + dp[j - a[i]]) % MOD;
		}
	}
	cout << dp[n] << endl;
	return 0;
	*/
	cin >> n;
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		if (i % 2 == 1)
			dp[i] = dp[i - 1];
		else
			dp[i] = dp[i - 2] + dp[i / 2];

		dp[i] %= MOD;
	}
	cout << dp[n] << endl;
	return 0;
}
