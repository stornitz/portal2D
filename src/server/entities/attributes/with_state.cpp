#include "server/entities/attributes/with_state.h"

WithState::WithState(const State state, GameEventCreator & gameEventCreator) : state(state), gameEventCreator(gameEventCreator) {}

const State& WithState::getState() const {
	return state;
}

void WithState::setState(const State& newState) {
	bool hasChanged = (state != newState);
	state = newState;

	if(hasChanged) {
		gameEventCreator.addStateUpdate(dynamic_cast<Entity*>(this));
	}
}
