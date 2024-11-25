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

#include "GEngine/interface/systems/RemoteLocal.hpp"
#include "GEngine/interface/network/systems/ClientServer.hpp"

#include "systems/CellManager.hpp"
#include "InputToGameEvent.hpp"
#include "Constants.hpp"

void GEngineDeclareSystems(Registry *r) {
    r->registerSystem<geg::system::io::RenderWindow>(WINDOW_WIDTH, WINDOW_HEIGHT, "hagar-i-oop");
    r->registerSystem<geg::system::io::KeyboardCatcher>();
    r->registerSystem<geg::system::io::Draw>();
    r->registerSystem<geg::system::io::DrawCircle>();

    r->registerSystem<geg::system::Motion2D>();



    r->registerSystem<hiop::system::CellManager>();
    r->registerSystem<hiop::system::InputToGameEvent>();


    r->registerSystem<gengine::interface::network::system::ConnectAtStart>("127.0.0.1", 4242);

    r->registerSystem<gengine::interface::network::system::ClientEventPublisher<
        hiop::event::UserCmd>
    >();
    r->registerSystem<gengine::interface::network::system::ServerEventReceiver<
        hiop::event::UserCmd>
    >();
    r->registerSystem<gengine::interface::system::HandleRemoteLocal>();
    r->registerSystem<gengine::interface::system::HandleLocal>();
}
