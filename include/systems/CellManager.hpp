/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** CellManager.hpp
*/

#pragma once

#include "GEngine/interface/events/RemoteLocal.hpp"
#include "GEngine/interface/events/SharedEvent.hpp"
#include "GEngine/libdev/Components.hpp"
#include "GEngine/libdev/Events.hpp"
#include "GEngine/libdev/System.hpp"

#include "components/Cell.hpp"
#include "events/CellCollision.hpp"
#include "events/UserCmd.hpp"

#define MAX_FOOD 100

namespace hiop::system {
class CellManager : public gengine::System<CellManager, component::Cell, geg::component::io::Circle, geg::component::io::Drawable, geg::component::Velocity2D, gengine::interface::component::RemoteLocal>, public gengine::RemoteSystem {
public:
    CellManager() = default;
    ~CellManager() = default;

    void init(void) final;

    void spawnPlayer(gengine::interface::event::NewRemoteLocal &e);
    void spawnFoodCell(geg::event::GameLoop &e);

    void updateSizes(geg::event::GameLoop &);
    void handleCollision(event::CellCollision &);

    void movePlayer(gengine::interface::event::SharedEvent<event::UserCmd> &);
};
} // namespace hiop::system