#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXP = 40320;
const int MAXN = 8;

typedef vector<int > vi;
typedef vector<bool> vb;

vi factor(MAXN, 1);
vb marked(MAXP, 0);
vi prv(MAXP, -1);
vi opr(MAXP, -1);

int mv[3][8] = {{7, 6, 5, 4, 3, 2, 1, 0},
                {3, 0, 1, 2, 5, 6, 7, 4},
                {0, 6, 1, 3, 4, 2, 5, 7}};
 
int perToIdx(vi  per) {
  int idx = 0;
  for (int i = 0; i < MAXN; i++) {
    int cnt = 0;
    for (int j = i + 1; j < MAXN; j++)
      if (per[i] > per[j])
        cnt++;
    idx += cnt * factor[MAXN - i - 1];
  }
  return idx;
} 

vi  idxToPer(int idx) {
  int val = MAXP - idx - 1;
  vi  per(MAXN, 0), usd(MAXN, 0);
  for (int i = 0; i < MAXN; i++) {
    int cnt  = 0;
    for (int j = MAXN - 1; j >= 0; j--)
      if (!usd[j] && val >= cnt * factor[MAXN - i - 1])
        per[i]  = j;
      if (!usd[j] && val  < cnt * factor[MAXN - i - 1])
        break;
      cnt++;
    }
    val -= (cnt - 1) * factor[MAXN - i - 1];
    usd[per[i]] = 1;
  }
  return per;
}

int bfs(int target, int start = 0) {
  queue<int>  q;
  q.push(start);
  marked[start] = 1;
  while (!q.empty()) {
    int x = q.front(); q.pop();
    if (x == target)
      return  x;
    int nxt = 0;
    vi  per = idxToPer(x), aux(MAXN);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 8; j++)
        aux[j] = per[mv[i][j]];
      int nxt  = perToIdx(aux);
      if (!marked[nxt]) {
        prv[nxt] = x;
        opr[nxt] = i;
        q.push( nxt);
        marked[nxt] = 1;
      }
    }
  }
}

vi getans(int n) {
  vi ans;
  while (prv[n] != -1)
    ans.push_back(opr[n]), n = prv[n];
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  vi data(MAXN, 0);
  for (int i = 0; i < MAXN;  i++)
    cin >> data[i], data[i]--;
  for (int i = 1; i < MAXN;  i++)
    factor[i] = i * factor[i - 1];
  vi ans = getans(bfs(perToIdx(data)));
  cout << ans.size() << endl;
  for (auto i: ans)
    cout << (char)(i + 'A') << " ";
  cout << endl;
  return 0;
}
