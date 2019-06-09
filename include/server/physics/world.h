#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Box2D/Box2D.h"

#include "server/entities/entity.h"
#include "common/objects/click_direction.h"
#include "server/map.h"
#include "server/entities/player.h"
#include "server/entities/utils/body_factory.h"
#include "server/physics/contact_listener.h"
#include "server/events/event_creator.h"

/*
	y
	^
	|
	|
	*------ > x
*/

#define PORTAL_REACH 30.0f

class World {
public:
	explicit World(Map& map, EventCreator& eventCreator);

    void createPlayer(PlayerEntity* player);
    void createPortal(PlayerEntity& player, ClickDirection& direction);

    void updatePhysics();
    void updateDynamics();

	const std::vector<Entity*>& getDynamicEntities() const;

	int getPlayersCount();

	b2World & getb2World();

private:
	b2World world;
	BodyFactory bodyFactory;
	Map& map;
	EventCreator& eventCreator;

    bool portal_color = false;

	std::vector<PlayerEntity*> players;

	// TODO maybe update with methods instead of b2World.getEntities()
	std::vector<Entity*> dynamicEntities;

	ContactListener contactListener;
};

#endif  // WORLD_H
