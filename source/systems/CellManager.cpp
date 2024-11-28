/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** CellManager.cpp
*/

#include "systems/CellManager.hpp"

#include "Constants.hpp"

namespace hiop::system {
void CellManager::init(void) {
    subscribeToEvent<gengine::interface::event::NewRemoteLocal>(&CellManager::spawnPlayer);
    subscribeToEvent<geg::event::GameLoop>(&CellManager::updateSizes);
    subscribeToEvent<geg::event::GameLoop>(&CellManager::spawnFoodCell);
    subscribeToEvent<event::CellCollision>(&CellManager::handleCollision);
    subscribeToEvent<gengine::interface::event::SharedEvent<event::UserCmd>>(&CellManager::movePlayer);
    subscribeToEvent<gengine::interface::event::SharedEvent<event::UserCmd>>(&CellManager::setPseudo);
    subscribeToEvent<geg::event::GameLoop>(&CellManager::onGameLoop);
}

static gengine::component::driver::output::Clr rdmColor(void) {
    gengine::component::driver::output::Clr color;
    color.a = 255;
    color.r = std::rand() % 255;
    color.g = std::rand() % 255;
    color.b = std::rand() % 255;

    return color;
}

void CellManager::setPseudo(gengine::interface::event::SharedEvent<event::UserCmd> &e) {
    auto &texts = getComponents<gengine::component::driver::output::Text>();
    auto &remotes = getComponents<gengine::interface::component::RemoteLocal>();

    for (auto [_, text, remote]: gengine::Zip(texts, remotes)) {
        if (remote == e.remoteUUID) {
            text.str = e->pseudo;
        }
    }
}

void CellManager::onGameLoop(geg::event::GameLoop &e) {
    auto &transforms = getComponents<geg::component::Transform2D>();
    auto &texts = getComponents<gengine::component::driver::output::Text>();
    auto &remotes = getComponents<gengine::interface::component::RemoteLocal>();
    auto &circles = getComponents<geg::component::io::Circle>();
    auto &drawbles = getComponents<geg::component::io::Drawable>();
    auto &cells = getComponents<component::Cell>();

    for (auto [entity, tranform, text, remote, drawable]: gengine::Zip(transforms, texts, remotes, drawbles)) {
        for (auto [entity2, tranform2, circle, remote2, cell]: gengine::Zip(transforms, circles, remotes, cells)) {
            if (remote != remote)
                continue;
            tranform.pos.y = tranform2.pos.y;
            tranform.pos.x = tranform2.pos.x - (circle.r / 2);
            drawable = cell.size + 1;
        }
    }
}

void CellManager::spawnPlayer(gengine::interface::event::NewRemoteLocal &e) {
    gengine::Vect2 vPos{(rand() % (WINDOW_WIDTH - 10)) + 10.f, (rand() % (WINDOW_HEIGHT - 10)) + 10.f};
    spawnEntity(gengine::interface::component::RemoteLocal(e.uuid), geg::component::network::NetSend(),
                component::Cell(20), geg::component::io::Drawable(20),
                geg::component::io::Circle(20, std::move(rdmColor())),
                geg::component::Transform2D(vPos),
                gengine::component::Velocity2D());
    spawnEntity(gengine::interface::component::RemoteLocal(e.uuid), geg::component::network::NetSend(),
                gengine::component::driver::output::Text("arcade.ttf", "jkldsfdflskd"),
                geg::component::io::Drawable(20),
                geg::component::Transform2D(vPos));
}

void CellManager::movePlayer(gengine::interface::event::SharedEvent<event::UserCmd> &e) {
    auto &velocities = getComponents<gengine::component::Velocity2D>();
    auto &players = getComponents<component::Cell>();
    auto &remotes = getComponents<gengine::interface::component::RemoteLocal>();

    for (auto [entity, remote, player, velocity] : gengine::Zip(remotes, players, velocities)) {
        if (remote.getUUIDBytes() != e.remoteUUID) // check if its the same remote (zip)
            continue;

        float vel = 1 / player.size * 100;
        switch (e->mvState) {
        case event::UserCmd::MvState::LEFT:
            velocity = {-vel, 0};
            break;
        case event::UserCmd::MvState::RIGHT:
            velocity = {vel, 0};
            break;
        case event::UserCmd::MvState::UP:
            velocity = {0, -vel};
            break;
        case event::UserCmd::MvState::DOWN:
            velocity = {0, vel};
            break;
        case event::UserCmd::MvState::UP_RIGHT:
            velocity = {vel, -vel};
            break;
        case event::UserCmd::MvState::UP_LEFT:
            velocity = {-vel, -vel};
            break;
        case event::UserCmd::MvState::DOWN_RIGHT:
            velocity = {vel, vel};
            break;
        case event::UserCmd::MvState::DOWN_LEFT:
            velocity = {-vel, vel};
            break;
        case event::UserCmd::MvState::STANDING:
            velocity = {0, 0};
            break;
        }
    }
}

void CellManager::spawnFoodCell(geg::event::GameLoop &e) {
    auto &cells = getComponents<component::Cell>();
    auto nbCell = cells.size();
    if (nbCell >= MAX_FOOD)
        return;
    int toSpawn = std::rand() % (MAX_FOOD - nbCell);
    for (int i = 0; i < toSpawn; i++) {
        int size = rand() % 3 + 2;
        gengine::Vect2 pos = {rand() % WINDOW_WIDTH * 1.f, rand() % WINDOW_HEIGHT * 1.f};
        spawnEntity(geg::component::network::NetSend(), component::Cell(size), geg::component::io::Drawable(size),
                    geg::component::io::Circle(size, std::move(rdmColor())), geg::component::Transform2D(pos));
    }
}

void CellManager::updateSizes(geg::event::GameLoop &e) {
    auto &cells = getComponents<component::Cell>();
    auto &circles = getComponents<geg::component::io::Circle>();
    auto &drawables = getComponents<geg::component::io::Drawable>();

    for (auto [entity, cell, circle, drawable] : gengine::Zip(cells, circles, drawables)) {
        cell.size -= cell.size * 0.00001;
        circle.r = cell.size;
        drawable = cell.size;
    }
}

void CellManager::handleCollision(event::CellCollision &e) {
    if (e.ratio < 50)
        return;

    auto &cells = getComponents<component::Cell>();
    if (!(cells.contains(e.bigger) && cells.contains(e.smaller)))
        return;
    auto &bigger = cells.get(e.bigger);
    auto &smaller = cells.get(e.smaller);

    bigger.size += smaller.size;
    killEntity(e.smaller);
}

} // namespace hiop::system