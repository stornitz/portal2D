#include <iostream>
#include <chrono>

#include "client/client.h"
#include "server/server_interface.h"
#include "common/clock_loop.h"
#include "common/view_event.h"

int main() {
    Client client;
	ServerInterface server;

	// create drawable world with statics objects
	// auto staticEntities = server.getStaticEntities();
	// auto initialDynamicEntities = server.getDynamicEntities();
	ClockLoop<60> clock;

    client.view.createPlayer(Position(1, 5));

	while (!client.quit()) {
        client.pollEvents();
        while (!client.queue.empty()) {
            ViewEvent event = client.queue.pop();
            server.movePlayer(event.direction, event.pressed);
        }
		server.updatePhysics();

		// update drawable world
		// auto dynamicEntities = server.getDynamicEntities();
        // for (auto& entity : dynamicEntities) {
        //     if (entity.getType() == TYPE_PLAYER) {
        //         Position position(entity.getX(), entity.getY());
        //         client.view.updatePosition(player_index, position);
        //     }
        // }
        client.view.update();

		// wait t1
		clock.waitNextLoop();
	}

	return 0;
}
