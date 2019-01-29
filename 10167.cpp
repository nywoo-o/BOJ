#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;

vector<int> xx, yy;
vector<pair<pair<int, int>, int>> gold;
int N, x, y, w;
vector<pair<int, int>> pos[3001];

ll res = -1e18;
ll seg[4 * 3001][4];
//0 : sum, 1 : prefixsum , 2: suffix , 3: max

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> x >> y >> w;
		xx.push_back(x);
		yy.push_back(y);
		gold.push_back({ { x, y }, w });
	}
	xx.push_back(-1);
	yy.push_back(-1);
	sort(xx.begin(), xx.end());
	xx.resize(unique(xx.begin(), xx.end()) - xx.begin());
	sort(yy.begin(), yy.end());
	yy.resize(unique(yy.begin(), yy.end()) - yy.begin());

	for (int i = 0; i < N; ++i) {
		x = lower_bound(xx.begin(), xx.end(), gold[i].first.first) - xx.begin();
		y = lower_bound(yy.begin(), yy.end(), gold[i].first.second) - yy.begin();
		w = gold[i].second;
		pos[y].push_back({ x, w });
	}

	int sz = 1;
	while (sz < N) sz <<= 1;

	for (int i = 1; i < yy.size(); ++i) {
		memset(seg, 0, sizeof(seg));

		for (int j = i; j < yy.size(); ++j) {
			for (int k = 0; k < pos[j].size(); ++k) {
				int node = sz + pos[j][k].first; w = pos[j][k].second;
				seg[node][0] += w;
				while (node >>= 1) {
					int l = node * 2, r = node * 2 + 1;
					seg[node][0] = seg[l][0] + seg[r][0];
					seg[node][1] = max(seg[l][0] + seg[r][1], seg[l][1]);
					seg[node][2] = max(seg[l][2] + seg[r][0], seg[r][2]);
					seg[node][3] = max(seg[node][0], max(seg[node][1], max(seg[node][2], seg[l][3])));
					seg[node][3] = max(seg[node][3], max(seg[r][3], seg[l][2] + seg[r][1]));
				}
			}
			res = max(res, seg[1][3]);
		}
	}

	cout << res;
	return 0;
}
