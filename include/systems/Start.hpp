/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** Start.hpp
*/

#pragma once

#include "GEngine/libdev/System.hpp"
#include "GEngine/libdev/systems/events/Native.hpp"

#include <string>

namespace hiop::system {
struct Start: public gengine::OnEventSystem<Start, gengine::system::event::StartEngine> {
    void onEvent(gengine::system::event::StartEngine &) override;
    std::string generateRandomString(size_t length);

    std::string pseudo;
};
}