#include "client/view/world_view.h"

WorldView::WorldView(BlockingQueue<ViewEvent>& queue) :
    event_manager(queue),
    screen(CLIENT_SETTINGS.INITIAL_SCREEN_WIDTH, CLIENT_SETTINGS.INITIAL_SCREEN_HEIGHT),
    camera_manager(screen),
    settings(screen.getWidth(), screen.getHeight(), screen.getTextureCreator()),
    background(settings.getScreenWidth(), settings.getScreenHeight(), settings.getTextureLoader()["Background"]),
    object_creator(view_objects, settings) {
    event_manager.addHandler((KeyboardHandler*) &sound_manager);
    event_manager.addHandler((MouseHandler*) &sound_manager);
    event_manager.addHandler((WindowEventHandler*) &screen);
    event_manager.addHandler((KeyboardHandler*) &screen);
}

WorldView::~WorldView() {
    for (const auto& object : view_objects) {
        delete object.second;
    }
    if (main_player) {
        delete main_player;
    }
}

void WorldView::pollEvents() {
    event_manager.pollEvents();
}

bool WorldView::quit() const {
    return event_manager.quit();
}

const ViewObjectCreator& WorldView::getObjectCreator() const {
    return object_creator;
}

int WorldView::getPlayerIndex() const {
    if (!main_player) {
        return -1;
    }
    return main_player->getIndex();
}

void WorldView::createEntity(size_t index, EntityType type,
                             const Position& position, const State& state) {
    switch (type) {
        case TYPE_STONE_BLOCK:
            object_creator.createStoneBlock(index, position);
            break;
        case TYPE_METAL_BLOCK:
            object_creator.createMetalBlock(index, position);
            break;
        case TYPE_METAL_DIAG_BLOCK:
            object_creator.createDiagonalMetalBlock(index, position);
            break;
        case TYPE_ACID:
            object_creator.createAcid(index, position);
            break;
        case TYPE_GATE:
            object_creator.createGate(index, position);
            break;
        case TYPE_ENERGY_BAR:
            object_creator.createEnergyBar(index, position);
            break;
        case TYPE_ENERGY_EMITTER:
            object_creator.createEnergyEmitter(index, position);
            break;
        case TYPE_ENERGY_RECEIVER:
            object_creator.createEnergyReceiver(index, position);
            break;
        case TYPE_BUTTON:
            object_creator.createButton(index, position);
            break;
        case TYPE_PORTAL:
            object_creator.createPortal(index, position, state);
            break;
        case TYPE_END_BARRIER:
            object_creator.createEndBarrier(index, position);
            break;
        case TYPE_ROCK:
            object_creator.createRock(index, position);
            break;
        case TYPE_PLAYER:
            object_creator.createPlayer(index, position);
            camera_manager.add(index, view_objects[index]);
            break;
        case TYPE_ENERGY_BALL:
            object_creator.createEnergyBall(index, position);
            break;
        default:
            throw std::runtime_error("Error: EntityType inválido");
    }
}

void WorldView::destroyEntity(size_t index) {
    if (index == main_player->getIndex()) {
        event_manager.removeHandler((KeyboardHandler*) main_player);
        event_manager.removeHandler((MouseHandler*) main_player);
    }

    bool destroyNow = view_objects.at(index)->setDestroy();
    if (destroyNow) {
        deleteEntity(index);
    }
}

void WorldView::updatePosition(size_t index, const Position& position) {
    view_objects.at(index)->updatePosition(position);
}

void WorldView::updateState(size_t index, const State& state) {
    view_objects.at(index)->updateState(state);
}

void WorldView::selectPlayer(size_t index) {
    Player* player = static_cast<Player*>(view_objects.at(index));
    camera_manager.select(index);
    main_player = new MainPlayer(index, *player, *screen.getCamera(), event_manager.getQueue());
    event_manager.addHandler((KeyboardHandler*) main_player);
    event_manager.addHandler((MouseHandler*) main_player);
}

void WorldView::update() {
    screen.setRenderDrawColor("white");
    screen.clear();
    screen.render(background);
    renderObjects();
    if (victory) {
        renderTexture("Victory");
    } else if (defeat) {
        renderTexture("Defeat");
    }
    screen.update();
}

void WorldView::setVictory() {
    victory = true;
}

void WorldView::setDefeat() {
    defeat = true;
}

void WorldView::renderObjects() {
    screen.centerCamera();
    for (const auto& object : view_objects) {
        screen.render(*object.second);
        if (object.second->isFinished()) {
            deleteEntity(object.first);
        }
    }
}

void WorldView::renderTexture(const std::string& name) {
    const Texture& texture = settings.getTextureLoader()[name];
    const Camera* camera = screen.getCamera();
    if (!camera) {
        screen.render(texture, 0, 0, 0.5);
        return;
    }
    int x = camera->position.x + camera->position.w/2;
    int y = camera->position.y + camera->position.h/2;
    screen.render(texture, x, y, 0.5);
}

void WorldView::deleteEntity(size_t index) {
    camera_manager.removeAndReplace(index);
    delete view_objects.at(index);
    view_objects.erase(index);
}
