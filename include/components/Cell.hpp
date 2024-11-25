/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** Cell.hpp
*/

#pragma once

#include "GEngine/libdev/Components.hpp"

namespace hiop::component {
    struct Cell : gengine::Component<Cell> {
        float size;

        Cell(float size) : size(size) {
        }

        bool operator==(const Cell &) const = default;
    };
}