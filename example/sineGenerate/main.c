#include "stdio.h"
#include "math.h"

union xx {
  int ii;
  float ff;
};

int main () {
  for (unsigned i = 0; i <= 255; i++) {
    double result = sin((double) i * 90.0 / 64.0 * (M_PI / 180));
    union xx conv;
    conv.ff = result;
    int sign = conv.ii < 0;
    conv.ii &= 0x7fffffff;
    int frac = (conv.ii & 0x7fffff) | 0x800000;
    int exp = (conv.ii >> 23) - 127;

    // align with exponent
    while (exp) {
      frac >>= 1;
      exp++;
    }

    // round
    if (   (frac & 0xc000) == 0x4000 && (frac & 0x3000) != 0
	|| (frac & 0xc000) == 0xc000) {
      frac += 0x8000;
      if (frac > 0xffffff) {
	frac >>= 1;
      }
    }

    frac >>= 16;

    // Bias it so that "1" becomes 7f
    frac--;

    if (sign) {
      frac = (-frac) & 0xff;
    }

    if (conv.ii == 0) {
      frac = 0;
      exp = 0;
    }
    printf("0x%02x,\n", frac);

  }
}
