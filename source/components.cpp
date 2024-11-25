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

void GEngineDeclareComponents(Registry *r) {
    r->registerComponent<geg::component::io::Circle>();
    r->registerComponent<geg::component::io::Drawable>();

    r->registerComponent<geg::component::Transform2D>();

    r->registerComponent<hiop::component::Cell>();


    r->registerComponent<gengine::interface::component::RemoteLocal>();
    r->registerComponent<geg::component::network::NetSend>();
}
