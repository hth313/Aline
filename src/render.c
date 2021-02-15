#include "aline.h"

void render (shape_t const *shape) {
  // Shape transformed and scaled into 'transpoint', perform pen actions.
  const uint8_t *penActions = shape->penActions;
  uindex_t pointCount = shape->pointCount;
  point16_t activePoint[pointCount];
  for (uindex_t i = 0; i < pointCount; i++) {
    activePoint[i].x = shape->position.x + shape->currentShape[i].x;
    activePoint[i].y = shape->position.y + shape->currentShape[i].y;
    switch (penActions[i]) {
    case movePen:
      break;
    case lineTo:
      draw(&activePoint[i - 1], &activePoint[i]);
      break;
    case plotAt:
      plot(&activePoint[i]);
      break;
    }
  }
}
