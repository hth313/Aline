#include "aline.h"

typedef struct lander {
  shape_t   shape;            // its shape
  point16_t scale;            // scale factors, 8 integer and 8 fraction bits
  point16_t speed;            // speed, 8 integer and 8 fraction bits
                              // number of bits to move each tick
  point16_t delta;            // counts how far we moved, to be moved
                              //   gradually to screen position
  uint16_t  fuel;             // fuel left
  uint8_t   angle;            // current angle, 144 degree based
  int8_t    rotationDelta;    // 144 degree based rotation angle
  uint8_t   rotationTick;     // how often to update rotation
  uint8_t   rotationCounter;  // count down to next rotation
  trans8_t  transformation;   // transformation matrix
} lander_t;

/* Local functions */
static void tickUpdateLander (shape_t * shape);

#define LanderPointCount 5

// A square of 100 pixels with axis in its center
const point8_t squarePoints[LanderPointCount] = {
  { -50, -50 },
  { 50, -50},
  { 50, 50 },
  { -50, 50 },
  { -50, - 50 }
};

const uint8_t squareActions[LanderPointCount] =
  { movePen, lineTo, lineTo, lineTo, lineTo };

point8_t currentPoints[LanderPointCount];

lander_t theLander = {
  { squareActions, squarePoints, currentPoints, LanderPointCount,
    { 0, 0 }, // initial position
    tickUpdateLander },
  { 0, 0 }, // scale factor, no scaling now
  { 0x05, 0x01 },  // initial speed
  { 0, 0 },        // count delta
  1000,            // fuel
  0,               // initial angle
  1,               // rotation
  2,               // rotation tick
  2,               // rotation counter
  { 0, }           // transformation, to be filled in
};

static void tickUpdateLander (shape_t * shape) {
  lander_t *lander = (lander_t*) shape;

  if (lander->rotationCounter) {
    // it is spinning!
    if (--lander->rotationCounter == 0) {
      // time to update its rotation
      uint8_t angle = addAngleDelta(lander->angle, lander->rotationDelta);
      lander->angle = angle;
      rotateTransformation(angle, &lander->transformation);
      transformAndScale(shape, &lander->transformation, &lander->scale);
    }
  }

  // Move by some fractional value
  lander->delta.x += lander->speed.x;
  lander->delta.y += lander->speed.y;

  // Update screen location if fractional add has contribution
  if (lander->delta.x >= 0x100) {
    lander->shape.position.x += lander->delta.x >> 8;
    lander->delta.x &= 0xff;
  } else if (lander->delta.x < -0x100) {
    lander->shape.position.x += (lander->delta.x >> 8) + 1;
    lander->delta.x |= 0xff00;
  }

  if (lander->delta.y >= 0x100) {
    lander->shape.position.y += lander->delta.y >> 8;
    lander->delta.y &= 0xff;
  } else if (lander->delta.y < -0x100) {
    lander->shape.position.y += (lander->delta.y >> 8) + 1;
    lander->delta.y |= 0xff00;
  }
}
