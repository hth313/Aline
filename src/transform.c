#include "aline.h"

// Apply a transformation on a shape with optional scaling
void transformAndScale(shape_t *shape,
		       trans8_t  const *transformation,
		       point16_t const *scale) {
  uindex_t end = shape->pointCount;
  point8_t transpoint[end];
  for (uindex_t i = 0; i < end; i++) {
      translatePointSine(&transpoint[i], &shape->canonicalShape[i], transformation);
      if (scale->x) {
	shape->currentShape[i].x = NormalizeQ8_8(transpoint[i].x * scale->x);
      }
      if (scale->y) {
	shape->currentShape[i].y = NormalizeQ8_8(transpoint[i].y * scale->y);
      }
    }
}

// Shape without transformation.
void scale(shape_t *shape, point16_t const *scale) {
  uindex_t end = shape->pointCount;
  for (uindex_t i = 0; i < end; i++) {
    if (scale->x) {
      shape->currentShape[i].x =
	NormalizeQ8_8(shape->canonicalShape[i].x * scale->x);
    }
    if (scale->y) {
      shape->currentShape[i].y =
	NormalizeQ8_8(shape->canonicalShape[i].y * scale->y);
    }
  }
}
