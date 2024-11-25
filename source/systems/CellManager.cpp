/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** CellManager.cpp
*/

#include "systems/CellManager.hpp"

namespace hiop::system {
void CellManager::init(void) {
    subscribeToEvent<gengine::interface::event::NewRemoteLocal>(&CellManager::spawnPlayer);
    subscribeToEvent<geg::event::GameLoop>(&CellManager::updateSizes);
    subscribeToEvent<geg::event::GameLoop>(&CellManager::spawnFoodCell);
    subscribeToEvent<event::CellCollision>(&CellManager::handleCollision);
}

static gengine::component::driver::output::Clr &&randomColor(void) {
    gengine::component::driver::output::Clr color;
    color.a = 255;
    color.r = std::rand() % 255;
    color.g = std::rand() % 255;
    color.b = std::rand() % 255;

    return std::move(color);
}

void CellManager::spawnPlayer(gengine::interface::event::NewRemoteLocal &e) {
    spawnEntity(gengine::interface::component::RemoteLocal(e.uuid), geg::component::network::NetSend(), component::Cell(20), geg::component::io::Drawable(20), geg::component::io::Circle(20, randomColor()));
}

void CellManager::spawnFoodCell(geg::event::GameLoop &e)
{
    auto &cells = getComponents<component::Cell>();
    auto nbCell = cells.size();
    if (nbCell >= MAX_FOOD)
        return;
    int toSpawn = std::rand() % (MAX_FOOD - nbCell);
    for (int i = 0; i < toSpawn; i++) {
        int size = rand() % 3 + 2;
        spawnEntity(geg::component::network::NetSend(), component::Cell(size), geg::component::io::Drawable(size), geg::component::io::Circle(size, randomColor()));
    }
}

void CellManager::updateSizes(geg::event::GameLoop &e) {
    auto &cells = getComponents<component::Cell>();
    auto &circles = getComponents<geg::component::io::Circle>();

    for (auto [entity, cell, circle] : gengine::Zip(cells, circles)) {
        cell.size -= cell.size * 0.001;
        circle.r = cell.size;
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