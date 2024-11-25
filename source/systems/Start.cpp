/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** Start.cpp
*/

#include "systems/Start.hpp"
#include "GEngine/libdev/systems/events/driver/output/Sound.hpp"

namespace hiop::system {
void Start::onEvent(gengine::system::event::StartEngine &e) {
    publishEvent(gengine::system::event::driver::output::Music("cr0c0.mp3"));
}
}