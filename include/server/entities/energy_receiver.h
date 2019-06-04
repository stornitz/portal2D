#ifndef ENERGY_RECEIVER_ENTITY_H
#define ENERGY_RECEIVER_ENTITY_H

#include "Box2D/Box2D.h"

#include "common/entities/entity.h"
#include "server/entities/with_subscribable_state.h"
#include "server/entities/handle_contact.h"

class EnergyReceiverEntity : public Entity, public WithSubscribableState, public HandleContact {
public:
	EnergyReceiverEntity(YAML::Node yaml);

	virtual void handleContactWith(Entity * other, b2Contact * contact, bool inContact) override;
};

#endif  // ENERGY_RECEIVER_ENTITY_H
