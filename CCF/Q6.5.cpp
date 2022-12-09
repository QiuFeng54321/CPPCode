#include <iostream>

const int N = 100002;
int n, m, ind = 0;
int City[N * 10], Next[N * 10], Head[N], Tail[N];
void add(int a, int b) {
  City[++ind] = b;
  if (Head[a] == 0)
    Head[a] = ind;
  else
    Next[Tail[a]] = ind;
  Tail[a] = ind;
}
int main() {
  std::cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int c1, c2;
    std::cin >> c1 >> c2;
    add(c1, c2);
    add(c2, c1);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = Head[i]; j; j = Next[j]) {
      std::cout << City[j] << " ";
    }
    std::cout << std::endl;
  }
}