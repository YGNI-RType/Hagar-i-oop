/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** CellCollision.hpp
*/

#pragma once

#include "GEngine/libdev/Entity.hpp"
#include "GEngine/libdev/System.hpp"

namespace hiop::event {
struct CellCollision : public gengine::Event {
    gengine::Entity bigger;
    gengine::Entity smaller;
    uint8_t ratio;

    CellCollision(gengine::Entity bigger, gengine::Entity smaller, uint8_t ratio)
        : bigger(bigger)
        , smaller(smaller)
        , ratio(ratio) {
    }
};
} // namespace hiop