#include "aline.h"

/*
 * A shape describes a series of points, lines or plots.
 * It is a sequence of very basic drawing commands that defines
 * the basic visual appearance of a shape.
 * When a shape is transformed, its points are recalculated, but the
 * draw commands stay the same.
 * To separate drawing from the data, two types are used.
 */

enum penAction { movePen, lineTo, plotAt, endPen } penAction_t;

typedef enum penAction *penActions_t;

typedef struct shape {
  uint8_t *draw;
  point8_t *where;
} shape_t;

// A square of 100 pixels with axis in its center
point8_t squarePoints[] = { { -50, -50 },
                             { 50, -50},
                             { 50, 50 },
                             { -50, 50 },
                             { -50, - 50 } };
uint8_t squareActions[] = { movePen, lineTo, lineTo, lineTo, lineTo, endPen };
shape_t square = { squareActions, squarePoints };
