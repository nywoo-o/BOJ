#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <vector>
#include <array>
#include <list>
using namespace std;
typedef long long ll;
#define LL long long
//1. 전체 cross 쌍의 갯수 세기
//2. i-k-1 >= 1인 경우에 2d seg[s[i-k-1], e[i-k-1]]를 1 증가시킴
//   2d seg tree에 ([s[i], e[i]], [end, 0]) 안에 있는 개수를 세서 전체에서 뺄거임


int N, K;
ll allCross, KCross;
int s[100001], e[100001], se[100001];
int numS[100001], numE[100001];
vector<int> seg[100001 * 4];
vector<ll> bitForSeg[100001 * 4];

ll sum(int i, int cur) {
	ll ans = 0;
	while (i > 0) {
		ans += bitForSeg[cur][i];
		i -= (i & -i);
	}
	return ans;
}

void update(int i, int diff, int cur) {
	while (i < bitForSeg[cur].size()) {
		bitForSeg[cur][i] += diff;
		i += (i & -i);
	}
}


void init(int cur, int l, int r) {
	if (l == r) {
		bitForSeg[cur].resize(2);//BIT는 1부터 인덱스가 시작해야함
		seg[cur].push_back(se[l]);
		return;
	}

	int mid = (l + r) >> 1;
	init(cur * 2, l, mid);
	init(cur * 2 + 1, mid + 1, r);

	seg[cur].resize(r - l + 1);
	bitForSeg[cur].resize(r - l + 2);
	merge(seg[cur * 2].begin(), seg[cur * 2].end(), seg[cur * 2 + 1].begin(), seg[cur * 2 + 1].end(), seg[cur].begin());
	sort(seg[cur].begin(), seg[cur].end());
	return;
}

int query(int node, int l, int r, int x, int y, int k, int mode) {
	if (l > y || x > r) return 0;
	if (x <= l && r <= y) {
		if (mode == 0) {//k보다 작은 것
			if (k < seg[node][0]) return 0;
			int position = lower_bound(seg[node].begin(), seg[node].end(), k) - seg[node].begin();
			if (position != r - l + 1 && k < seg[node][position]) position--;
			if (position != r - l + 1) position++;
			return sum(position, node);
		}
		else {//k보다 큰 것
			int position = lower_bound(seg[node].begin(), seg[node].end(), k) - seg[node].begin();
			if (position == r - l + 1) return 0;
			return sum(bitForSeg[node].size()-1, node) - sum(position, node);
		}
	}

	int mid = (l + r) / 2;
	return query(node * 2, l, mid, x, y, k, mode) + query(node * 2 + 1, mid + 1, r, x, y, k, mode);
}

void updateSeg(int node, int l, int r, int pos, int k) {
	if (l > pos || pos > r) return;
	if (l == r) {
		update(1, 1, node);
		return;
	}
	int mid = (l + r) >> 1;
	int position = lower_bound(seg[node].begin(), seg[node].end(), k) - seg[node].begin() + 1;
	update(position, 1, node);
	updateSeg(node * 2, l, mid, pos, k);
	updateSeg(node * 2 + 1, mid + 1, r, pos, k);
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> N >> K;
	for (int i = 1; i <= N; ++i) {
		cin >> s[i];
		numS[s[i]] = i;
	}

	for (int i = 1; i <= N; ++i) {
		cin >> e[i];
		numE[e[i]] = i;
	}

	for (int i = 1; i <= N; ++i) {
		se[numS[i]] = numE[i];
	}

	init(1, 1, N);

	for (int cow = K+2; cow <= N; ++cow) {
		updateSeg(1, 1, N, numS[cow-K-1], numE[cow-K-1]);
		
		KCross += query(1, 1, N, numS[cow], N, numE[cow], 0);
		KCross += query(1, 1, N, 1, numS[cow], numE[cow], 1);
	}

	cout << KCross;

	return 0;
}
