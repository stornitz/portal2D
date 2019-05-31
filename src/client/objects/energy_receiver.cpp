#include "client/objects/energy_receiver.h"

EnergyReceiver::EnergyReceiver(const Size& size,
        const Position& initial, const Ratio& ratio,
        const Texture& texture, double rotation) :
    Block(size, initial, ratio, texture) {
    sprite.addClip(1, 1028, 193, 193, rotation);
}
