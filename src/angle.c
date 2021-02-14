#include "aline.h"

// Angles are based on that a full circle is 144, so the smallest
// unit is 2.5 degrees.
#define QuarterCircle 64

// Sine table
const uint8_t sineTable[QuarterCircle] = {
  0x00, 0x02, 0x05, 0x08, 0x0b, 0x0e, 0x12, 0x15,
  0x18, 0x1b, 0x1e, 0x21, 0x24, 0x27, 0x2a, 0x2d,
  0x30, 0x33, 0x35, 0x38, 0x3b, 0x3e, 0x41, 0x43,
  0x46, 0x48, 0x4b, 0x4d, 0x50, 0x52, 0x55, 0x57,
  0x59, 0x5b, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x67,
  0x69, 0x6b, 0x6d, 0x6e, 0x70, 0x71, 0x72, 0x74,
  0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c,
  0x7c, 0x7d, 0x7d, 0x7e, 0x7e, 0x7e, 0x7f, 0x7f
};

void rotateTransformation(uint8_t angle, trans8_t* trans) {
  int8_t sinAngle, cosAngle;
  if (angle < QuarterCircle) {
    sinAngle =   sineTable[angle];
    cosAngle =   sineTable[QuarterCircle - angle];
  } else if (angle < 2 * QuarterCircle) {
    sinAngle =   sineTable[2 * QuarterCircle - angle];
    cosAngle = - sineTable[angle - QuarterCircle];
  } else if (angle < 3 * QuarterCircle) {
    sinAngle = - sineTable[angle - 2 * QuarterCircle];
    cosAngle = - sineTable[3 * QuarterCircle - angle];
  } else {
    sinAngle = - sineTable[4 * QuarterCircle - angle];
    cosAngle =   sineTable[angle - 3 * QuarterCircle];
  }
  trans->matrix[0][0] =  cosAngle;
  trans->matrix[1][1] =  cosAngle;
  trans->matrix[0][1] =  sinAngle;
  trans->matrix[1][0] = -sinAngle;
}
