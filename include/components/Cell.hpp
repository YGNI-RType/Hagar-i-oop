/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** Cell.hpp
*/

#include "GEngine/libdev/Components.hpp"

namespace hiop::component {
    struct Cell : gengine::Component<Cell> {
        uint16_t size;

        Cell(uint16_t size) : size(size) {
        }

        bool operator==(const Cell &) const = default;
    };
}