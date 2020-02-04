/*
λ����, ����
һ������Ϊmaskû�н�ȡ��6λ
��һ������Ϊû�п���ȫ��
*/
#include <iostream>
#include <algorithm>

using namespace std;

int t;
int gin[5];
int gbak[5];
int gout[5];

void read() {
	int tmp;
	for (int i = 0; i < 5; i++) {
		gin[i] = 0;
		for (int j = 0; j < 6; j++) {
			cin >> tmp;
			gin[i] = gin[i] << 1;
			gin[i] += tmp;
		}
		gbak[i] = gin[i];
	}
}

void solve(int mask) {
	for (int i = 0; i < 5; i++) {
		gout[i] = mask;
		if(i - 1 >= 0)
			gin[i - 1] = gin[i - 1] ^ mask;
		gin[i] = gin[i] ^ mask;
		gin[i] = gin[i] ^ (mask << 1) & 63;
		gin[i] = gin[i] ^ (mask >> 1) & 63;
		if (i + 1 <= 4)
			gin[i + 1] = gin[i + 1] ^ mask & 63;
		mask = gin[i];
	}
}

void print() {
	for (int i = 0; i < 5; i++) {
		for (int j = 5; j >= 0; j--) {
			cout << ((gout[i] >> j) & 1) << ' ';
		}
		cout << endl;
	}
}


int main() {
	cin >> t;
	for (int k = 1; k <= t; k++) {
		read();
		int mask = 0;
		while (mask != (1 << 6)) {
			solve(mask);
			if (gin[4] == 0)
				break;
			for (int i = 0; i < 5; i++)
				gin[i] = gbak[i];
			mask++;
		}
		cout << "PUZZLE #" << k << endl;
		print();
	}
	return 0;
}