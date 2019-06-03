#include "client/objects/end_barrier.h"

EndBarrier::EndBarrier(const Size& size, const Position& initial,
                       const WorldViewSettings& settings, const Texture& texture, double rotation) :
    AnimatedDrawableBox2D(size, initial, settings, texture, rotation) {
    for (int i = 0; i < 4; ++i) {
        animation.addClip(1 + 252*i, 4597, 251, 251);
    }
}
