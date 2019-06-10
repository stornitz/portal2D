#include "server/client_manager.h"

ClientManager::~ClientManager() {
    for (const auto& client : clients) {
        delete client;
    }
}

std::queue<WorldEvent>& ClientManager::getSendQueue() {
    return world_events;
}

std::queue<ViewEvent>& ClientManager::getReceiveQueue() {
    return view_events;
}

void ClientManager::addClient(ActiveSocket skt) {
    Interface<WorldEvent, ViewEvent>* client_interface = new Interface<WorldEvent, ViewEvent>(std::move(skt));
    clients.push_back(client_interface);
}

void ClientManager::addSelectPlayer(int client_index, int player_index) {
    checkValidIndex(client_index);
    WorldEvent event;
    event.type = SELECT_PLAYER;
    event.id = player_index;
    clients[client_index]->getSendQueue().push(event);
}

void ClientManager::joinInputQueues() {
    for (const auto& client : clients) {
        std::vector<ViewEvent> events = client->getReceiveQueue().popAll();
        for (const auto& event : events) {
            view_events.push(event);
        }
    }
}

void ClientManager::broadcast() {
    while (!world_events.empty()) {
        WorldEvent event = world_events.front();
        world_events.pop();
        for (const auto& client : clients) {
            client->getSendQueue().push(event);
        }
    }
}

void ClientManager::checkValidIndex(size_t index) {
    if (index >= clients.size()) {
        throw std::runtime_error("Error: Índice de cliente inválido");
    }
}
