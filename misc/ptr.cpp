#include <iostream>
using namespace std;
int main() {
    int a = 365;
    auto b = &a;
    cout << a << " " << &a << endl;
    cout << *b << " " << b << endl;

}