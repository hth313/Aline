#include "aline.h"

#define Normalize(x)        ((uint8_t) (((uint16_t)((x) + 0x60)) >> 7))

// **********************************************************************
//
// translatePointSine - multiply 2x1 by 2x2 matrix sin/cos values
//
// This function translates a point using a transformation matrix.
// The typical use case is rotation, but it can (depending on input
// also be used for shear).
//
// Inputs are a point in 8-bits resolution and a transformation matrix
// that describes sine/cosine values in Q0.7 form.
//
// The value "1" is not exactly represented in the transformation matrix.
// Instead it is the closest number below 0.1111111 (binary).
// We round up during normalization to compensate for this.
//
// **********************************************************************

void translatePointSine (point8_t *result,
                         point8_t const *point, trans8_t const *trans) {
  result->x = Normalize(point->x * trans->matrix[0][0] + point->y * trans->matrix[1][0]);
  result->y = Normalize(point->x * trans->matrix[0][1] + point->y * trans->matrix[1][1]);
}
