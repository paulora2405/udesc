#include <bitset>
#include <cmath>
#include <iostream>

using std::bitset;

unsigned int bit_considerados = 4;

bitset<4> bin4(unsigned int a) {
  return bitset<4>(a);
}

bitset<8> bin8(unsigned int a) {
  return bitset<8>(a);
}

std::size_t bin_count(unsigned int n) {
  int count = 0;
  while(n) {
    count++;
    n = n >> 1;
  }
  return count;
}

int multiply(unsigned int x, unsigned int y) {
  int n = std::max(bin_count(x), bin_count(y));
  std::cout << "x=" << x << "\ty=" << y << '\n';

  if(bit_considerados == 4) {
    if(n == 1) return x * y;

    bitset<4> xl;
    bitset<4> xr;
    bitset<4> yl;
    bitset<4> yr;
  }
  if(n == 1) return x * y;

  bitset<2> xl;
  bitset<2> xr;
  bitset<2> yl;
  bitset<2> yr;

  bitset<1> xl;
  bitset<1> xr;
  bitset<1> yl;
  bitset<1> yr;

  unsigned int xl = x & ((1 << 2) - 1);
  unsigned int xr = x >> 2;
  unsigned int yl = y & ((1 << 2) - 1);
  unsigned int yr = y >> 2;
  std::cout << bin4(xl) << '\n';
  std::cout << bin4(xr) << '\n';
  std::cout << bin4(yl) << '\n';
  std::cout << bin4(yr) << '\n';
  std::cout << n << '\n';

  unsigned int p1 = multiply(xl, yl);
  unsigned int p2 = multiply(xr, yr);
  unsigned int p3 = multiply(xl + xr, yl + yr);

  bit_considerados /= 2;
  return p1 * pow(2, n) + (p3 - p1 - p2) * pow(2, n / 2) + p2;
}

int main() {
  unsigned int x = 0b1111;
  unsigned int y = 0b1010;

  unsigned int result = multiply(x, y);

  return 0;
}
