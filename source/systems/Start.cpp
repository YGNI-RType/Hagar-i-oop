/*
** EPITECH PROJECT, 2024
** Hagar-i-oop
** File description:
** Start.cpp
*/

#include "systems/Start.hpp"
#include "GEngine/libdev/systems/events/driver/output/Sound.hpp"

#include <iostream>
#include <string>
#include <random>

namespace hiop::system {
std::string Start::generateRandomString(size_t length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);
    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }
    return randomString;
}

void Start::onEvent(gengine::system::event::StartEngine &e) {
    publishEvent(gengine::system::event::driver::output::Music("cr0c0.mp3"));

    for (const std::string &p: e.params) {
        if (p.starts_with("--pseudo=")) {
            pseudo = p.substr(9);
            return;
        }
    }
    pseudo = generateRandomString(10);
}
}