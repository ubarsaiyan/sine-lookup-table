#include <stdio.h>
#include "sine_table.h"

#define f 100 // frequency not expected to change at runtime as it is the property of the source

unsigned long angle;
int amp;

int mpy(int x, int y) {
  return x*y/32768;
}

long mpy_32(long x, int y) {
  long ans = 0;
  int cnt = 0;
  // printf("%lld %d\t", x, y);
  while (y) {
    long t;
    if (y%2 == 1) {
      t = x << cnt;
      ans += t;
    }
    y /= 2;
    cnt++;
  }
  // printf("%lld\t", ans );
  return ans;
}

int sine(long theta) {
  // printf("%lld\t", theta );
  int t = (int) (theta >> 23);
  // printf(" *%d* ", t);
  int sign = 1;
  if (t>=512)
   t = t%512;
  if (t>=256) {
    t = t%256;
    sign = -1;
  }
  if (t>=128 && t<256)
    t = 255 - t;
  return sign*sine_128[t];
}

int Hundredusinterrupt() {
  //for (int t = 0; f*t <= 10000; t++) { // t is time in 100us
  //printf("%d\n", mpy(amp, sine(mpy_32(2147483648, 2 * f * t) / 10000 + angle))); // PI scaled to 2^32 where 2^32 = 360
  //}
  return mpy(amp, sine(mpy_32(2147483648, 2 * f * t) / 10000 + angle));
}

int main() {
  printf("Enter Amplitude between 0 and 32767 where Amplitude of 0 = 0 and Amplitude of 1 = 32767: ");
  scanf("%d", &amp); //eg. 16384
  printf("Enter phase angle between 0 and 2^32 where 0 = 0 deg and 2^32 = 360 deg: ");
  scanf("%ld", &angle); //eg. 2147483648
  // Hundredusinterrupt();
  return 0;
}
