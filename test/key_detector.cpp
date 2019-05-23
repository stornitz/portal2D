#include "key_detector.h"

KeyDetector::KeyDetector(int x, int y, std::vector<Sprite*> sprites) :
    x(x), y(y), sprites(sprites) {}

Texture& KeyDetector::getTexture() {
    return sprites[current]->getTexture();
}

int KeyDetector::getX() const {
    return x;
}

int KeyDetector::getY() const {
    return y;
}

int KeyDetector::getWidth() const {
    return sprites[current]->getWidth();
}

int KeyDetector::getHeight() const {
    return sprites[current]->getHeight();
}

void KeyDetector::handle(const KeyboardEvent& event) {
    if (event.pressed) {
        if (event.key == SDLK_w) {
            current = 1;
        } else if (event.key == SDLK_a) {
            current = 2;
        } else if (event.key == SDLK_s) {
            current = 3;
        } else if (event.key == SDLK_d) {
            current = 4;
        } else {
            current = 0;
        }
    } else {
        current = 0;
    }
}
