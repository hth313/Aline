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
// that describe sine/cosine values in Q1.8 form.
//
// The result is a point in 16-bits resolution, which typically is a
// scaled value (fixed binary decimal point) that will need some
// additional operations depending on how it is actually used.
//
// **********************************************************************

void translatePoint8 (point16_t *result,
		      point8_t const *point, trans16_t const *trans) {
  // As the translation matrix has elements signed in Q1.8 form
  // we special handle the case when it is exactly one.
  // There are two reasons for this.
  // 1. We can avoid doing a multiplication which is going to
  //    return the same value, possibly negated.
  // 2. When we actually need to multiply, we can do it in 8x8 to
  //    16-bit result mode, which the compiler (may) implement
  //    more efficiently.
  // The downsize are some extra tests and a bit of code bloat,
  // but as it is intended to be used with a compiler that can
  // multiply 8x8 faster than 16x16, it is judged to be worth it.
  int16_t x;
  if ((trans->matrix[0][0] & 0xff) == 0) {
    // 1 or -1
    if (trans->matrix[0][0] < 0) {
	x = - point->x;
      } else {
	x = point->x;
      }
  } else {
    x = point->x * (int8_t) trans->matrix[0][0];
  }
  if ((trans->matrix[1][0] & 0xff) == 0) {
    // 1 or -1
    if (trans->matrix[1][0] < 0) {
	result->x = x - point->y;
      } else {
	result->x = x + point->y;
      }
  } else {
    result->x = x + point->y * (int8_t) trans->matrix[1][0];
  }

  int16_t y;
  if ((trans->matrix[0][1] & 0xff) == 0) {
    // 1 or -1
    if (trans->matrix[0][1] < 0) {
	y = - point->x;
      } else {
	y = point->x;
      }
  } else {
    x = point->x * (int8_t) trans->matrix[0][1];
  }
  if ((trans->matrix[1][1] & 0xff) == 0) {
    // 1 or -1
    if (trans->matrix[1][1] < 0) {
	result->y = y - point->y;
      } else {
	result->y = y + point->y;
      }
  } else {
    result->y = y + point->y * (int8_t) trans->matrix[1][1];
  }

#if 0
  result->x = point->x * trans->matrix[0][0] + point->y * trans->matrix[1][0];
  result->y = point->x * trans->matrix[0][1] + point->y * trans->matrix[1][1];
#endif
}
