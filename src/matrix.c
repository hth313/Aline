#include "aline.h"

// **********************************************************************
//
// translatePoint8 - multiply 2x1 by 2x2 matrix
//
// This function translates a point using a transformation matrix.
// The typical use case is rotation, but it can also be used for
// shear.
//
// Inputs are a point in 8-bits resolution and a transformation matrix
// that describe sine/cosine values in Q0.7 form.
//
// The result is a point in 16-bits resolution, which typically is a
// scaled value (fixed binary decimal point) that will need some
// additional operations depending on how it is actually used.
//
// **********************************************************************

void translatePoint8 (point16_t *result,
		      point8_t const *point, trans8_t const *trans) {
  result->x = point->x * trans->matrix[0][0] + point->y * trans->matrix[1][0];
  result->y = point->x * trans->matrix[0][1] + point->y * trans->matrix[1][1];
}
