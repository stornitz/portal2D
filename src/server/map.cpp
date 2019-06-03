#include "server/map.h"

Map::Map(const char * mapName) {
	YAML::Node file = YAML::LoadFile(mapName);
    this->loadSettings(file);
	this->loadEntities(file);
}

const std::vector<Entity*> & Map::getStaticEntities() const {
	return this->staticEntities;
}

const std::vector<Entity*> & Map::getDynamicEntities() const {
	return this->dynamicEntities;
}

EndZone & Map::getEndZone() {
	return this->endZone;
}

b2Vec2 & Map::getSpawn() {
	return this->spawn;
}

int Map::getMinPlayers() {
	return this->minPlayers;
}

void Map::loadSettings(YAML::Node yaml) {
	this->minPlayers = yaml["min-players"].as<int>();

	YAML::Node spawn = yaml["spawn"];
	this->spawn.x = spawn["x"].as<float>();
	this->spawn.y = spawn["y"].as<float>();
}

void Map::loadEntities(YAML::Node yaml) {
	YAML::Node entities = yaml["entities"];

	std::map<std::string, WithSubscribableState*> subscribables;
	std::vector<DoorEntity*> doors;

	for(uint i = 0; i < entities.size(); i++) {
		Entity * entity = this->createEntity(entities[i]);

		if(entity->getType() < DYNAMIC_ENTITY_START) {
			this->staticEntities.push_back(entity);
		} else {
			this->dynamicEntities.push_back(entity);
		}

		if(entity->getType() == TYPE_BUTTON ||
			entity->getType() == TYPE_ENERGY_RECEIVER) {
			std::string entityName = entities[i]["name"].as<std::string>();

			if(entity->getType() == TYPE_BUTTON) {
				subscribables[entityName] = entity->as<ButtonEntity>();
			} else {
				subscribables[entityName] = entity->as<EnergyReceiverEntity>();
			}
		}

		if(entity->getType() == TYPE_GATE) {
			doors.push_back(entity->as<DoorEntity>());
		}
	}

	for(DoorEntity * door : doors) {
		door->attach(subscribables);
	}
}

Entity * Map::createEntity(YAML::Node yaml) {
	std::string type_string = yaml["type"].as<std::string>();

	Entity * entity = nullptr;
    EntityType type = getEntityType(type_string);
	switch(type) {
		case TYPE_STONE_BLOCK:
		case TYPE_METAL_BLOCK:
		case TYPE_METAL_DIAG_BLOCK:
		case TYPE_ACID:
		case TYPE_ENERGY_BAR:
			entity = new Entity(type, yaml);
			break;
		case TYPE_GATE:
			entity = new DoorEntity(yaml);
			break;
		case TYPE_ENERGY_EMITTER:
			entity = new EnergyEmittorEntity(yaml);
			break;
		case TYPE_ENERGY_RECEIVER:
			entity = new EnergyReceiverEntity(yaml);
			break;
		case TYPE_BUTTON:
			entity = new ButtonEntity(yaml);
			break;
		case TYPE_END_BARRIER:
			entity = new EndBarrierEntity(yaml, this->endZone);
			break;
		case TYPE_ROCK:
			entity = new RockEntity(yaml);
			break;
		default:
			throw std::runtime_error("Unsupported entity type");
	}

	return entity;
}

Map::~Map() {
	for(uint i = 0; i < this->staticEntities.size(); i++) {
		delete this->staticEntities[i];
	}

	for(uint i = 0; i < this->dynamicEntities.size(); i++) {
		delete this->dynamicEntities[i];
	}
}

EntityType Map::getEntityType(std::string str) {
    if (str == "TYPE_STONE_BLOCK") {
        return TYPE_STONE_BLOCK;
    }
	if (str == "TYPE_METAL_BLOCK") {
        return TYPE_METAL_BLOCK;
    }
	if (str == "TYPE_METAL_DIAG_BLOCK") {
        return TYPE_METAL_DIAG_BLOCK;
    }
	if (str == "TYPE_ACID") {
        return TYPE_ACID;
    }
	if (str == "TYPE_GATE") {
        return TYPE_GATE;
    }
	if (str == "TYPE_ENERGY_BAR") {
        return TYPE_ENERGY_BAR;
    }
	if (str == "TYPE_ENERGY_EMITTER") {
        return TYPE_ENERGY_EMITTER;
    }
	if (str == "TYPE_ENERGY_RECEIVER") {
        return TYPE_ENERGY_RECEIVER;
    }
	if (str == "TYPE_BUTTON") {
        return TYPE_BUTTON;
    }
	if (str == "TYPE_PORTAL") {
        return TYPE_PORTAL;
    }
	if (str == "TYPE_END_BARRIER") {
        return TYPE_END_BARRIER;
    }
	if (str == "TYPE_ROCK") {
        return TYPE_ROCK;
    }
	if (str == "TYPE_PLAYER") {
        return TYPE_PLAYER;
    }
	if (str == "TYPE_ENERGY_BALL") {
        return TYPE_PLAYER;
    }
    throw std::runtime_error("Error: string mal formado en el archivo del mapa");
}
