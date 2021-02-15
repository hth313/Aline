#ifndef __ALINE_H__
#define __ALINE_H__

#include <stdint.h>
#include <stdbool.h>

// This is the number of fixed point decimal bits used for a scale
// factor. Thus (1 << ScaleFactor) means keep current size.
// #define ScaleFactor 4

// Normalize a result after transformation. This rounds a fixed
// point value with 8 binary fraction digits.
#define Normalize(x)        ((uint8_t) (((x) + 0x40) >> 8))
//#define NormalizeScaling(x) \
//           ((uint8_t) (((x) + (1 << (ScaleFactor - 2))) >> ScaleFactor))

// Fast indexing type used for shape arrays
typedef uint_fast8_t uindex_t;

typedef struct upoint8 {
  uint8_t x, y;
} upoint8_t;

typedef struct point8 {
  int8_t x, y;
} point8_t;

typedef struct upoint16 {
  uint16_t x, y;
} upoint16_t;

typedef struct point16 {
  int16_t x, y;
} point16_t;

typedef struct upoint32 {
  uint32_t x, y;
} upoint32_t;

typedef struct point32 {
  int32_t x, y;
} point32_t;

// A standard transformation matrix.
// The first index is the row and the second the column index.
typedef struct trans8 {
  int8_t    matrix[2][2];
} trans8_t;

typedef struct trans16 {
  int16_t   matrix[2][2];
} trans16_t;

/*
 * A shape is described by a series of points, lines or plots.
 * It is a sequence of very basic drawing commands that defines
 * the visual appearance of a shape.
 * Shapes have a canonical set of points that define its basic
 * look, which can be tranformed in various way.
 * When a shape is transformed, its points are recalculated, but the
 * draw commands stay the same.
 * Such tranformed shape is stored in a cached form which is intended
 * to stay untocuhed until some other tranformation changes it.
 * Drawing commands are stored separate from the point data, as
 * it is not normally changed.
 * By using pointers to arrays, it is possible to swap to an alternative
 * shape shape points definition (possibly also penActions), or the
 * cached transformed points sequence can be quickly swapped between a
 * couple of precalculated ones.
 * The shape is intended to be included in some other structure that
 * defines the state of a specific object, which may contain things
 * such as, angle, rotation, speed and direction, hit points, fuel
 * or other properties. Such properties are not part of the active
 * visual appearance.
 */

enum penAction { movePen, lineTo, plotAt  };

typedef enum penAction *penActions_t;

typedef struct shape {
  uint8_t  const *penActions;       // pen actions used for rendering
  point8_t const *canonicalShape;   // the basic untransformed shape
  point8_t       *currentShape;     // how it looks now, with transformations
  uint8_t         pointCount;       // number of elements in above arrays
  point16_t       position;         // screen position
  void (*tickUpdate)(struct shape*);
                                    // function that will update a shape when a
                                    // tick occurs
  bool            visible;
} shape_t;

// The application type
typedef struct app {
  void (*tick)();
  void (*render)(uint8_t);
} app_t;

/*
 * Exported functions
 */

void transformAndScale(shape_t *shape,
		       trans8_t const *transformation,
		       point16_t const *scale);

void scale(shape_t *shape, point16_t const *scale);

void translatePoint8 (point16_t *result,
		      point8_t const *point, trans8_t const *trans);

void rotateTransformation(uint8_t angle, trans8_t* trans);

void draw (point16_t* from, point16_t* to);

void plot (point16_t* at);

#endif // __ALINE_H__
