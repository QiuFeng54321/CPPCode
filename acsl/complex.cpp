#include <cmath>
#include <iostream>
using namespace std;
double z, i, f2[505][2], f[505][2];
int e, c;
void print_complex(double* c) {
    cout << c[0] << (c[1] < 0 ? "" : "+") << c[1] << "i" << endl;
}
double round2(double d) {
    // cout << "Pre: " << d << endl;
    bool negative = d < 0;
    auto d100 = d * 100;
    if (negative)
        if (d100 - int(d100))
    return int(d * 100) / 100.0;
}
bool find(int count) {
  f[count + 1][0] = round2(
      (f[count][0] * f[count][0] - f[count][1] * f[count][1]) + f[1][0]);
  f[count + 1][1] = round2(f[count][0] * f[count][1] * 2 + f[1][1]);
  print_complex(f[count + 1]);

  // cout << f[count][0] << " " << f[count][1] << " " << f[count+1][0] << " " <<
  // f[count+1][1] << endl;

//   f2[count + 1][0] = (int)(f[count + 1][0]);
//   f2[count + 1][1] = (int)(f[count + 1][1]);

//   if ((f[count + 1][0] - f2[count + 1][0]) >= 0.5)
//     f2[count + 1][0] = (int)(f[count + 1][0]) + 1;
//   else if ((f[count + 1][0] - f2[count + 1][0]) <= -0.5)
//     f2[count + 1][0] = (int)(f[count + 1][0]) - 1;

//   if ((f[count + 1][1] - f2[count + 1][1]) >= 0.5)
//     f2[count + 1][1] = (int)(f[count + 1][1]) + 1;
//   else if ((f[count + 1][1] - f2[count + 1][1]) <= -0.5)
//     f2[count + 1][1] = (int)(f[count + 1][1]) - 1;

  if (f[count + 1][0] == f[1][0] && f[count + 1][1] == f[1][1]) {
    c = count--;
    cout << c << endl;
    return true;
  }

  if (sqrt(pow(double(f[count + 1][0]), 2) +
           pow(double(f[count + 1][1]), 2)) > 4) {
    e = count - 1;
    cout << "ESCAPES " << e << endl;
    return true;
  }

  // printf("%.f %.f\n",f2[count+1][0],f2[count+1][1]);
  // if (count > 5) return;
  return false;
}
int main() {
  scanf("%lf%lf", &z, &i);
  f[1][0] = round2(z);
  f[1][1] = round2(i);
  // cout << f[1][0] <<  " " << f[1][1] << endl;
  f2[1][0] = round2(z);
  f2[1][1] = round2(i);
  // printf("%.2lf %.2lf\n",f2[1][0],f2[1][1]);
  e = 0;
  c = 0;
  for (int i = 1; i < 20; i++) {
      if (find(i)) break;
  }
  return 0;
}