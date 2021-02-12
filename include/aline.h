#ifndef __ALINE_H__
#define __ALINE_H__

#include <stdint.h>

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

#endif // __ALINE_H__
