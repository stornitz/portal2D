#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>

enum EntityType {
	// Static
	// - Ground
	TYPE_STONE_BLOCK = 0,
	TYPE_METAL_BLOCK,
	TYPE_METAL_DIAG_BLOCK,
	// - Not Ground
	TYPE_ACID,
	TYPE_DOOR,
	TYPE_ENERGY_BAR,
	TYPE_ENERGY_EMITTOR,
	TYPE_ENERGY_RECEIVER,
	TYPE_ENDCAKE,
	TYPE_BUTTON,
	TYPE_PORTAL,

	// Dynamic
	TYPE_ROCK,
	TYPE_PLAYER,

	// Kinematic
	TYPE_ENERGY_BALL,

	ENTITY_TYPES_LENGTH,
};

enum EntitySetting {
    X_OFFSET = 0,
    Y_OFFSET = 1,
    HALF_WIDTH = 2,
    HALF_HEIGHT = 3,
};

const float entitiesSettings[ENTITY_TYPES_LENGTH][4] = {
	// {x_offset, y_offset, half-width, half-height}

	{0.0f, 0.0f, 0.5f, 0.5f},      // TYPE_STONE_BLOCK
	{0.0f, 0.0f, 0.5f, 0.5f},      // TYPE_METAL_BLOCK
	{0.0f, 0.0f, 0.5f, 0.5f},      // TYPE_METAL_DIAG_BLOCK
	{0.0f, -0.25f, 0.5f, 0.25f},   // TYPE_ACID
	{0.0f, 0.0f, 0.5f, 1.0f},      // TYPE_DOOR
	{0.0f, 0.5f, 0.5f, 0.05f},     // TYPE_ENERGY_BAR
	{0.0f, 0.0f, 0.5f, 0.5f},      // TYPE_ENERGY_EMITTOR
	{0.0f, 0.0f, 0.5f, 0.5f},      // TYPE_ENERGY_RECEIVER
	{0.0f, 0.0f, 0.5f, 0.5f},      // TYPE_ENDCAKE
	{0.0f, -0.25f, 0.5f, 0.25f},   // TYPE_BUTTON
	{-0.5f, 0.0f, 0.05f, 0.5f},    // TYPE_PORTAL
	{0.0f, 0.0f, 0.25f, 0.25f},    // TYPE_ROCK
	{0.0f, -0.1f, 0.25f, 0.4f},    // TYPE_PLAYER
	{0.0f, 0.0f, 0.25f, 0.25f},    // TYPE_ENERGY_BALL
};

constexpr EntityType DYNAMIC_ENTITY_START = TYPE_ROCK;

class Entity {
public:
	Entity(EntityType type, float32 x, float32 y, float32 angle = 0.0f);

	float32 getX() const;
	float32 getY() const;
    void setX(float32 x);
    void setY(float32 y);

	float getAngle() const;
    void setAngle(float angle);

	EntityType getType() const;
    void beginContactWith(Entity *, b2Contact *);
    void endContactWith(Entity *, b2Contact *);

private:
	EntityType type;
	float32 x;
	float32 y;
	float32 angle;
};

#endif  // ENTITY_H
