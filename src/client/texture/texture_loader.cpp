#include "client/texture/texture_loader.h"

TextureLoader::TextureLoader(const TextureCreator& textureCreator) {
    texture_map.emplace("Background", textureCreator("../data/sprites/background.png"));
    texture_map.emplace("Player", textureCreator("../data/sprites/character.png"));
    texture_map.emplace("Block", textureCreator("../data/sprites/blocks.png"));
}

const Texture& TextureLoader::operator[](const std::string& key) const {
    return texture_map.at(key);
}
