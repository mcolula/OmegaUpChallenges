#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int n = 0;
  scanf("%d", &n);
  while(n != 0) {
    int  msge[n];
    char msgc[n];
    char msgf[n];
    for(int i = 0; i < n; i++)
      scanf("%02X", &msge[i]);
    cin.ignore();
    cin.read(msgc, n);
    cin.ignore();
    cin.read(msgf, n);
    cin.ignore();
    for(int i = 0; i < n; i++)
        printf("%02X ", msge[i] xor msgc[i] xor msgf[i]);
    printf("\n");
    scanf("%d", &n);
  }
}
