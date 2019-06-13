#include "common/events/world_event.h"

WorldEvent::WorldEvent(WorldEventType type) : type(type) {}

WorldEvent::WorldEvent(int id, EntityType type, const Position& position) :
    type(ENTITY_CREATION), id(id), entity_type(type), position(position) {}

WorldEvent::WorldEvent(int id) :
    type(ENTITY_DESTRUCTION), id(id) {}

WorldEvent::WorldEvent(int id, const Position& position) :
    type(POSITION_UPDATE), id(id), position(position) {}

WorldEvent::WorldEvent(int id, const State& state) :
    type(STATE_UPDATE), id(id), state(state) {}

WorldEvent::WorldEvent(const Size & size) :
    type(WORLD_SIZE), position(size.x, size.y, 0.0f) {}
