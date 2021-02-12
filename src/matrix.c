#include "aline.h"

// **********************************************************************
//
// translate_point8 - multiply 2x1 by 2x2 matrix
//
// This function translates a point using a transformation matrix.
// The typical use case is rotation, but it can also be used for
// shear.
//
// Inputs are a point in 8-bits resolution and a transformation matrix
// also in 8-bits resolution.
//
// The result is a point in 16-bits resolution, which typically is a
// scaled value (fixed binary decimal point) that will need some
// additional operations.
//
// **********************************************************************

void translate_point8 (point16_t* result,
                       point8_t*  point,
                       int8_t    trans[2][2]) {
  result->x = point->x * trans[0][0] + point->y * trans[1][0];
  result->y = point->x * trans[0][1] + point->y * trans[1][1];
}
