#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int B = 40320;
const int A = 8;

typedef vector<int > vi;
typedef vector<bool> vb;

vi factor(A, 1);
vb marked(B, 0);
vi prv(B, -1);
vi opr(B, -1);
 
int perToIdx(vi  per) {
  int idx = 0;
  for (int i = 0; i < A; i++) {
    int cnt = 0;
    for (int j = i + 1; j < A; j++)
      if (per[i] > per[j])
        cnt++;
    idx += cnt * factor[A - i - 1];
  }
  return idx;
} 

int cost(vi usd, int i, int j) {
  int cnt = 0;
  for (int k = 0; k < A; k++)
    if (!usd[k] && j < k)
      cnt++;
  return cnt * factor[A - i - 1];
}

vi  idxToPer(int idx) {
  int val = B - idx - 1;
  int cst = 0 ;
  vi per(A, 0); 
  vi usd(A, 0);
  for (int i = 0; i < A; i++) {
    for (int j = A - 1; j >= 0; j--) {
      cst = cost(usd, i, j);
      if (!usd[j] && val >= cst)
        per[i]  = j;
    }
    val -= cost(usd, i, per[i]);
    usd[per[i]] = 1;
  }
  return per;
}

int operationA(vi per) {
  vi ans(per);
  for (int i = 0; i < A; i++)
    ans[i] = per[(i + A / 2) % A];
  reverse(ans.begin(), ans.begin() + A / 2);
  reverse(ans.begin()  +  A / 2, ans.end());
  return perToIdx(ans);
}

int operationB(vi per) {
  vi ans(per);
  for (int i = 0; i < A / 2; i++)
    ans[i] = per[(i - 1 + A / 2) % (A / 2)];
  for (int i = A / 2; i < A; i++)
    ans[i] = per[(i + 1) % (A / 2) + A / 2];
  return perToIdx(ans);
}

int operationC(vi per) {
  vi ans(per);
  ans[1] = per[6];
  ans[2] = per[1];
  ans[5] = per[2];
  ans[6] = per[5];
  return perToIdx(ans);
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
    vi  per = idxToPer(x);
    nxt = operationA(per);
    if (!marked[nxt]) {
      prv[nxt] = x;
      opr[nxt] = 0;
      q.push( nxt);
      marked[nxt] = 1;
    }
    nxt = operationB(per);
    if (!marked[nxt]) {
      prv[nxt] = x;
      opr[nxt] = 1;
      q.push( nxt);
      marked[nxt] = 1;
    }
    nxt = operationC(per);
    if (!marked[nxt]) {
      prv[nxt] = x;
      opr[nxt] = 2;
      q.push( nxt);
      marked[nxt] = 1;
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
  vi data(A, 0);
  for (int i = 0; i < A;  i++)
    cin >> data[i], data[i]--;
  for (int i = 1; i < A;  i++)
    factor[i] = i * factor[i - 1];
  vi ans = getans(bfs(perToIdx(data)));
  cout << ans.size() << endl;
  for (auto i: ans)
    cout << (char)(i + 'A') << " ";
  cout << endl;
  return 0;
}
