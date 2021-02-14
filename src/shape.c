#if 0
#include "aline.h"

/*
 * A shape describes a series of points, lines or plots.
 * It is a sequence of very basic drawing commands that defines
 * the basic visual appearance of a shape.
 * When a shape is transformed, its points are recalculated, but the
 * draw commands stay the same.
 * To separate drawing from the data, two types are used.
 */

enum penAction { movePen, lineTo, plotAt  };

typedef struct shape {
  uint8_t *penActions;   // pen actions
  point8_t *points;      // coordinates
  uint8_t pointCount;    //
} shape_t;

// A square of 100 pixels with axis in its center
point8_t squarePoints[] = { { -50, -50 },
                             { 50, -50},
                             { 50, 50 },
                             { -50, 50 },
                             { -50, - 50 } };
uint8_t squareActions[] = { movePen, lineTo, lineTo, lineTo, lineTo };
shape_t square = { squareActions, squarePoints, 5 };

typedef struct shapeInstance {
  point16_t position;         // the position of the object
  shape_t  *shape;            // basic shape
  color_t   color;            // base color to draw it in
  trans_t  *transformation;   // active transformation matrix
  uint8_t   scaleX;           // scale factor, fixed point value scaled by
                              // ScaleFactor, 0 means the same as
                              // (1 << ScaleFactor), i.e. keep current size.
  uint8_t   scaleY;
} shape_instance_t;
#endif
