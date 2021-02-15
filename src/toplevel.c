#include "aline.h"
#include <intrinsics6502.h>

// This variable is set to 0 or 1 by the vblank interrupt to indicate which
// bitmap is currently being show.
__zpage uint8_t activeBitmap;

// Top level loop, the applications
void topLevel(app_t *app) {
  while (true) {
    // The bitmap we are going to fill
    uint8_t bitmapIndex = activeBitmap ^ 1;

    // Send a tick to all shapes to make them update.
    app->tick();

    // Render a frame
    app->render(bitmapIndex);

    // Wait until vblank
    __wait_for_interrupt();
  }
}

// Send ticks to a slice of shapes
void sendTicks (shape_t *shapes[], uindex_t count) {
  for (uindex_t i = 0; i < count; i++) {
    if (shapes[i]->visible) {
      shapes[i]->tickUpdate(shapes[i]);
    }
  }
}

// Render a slice of shapes
void renderShapes (shape_t *shapes[], uindex_t count) {
  for (uindex_t i = 0; i < count; i++) {
    if (shapes[i]->visible) {
//      render(shapes[i]);
    }
  }
}
