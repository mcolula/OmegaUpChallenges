#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <set>

using namespace std;

bool des_ord(char a, char b) { return a > b; } 

int asc(int number) {
  string num_str = to_string(number);
  sort(num_str.begin(), num_str.end());
  int new_num = stoi(num_str);
  return new_num;
}

int des(int number) {
  string num_str = to_string(number);
  sort(num_str.begin(), num_str.end(), des_ord);
  int new_num = stoi(num_str);
  return new_num;
}

int main() {
  int number = 0;
  int i, a, d;
  set<int> nums;
  scanf("%d", &number);
  while(number != 0) {
    i = 1;
    do {
      number = des(number) - asc(number);
      if((nums.find(number) != nums.end()))
        break;
      nums.insert(number);
      i++;
    } while(true);
    nums.clear();
    printf("Chain length %d\n", i);
    scanf("%d", &number);
  }
  return 0;
}
