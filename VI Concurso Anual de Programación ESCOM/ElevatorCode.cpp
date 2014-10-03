#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>  
#include <cmath>

using namespace std;

typedef struct { 
  bool pos;
  int  val;
  int  sz;
} num;

int create(num * n, bool pos, int sz) {
  n->pos = pos;
  n->sz  = sz;
  n->val = 0;
  return 0;
}

int update(num * n, int  val) {
  if(n->sz <= 0)
    return -1;
  n->val += val * pow(10, --(n->sz));
  return 0;
}


bool operator<(const num & a, const num & b) {
  if(!a.pos && b.pos)
    return true;
  if(a.pos && !b.pos)
    return false;
  return a.sz < b.sz;
}

int max_val(const char * expr, char * nums, int sz) {
  priority_queue<num> pq;
  int i = 0;
  int j = 0;
  bool pos = true;
  num n;
  while(i < strlen(expr)) {
    if(expr[i] == '-') {
      if(j > 0) {
        create(&n, pos, j);
        pq.push(n);
      }
      pos = false;
      j = -1;
    }
    else if(expr[i] == '+') {
      if(j > 0) {
        create(&n, pos, j);
        pq.push(n);
      }
      pos = true;
      j = -1;
    }
    i++;
    j++;
  }
  create(&n, pos, j);
  pq.push(n);
  
  int max_sum = 0;
  sort(nums, nums + sz);
  i =  0;
  j = sz - 1;
  while(i <= j) {
    n = pq.top();
    pq.pop();
    if(n.pos) {
      update(&n, nums[j] - '0');
      j--;
      if(n.sz == 0)
        max_sum += n.val;
      else
        pq.push(n);
    }
    else {
      update(&n, nums[i] - '0');
      i++;
      if(n.sz == 0)
        max_sum -= n.val;
      else
        pq.push(n);
    }
  }
  return max_sum;
}

int main(int argc, char **argv) {
  int n;
  scanf("%d", &n);
  char expr[500];
  char nums[500];
  while(n--) {
    scanf("%s", expr);
    scanf("%s", nums);
    printf("%d\n", max_val(expr, nums, strlen(nums))); 
  }
  return 0;
}
