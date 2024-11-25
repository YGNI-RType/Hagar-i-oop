/*
** EPITECH PROJECT, 2024
** r->
** File description:
** game.cpp
*/

#include "GEngine/libdev/Components.hpp"
#include "GEngine/GEngine.hpp"
#include "GEngine/interface/components/RemoteLocal.hpp"

#include "components/Cell.hpp"

#include "GEngine/libdev/components/driver/output/Sound.hpp"
#include "GEngine/libdev/components/driver/output/Text.hpp"

void GEngineDeclareComponents(Registry *r) {
    r->registerComponent<geg::component::io::Circle>();
    r->registerComponent<geg::component::io::Drawable>();

    r->registerComponent<geg::component::Transform2D>();
    r->registerComponent<geg::component::Velocity2D>();

    r->registerComponent<hiop::component::Cell>();

    r->registerComponent<gengine::component::driver::output::Text>();


    r->registerComponent<gengine::interface::component::RemoteLocal>();
    r->registerComponent<geg::component::network::NetSend>();

    r->registerComponent<gengine::component::driver::output::Music>();
    r->registerComponent<gengine::component::driver::output::Sound>();
}
