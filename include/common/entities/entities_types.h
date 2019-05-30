#ifndef ENTITIES_TYPES_H
#define ENTITIES_TYPES_H

enum EntityType {
	// Static
	// - Ground
	TYPE_STONE_BLOCK = 0,
	TYPE_METAL_BLOCK,
	TYPE_METAL_DIAG_BLOCK,
	// - Not Ground
	TYPE_ACID,
	TYPE_GATE,
	TYPE_ENERGY_BAR,
	TYPE_ENERGY_EMITTER,
	TYPE_ENERGY_RECEIVER,
	TYPE_BUTTON,
	TYPE_PORTAL,
	TYPE_END_BARRIER,

	// Dynamic
	TYPE_ROCK,
	TYPE_PLAYER,

	// Kinematic
	TYPE_ENERGY_BALL,

	ENTITY_TYPES_LENGTH,
};

constexpr EntityType DYNAMIC_ENTITY_START = TYPE_ROCK;

#endif