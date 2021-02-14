#include "aline.h"

// Apply a transformation on a shape with optional scaling
void transformAndScale(shape_t *shape,
		       trans8_t const *transformation,
		       point16_t const *scale) {
  uindex_t end = shape->pointCount;
  point16_t transpoint[end];
  for (uindex_t i = 0; i < end; i++) {
      translatePoint8(&transpoint[i], &shape->canonicalShape[i], transformation);
      if (scale->x) {
	shape->currentShape[i].x =
	  Normalize(Normalize(transpoint[i].x) * scale->x);
      }
      if (scale->y) {
	shape->currentShape[i].y =
	  Normalize(Normalize(transpoint[i].y) * scale->y);
      }
    }
}

// Shape without transformation.
void scale(shape_t *shape, point16_t const *scale) {
  uindex_t end = shape->pointCount;
  for (uindex_t i = 0; i < end; i++) {
    if (scale->x) {
      shape->currentShape[i].x =
	Normalize(shape->canonicalShape[i].x * scale->x);
    }
    if (scale->y) {
      shape->currentShape[i].y =
	Normalize(shape->canonicalShape[i].y * scale->y);
    }
  }
}
