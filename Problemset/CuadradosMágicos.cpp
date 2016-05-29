#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


const int B = 40320;
const int A = 8;


typedef vector<int > vi;
typedef vector<bool> vb;
vi factor(A, 1);


int perToIdx(vi  per) {
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



int main() {
  for (int i = 1; i < A; i++)
    factor[i] = i * factor[i - 1];
  for (int i = B - 1; i >= B - 20; i--) {
    for (auto j: idxToPer(i))
      cout << j << " ";
    cout << endl;
  }
  return 0;
}
