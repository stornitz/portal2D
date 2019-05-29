#include "client/view/view_object_creator.h"

ViewObjectCreator::ViewObjectCreator(Ratio& ratio, std::vector<DrawableBox2D*>& view_objects,
    const TextureCreator& texture_creator, size_t width, size_t height) :
    meter_to_pixel(ratio), view_objects(view_objects), textures(texture_creator),
    background(width, height, textures["Background"]) {}

void ViewObjectCreator::createPlayer(size_t index, const Position& initial) {
    Size size(entitiesSettings[TYPE_PLAYER][HALF_WIDTH]*2, entitiesSettings[TYPE_PLAYER][HALF_HEIGHT]*2);
    Player* player = new Player(size, initial, meter_to_pixel, textures["Player"]);
    view_objects.at(index) = player;
}

void ViewObjectCreator::createMetalBlock(size_t index, const Position& initial) {
    Size size(entitiesSettings[TYPE_METAL_BLOCK][HALF_WIDTH]*2, entitiesSettings[TYPE_METAL_BLOCK][HALF_HEIGHT]*2);
    Block* block = new MetalBlock(size, initial, meter_to_pixel, textures["Block"]);
    view_objects.at(index) = block;
}

void ViewObjectCreator::createStoneBlock(size_t index, const Position& initial) {
    Size size(entitiesSettings[TYPE_STONE_BLOCK][HALF_WIDTH]*2, entitiesSettings[TYPE_STONE_BLOCK][HALF_HEIGHT]*2);
    Block* block = new MetalBlock(size, initial, meter_to_pixel, textures["Block"]);
    view_objects.at(index) = block;
}

void ViewObjectCreator::createAcid(size_t index, const Position& initial) {
    Size size(entitiesSettings[TYPE_ACID][HALF_WIDTH]*2, entitiesSettings[TYPE_ACID][HALF_HEIGHT]*2);
    Acid* acid = new Acid(size, initial, meter_to_pixel, textures["Miscellaneous"]);
    view_objects.at(index) = acid;
}

void ViewObjectCreator::createButton(size_t index, const Position& initial) {
    Size size(entitiesSettings[TYPE_BUTTON][HALF_WIDTH]*2, entitiesSettings[TYPE_BUTTON][HALF_HEIGHT]*2);
    Button* button = new Button(size, initial, meter_to_pixel, textures["Miscellaneous"]);
    view_objects.at(index) = button;
}

void ViewObjectCreator::createEnergyBall(size_t index, const Position& initial) {
    Size size(entitiesSettings[TYPE_ENERGY_BALL][HALF_WIDTH]*2, entitiesSettings[TYPE_ENERGY_BALL][HALF_HEIGHT]*2);
    EnergyBall* energy_ball = new EnergyBall(size, initial, meter_to_pixel, textures["FX"]);
    view_objects.at(index) = energy_ball;
}

void ViewObjectCreator::createEnergyReceiver(size_t index, const Position& initial, double rotation) {
    Size size(entitiesSettings[TYPE_ENERGY_RECEIVER][HALF_WIDTH]*2, entitiesSettings[TYPE_ENERGY_RECEIVER][HALF_HEIGHT]*2);
    EnergyReceiver* energy_receiver = new EnergyReceiver(size, initial, meter_to_pixel, textures["Block"], rotation);
    view_objects.at(index) = energy_receiver;
}

void ViewObjectCreator::createRock(size_t index, const Position& initial, double rotation) {
    Size size(entitiesSettings[TYPE_ROCK][HALF_WIDTH]*2, entitiesSettings[TYPE_ROCK][HALF_HEIGHT]*2);
    Rock* rock = new Rock(size, initial, meter_to_pixel, textures["Block"], rotation);
    view_objects.at(index) = rock;
}
