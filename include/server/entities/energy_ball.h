#ifndef ENERGY_BALL_ENTITY_H
#define ENERGY_BALL_ENTITY_H

#include <chrono>

#include "server/entities/entity.h"
#include "server/entities/attributes/teleportable_entity.h"
#include "server/events/game_event_creator.h"
#include "server/objects/server_settings.h"
#include "server/objects/server_settings.h"
extern ServerSettings SETTINGS;

class EnergyBallEntity;

#include "server/entities/energy_emitter.h"

class EnergyBallEntity :  public TeleportableEntity {
public:
	EnergyBallEntity(const float intialX, const float intialY, const float angle, 
		GameEventCreator& gameEventCreator, EnergyEmitterEntity & owner);

	virtual void handleContactWith(Entity * other, b2Contact * contact, bool inContact) override;

	std::chrono::system_clock::time_point * getDeathTP();

	virtual ~EnergyBallEntity() override;

private: 
	EnergyEmitterEntity & owner;
	bool justEmitted = true;
	std::chrono::system_clock::time_point deathTP =
		std::chrono::system_clock::now()
		+ std::chrono::duration<int>(SETTINGS.ENERGY_BALL_LIFE_LENGTH);

	void evaluateCollision(b2Contact * contact);
};

#endif  // ENERGY_BALL_ENTITY_H
