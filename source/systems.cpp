/*
** EPITECH PROJECT, 2024
** GameEngine
** File description:
** shared.cpp
*/

#include "GEngine/libdev/Systems.hpp"
#include "GEngine/interface/network/systems/ClientEventPublisher.hpp"
#include "GEngine/interface/network/systems/ServerEventReceiver.hpp"
#include "GEngine/GEngine.hpp"
#include "events/UserCmd.hpp"

void GEngineDeclareSystems(Registry *r) {
    r->registerSystem<gengine::system::driver::input::MouseCatcher>();
    r->registerSystem<gengine::system::driver::input::KeyboardCatcher>();

    r->registerSystem<gengine::interface::network::system::ClientEventPublisher<
        hiop::event::UserCmd>
    >();
    r->registerSystem<gengine::interface::network::system::ServerEventReceiver<
        hiop::event::UserCmd>
    >();
}
