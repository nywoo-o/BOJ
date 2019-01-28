#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <vector>
using namespace std;

int s[50001], seg[100001*4];
int seq, N;
int res = 0;
set<pair<int, int>> st;

void update(int node, int x, int y, int pos, int val) {
	if (x > pos || pos > y) return;
	if (x == y) {
		seg[node] += val; return;
	}
	int mid = (x + y) >> 1;
	update(node * 2, x, mid, pos, val);
	update(node * 2 + 1, mid + 1, y, pos, val);
	seg[node] = seg[node * 2] + seg[node * 2 + 1];
}

int query(int node, int x, int y, int l, int r) {
	if (x > r || y < l) return 0;
	if (l <= x && y <= r) return seg[node];
	int mid = (x + y) >> 1;
	return query(node * 2, x, mid, l, r) + query(node * 2 + 1, mid + 1, y, l, r);
}
int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 1; i <= 2 * N; ++i) {
		cin >> seq;
		if (s[seq]) {
			update(1, 1, 2 * N, s[seq], -1);
			res += query(1, 1, 2 * N, s[seq], i);
		}
		else {
			update(1, 1, 2 * N, i, 1);
			s[seq] = i;
		}
	}


	cout << res;
}
