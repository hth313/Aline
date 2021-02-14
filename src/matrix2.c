#include "aline.h"

// **********************************************************************
//
// translate_point16 - multiply 2x1 by 2x2 matrix
//
// This function translates a point using a transformation matrix.
// The typical use case is rotation, but it can also be used for
// shear.
//
// Inputs are a point in 16-bits resolution and a transformation matrix
// also in 16-bits resolution.
//
// The result is a point in 32-bits resolution, which typically is a
// scaled value (fixed binary decimal point) that will need some
// additional operations.
//
// **********************************************************************

void translate_point16 (point32_t *result,
                        point16_t const *point,
                        trans16_t const *trans) {
  result->x = (long) point->x * trans->matrix[0][0] +
              (long) point->y * trans->matrix[1][0];
  result->y = (long) point->x * trans->matrix[0][1] +
              (long) point->y * trans->matrix[1][1];
}
