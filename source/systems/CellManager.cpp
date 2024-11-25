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
}

static gengine::component::driver::output::Clr rdmColor(void) {
    gengine::component::driver::output::Clr color;
    color.a = 255;
    color.r = std::rand() % 255;
    color.g = std::rand() % 255;
    color.b = std::rand() % 255;

    return color;
}

void CellManager::spawnPlayer(gengine::interface::event::NewRemoteLocal &e) {
    spawnEntity(gengine::interface::component::RemoteLocal(e.uuid), geg::component::network::NetSend(),
                component::Cell(20), geg::component::io::Drawable(20),
                geg::component::io::Circle(20, RED),
                geg::component::Transform2D(gengine::Vect2{50, 50}));
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
                    geg::component::io::Circle(size, std::move(rdmColor())),
                    geg::component::Transform2D(pos));
    }
}

void CellManager::updateSizes(geg::event::GameLoop &e) {
    auto &cells = getComponents<component::Cell>();
    auto &circles = getComponents<geg::component::io::Circle>();
    auto &drawables = getComponents<geg::component::io::Drawable>();

    for (auto [entity, cell, circle, drawable] : gengine::Zip(cells, circles, drawables)) {
        // cell.size -= cell.size * 0.00001;
        circle.r = cell.size;
        drawable = cell.size;
    }
}

void CellManager::handleCollision(event::CellCollision &e) {
    if (e.ratio < 50)
        return;
    std::cout << e.ratio << std::endl;

    auto &cells = getComponents<component::Cell>();
    if (!(cells.contains(e.bigger) && cells.contains(e.smaller)))
        return;
    auto &bigger = cells.get(e.bigger);
    auto &smaller = cells.get(e.smaller);

    bigger.size += smaller.size;
    killEntity(e.smaller);
}

} // namespace hiop::system