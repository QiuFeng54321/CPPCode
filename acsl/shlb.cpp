#include <iostream>
#include <string>

void B(int length, int width) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      std::cout << '*';
    }
    std::cout << std::endl;
  }
}

void H(int height) {
  for (int i = 0; i < height; i++) {
    for (int e = 0; e < i; e++) {
      std::cout << ' ';
    }
    for (int s = 0; s < height - i; s++) {
      std::cout << '*';
    }
    std::cout << std::endl;
  }
}

void L(int height) {
  for (int i = 0; i < height; i++) {
    for (int s = 0; s < height - i; s++) {
      std::cout << '*';
    }
    std::cout << std::endl;
  }
}

void S(int height) { B(height, height); }

int main() {
  char type, split;
  int height, length;
  for (int i = 0; i < 4; i++) {
    std::cin >> type >> split >> height;
    if (type == 'B') std::cin >> split >> length;
    switch (type) {
      case 'S':
        S(height);
        break;
      case 'H':
        H(height);
        break;
      case 'L':
        L(height);
        break;
      case 'B':
        B(height, length);
        break;
    }
  }
}