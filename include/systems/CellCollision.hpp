/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** CellCollision.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/Events.hpp"
#include "GEngine/libdev/Components.hpp"
#include "events/CellCollision.hpp"

namespace hiop::system {
struct CellCollision: public gengine::System<CellCollision, geg::component::Transform2D, geg::component::io::Circle> {
    void init(void) override;
    void onGameLoop(geg::event::GameLoop &);
};
}