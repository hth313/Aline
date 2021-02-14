#include "aline.h"

// Angles are based on that a full circle is 144, so the smallest
// unit is 2.5 degrees.
#define FullCircle    144
#define QuarterCircle (FullCircle / 4)

// Sine table
uint8_t sine144[QuarterCircle] = {
  0x00,
};

// Adjust an angle. This function assume that the angle you
// adjust with is does not cause an overflow. As we have
// 144 as maximum, a positive overflow happens when
// 256-144 -> 112, 112 x 2.5 = 280 degrees, which is a rather
// large delta.
uint8_t addAngleDelta(uint8_t angle, int8_t delta) {
  if (delta >= 0) {
    angle += delta;
    if (angle >= FullCircle) {
      angle -= FullCircle;
    }
  } else {
    angle += delta;
    if ((int8_t)angle < 0) {
      angle += FullCircle;
    }
  }
  return angle;
}

void rotateTransformation(uint8_t angle, trans8_t* trans) {
  int8_t sinAngle, cosAngle;
  if (angle < QuarterCircle) {
    sinAngle =   sine144[angle];
    cosAngle =   sine144[QuarterCircle - angle];
  } else if (angle < 2 * QuarterCircle) {
    sinAngle =   sine144[2 * QuarterCircle - angle];
    cosAngle = - sine144[angle - QuarterCircle];
  } else if (angle < 3 * QuarterCircle) {
    sinAngle = - sine144[angle - 2 * QuarterCircle];
    cosAngle = - sine144[3 * QuarterCircle - angle];
  } else {
    sinAngle = - sine144[4 * QuarterCircle - angle];
    cosAngle =   sine144[angle - 3 * QuarterCircle];
  }
  trans->matrix[0][0] =  cosAngle;
  trans->matrix[1][1] =  cosAngle;
  trans->matrix[0][1] =  sinAngle;
  trans->matrix[1][0] = -sinAngle;
}
